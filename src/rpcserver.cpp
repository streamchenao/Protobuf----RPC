#include "rpcserver.h"
#include<functional>
#include<algorithm>
#include "loadxmlconfig.h"
/*
struct ServiceInfo
{
	google::protobuf::Service* service;
	unordered_map<string, const google::protobuf::MethodDescriptor*> method_map;
};
unordered_map<string, ServiceInfo> service_map;
*/
RpcServer*  RpcServer::rpcServer_ = nullptr;

RpcServer::RpcServer(EventLoop* loop,
	const InetAddress& listenAddr,
	const string& nameArg)
	:server_(loop, listenAddr, nameArg)
	, loop_(loop)
{
	// ���ûص�����
	server_.setConnectionCallback(bind(&RpcServer::onConnection, this, _1));
	server_.setMessageCallback(bind(&RpcServer::onMessage, this, _1, _2, _3));

	// �����߳�����
	server_.setThreadNum(4);

	// ����zookeeper
	_zkclient.start();
	// �����ӳɹ�֮��Ϳ�ʼ��zkserver����������ά��session
	_zkclient.sendHeartBeat();
}
//��Ƴɵ����ĺô����ǣ��Ѵ�����������ϸ�ڷ�װ���˶��󴴽��Ĺ����У��û�ʹ�õ�ʱ��Ͳ���Ҫ��ע��
RpcServer* RpcServer::getInstance()//�ѷ������������ŵ���ȡ���������
{
	if (nullptr == rpcServer_)
	{
		static EventLoop loop;
		string IP = XmlConfig::getInstance().getRpcServerIp();
		unsigned short Port = XmlConfig::getInstance().getRpcServerPort();
		//static InetAddress addr("127.0.0.1", 10000);//���Դ������ļ�����ip+port
		static InetAddress addr(IP,Port);
		rpcServer_ = new RpcServer(&loop, addr, "server");//����һ��rpcվ�㣬�ѱ��ص�6000�˿ڰ󶨵�rpcserver�ϡ�
	}
	return rpcServer_;
}

void RpcServer::registerService(google::protobuf::Service* _service)
{
	ServiceInfo _info;
	_info.service = _service; 

	const ServiceDescriptor* _descriptor = _service->GetDescriptor();
	int _count = _descriptor->method_count();
	string service_name = _descriptor->name();

	//��������ڵ�znode
	string path = _zkclient.getRootPath();
	path += "/" + service_name;
	_zkclient.create(path.c_str(), nullptr, -1);

	for (int i = 0; i < _count; ++i)
	{
		const google::protobuf::MethodDescriptor* method = _descriptor->method(i);
		string method_name = method->name();
		_info.method_map.insert({ method_name ,method});

		//��ע������ʱ��Ҳ��Ҫ���÷���ڵ㴴����zk��
		string method_path;
		method_path += ( path + "/" + method_name);
		_zkclient.create(method_path.c_str(), server_.ipPort().c_str(), server_.ipPort().size(), ZOO_EPHEMERAL);
	}
    service_map[_descriptor->name()] = _info;
	cout << "call RpcServer::registerService succeed!!!" << endl;
}

void RpcServer::run()
{
	server_.start();//ͨ��epoll_add��listen_fd��ӵ�epoll��
	loop_->loop();//����epoll_wait
}

// ���������Ӻ����ӶϿ�
//void RpcServer::onConnection(const TcpConnectionPtr& con)
//{
	//����rpcclient�������¼��ͶϿ��¼�
	//������������ʱ�����߾ɵ�����Ҫ�Ͽ�ʱ���ûص������ᱻ����
	//cout << "�ͻ��� ��" << con->peerAddress().toIpPort();
	//�������ӵ���ʱ����ӡ�ͻ��˵�ip+port
	//���ڷ�������ȡ����������������Ӧ��ͻ��˵������Ժ�������Ͽ������ˣ����Բ��ö����ӶϿ�(���������)����Ӧ�Ĵ���
//}
void RpcServer::onConnection(const TcpConnectionPtr& con)
{
	 //��ִ����ص�֮�����������Ͽ����ӡ����Բ��ô������ӶϿ��¼���ֻ�������ӽ����¼�
	if (con->connected())
	{
		cout << "���Կͻ��� " << con->peerAddress().toIpPort() << " ������";
	}
}
void  RpcServer::onMessage(const TcpConnectionPtr& con, Buffer* buf, Timestamp time)
{
	//1.����buf�е�����,����ʽ�������ݣ�2.��ѯmap���ҵ���Ӧ�ķ���  3.���ø÷���
	string message = buf->retrieveAllAsString();
	//ǰ���ֽڵ�size   �м���service_name+method_name  �����args
	int MessageInfo_size = 0;
	message.copy((char*)&MessageInfo_size, sizeof(int), 0);//copy�����������Ǵ�string������ȡ�������ַ���ŵ�����s�С����У�s���ַ����飬len��ʾҪȡ���ַ��ĸ�����pos��ʾҪȡ���ַ��Ŀ�ʼλ��

	string FromClientRequest;
	FromClientRequest = message.substr(4, MessageInfo_size);
	//���ַ���ʱprotobuf��Message���л�֮��Ľ��������������Ҫ�����л��õ�request�����е�service_name��method_name
	
	MessageInfo request_info;//��proto�ļ��ж���õĽ��������Ĵ������
	request_info.ParseFromString(FromClientRequest);

	//����protobufΪ�������ɵ�get/set�����е�get������ȡ����
	string service_name = request_info.service_name();
	string method_name = request_info.method_name();

	//���������ڶ������飬��ѯ����ͷ����Ƿ����
	auto service_info = service_map.find(service_name);
	if (service_info == service_map.end())
	{
		Buffer buf;
		buf.append("service not found!!!");
		con->send(&buf);
	}
	auto method_info = service_map[service_name].method_map.find(method_name);
	if (method_info == service_map[service_name].method_map.end())
	{
		Buffer buf;
		buf.append("Service Founded but method not found!!!");
		con->send(&buf);
	}
	//�����map���в�ѯ�����Ѵ��ڵ�service��method������ε����أ�������Ҫ��ȷ������Ϊ���һ����ͨ��callMethod�����õ����ط�����
// Example:
  //   const MethodDescriptor* method =
  //     service->GetDescriptor()->FindMethodByName("Foo");
  //   Message* request  = stub->GetRequestPrototype (method)->New();
  //   Message* response = stub->GetResponsePrototype(method)->New();
  //   request->ParseFromString(input);
  //   service->CallMethod(method, *request, response, callback);
	google::protobuf::Service* _service = service_info->second.service;
		//service_map[service_name].service;
	 const MethodDescriptor* method = method_info->second;
		//service_map[service_name].method_map[method_name];

	Message* request = _service->GetRequestPrototype(method).New();
		
    Message* response = _service->GetResponsePrototype(method).New();

	//done������Ԥ�ƵĻص�����
	auto done = google::protobuf::NewCallback
		<RpcServer, const TcpConnectionPtr& , google::protobuf::Message*>
		(this,&RpcServer::sendResponseCallBack,con,response);

	//���յ�Ŀ�����ÿ���ܵ��õ�����ҵ��Ҳ���ǿ��ͨ��CallMethod���õ�����proto�ļ��ж����rpc����
	_service->CallMethod(method,nullptr,request, response, done);
}

/* done��protobuf������Ԥ���Ļص��ӿڣ�ʹ��protobuf���ṩ�Ķ���ص��ĺ���NewCallback()
template <typename Class, typename Arg1, typename Arg2>
inline Closure* NewCallback(Class* object, void (Class::*method)(Arg1, Arg2),
							Arg1 arg1, Arg2 arg2) {
  return new internal::MethodClosure2<Class, Arg1, Arg2>(
	object, method, true, arg1, arg2);
}
*/
/*
void UserServiceRpc::CallMethod(const ::google::protobuf::MethodDescriptor* method,
							 ::PROTOBUF_NAMESPACE_ID::RpcController* controller,
							 const google::protobuf::Message* request,
							 ::google::protobuf:::Message* response,
							 ::google::protobuf::Closure* done)
*/
#if 0
// �����շ���Ϣ,������Ϣ����ʱ�ú����ᱻ����
void RpcServer::onMessage(const TcpConnectionPtr& con, Buffer* buf, Timestamp time)
{
	// ��ȡͷ����Ϣ��ǰ�ĸ��ֽ�
	string message = buf->retrieveAllAsString(); // ��ȡ�ͻ��˷��͵����л�������
   // ��ȡmessage��ǰ�ĸ��ֽڵ�����
	int header_size = 0;
	message.copy((char*)& header_size, sizeof(int));
	// ��ȡ�������ͺͷ���
	string service_method;
	service_method = message.substr(4, header_size); // ����1�ǽ�ȡ��ʼ������2�ǽ�ȡ����
    // �����ݷ����л�
	MessageInfo headerInfo;
	headerInfo.ParseFromString(service_method);
	string service_name = headerInfo.service_name(); // ��ȡ��������
	string method_name = headerInfo.method_name(); // ��ȡ����ķ�����
	// ��ȡ����
	string method_args;
	method_args = message.substr(4 + header_size);
	// ��RPC�����ע��ķ�������Ѱ����Ҫ���õķ�������
	auto  service_info = service_map.find(service_name);
	Buffer buff;//���ڻظ�client����Ϣ
	if (service_info == service_map.end())// û�ҵ���˵���÷���δ����
	{
		buff.append("service not exist");
		con->send(&buff);
	}
	// �ڷ�������Ѱ������Ҫ���õķ���
	auto method = service_map[service_name].method_map.find(method_name);
	if (method == service_map[service_name].method_map.end())// û�ҵ���˵���÷�����δ�����÷���
	{
		buff.append("method not exist in this service");
		con->send(&buff);
	}
	// ��ȡ�÷�����proto����Ĳ������͸�ʽ
	// ������ʽָ��
	auto request = service_info->second.service->GetRequestPrototype(method->second).New();
	request->ParseFromString(method_args); // �����������л�
	// ����ֵ��ʽָ��
	auto response = service_info->second.service->GetResponsePrototype(method->second).New();
	// ��RPC����������ɺ󣬸�������õĻص�
	auto done = google::protobuf::NewCallback
		<RpcServer, const TcpConnectionPtr&, google::protobuf::Message*>
		(this, &RpcServer::sendResponseCallBack, con, response);
	// �ɿ����Ϊ����ȥ���þ���ķ���
	auto service = service_map[service_name].service;
	service->CallMethod(method->second, nullptr, request, response, done);
}
#endif


// RPC�����������Ժ���õĻص�����
void RpcServer::sendResponseCallBack(const TcpConnectionPtr& con,
	google::protobuf::Message* response)
{
	// ��response���ظ��ͻ���
	string response_str;
	response->SerializeToString(&response_str);
	con->send(response_str);
	con->shutdown();// ��ȡ�����ӵķ�ʽ,�ɷ������Ͽ�����
}
//�����testrpcserver����done->Run()ʱ��ʵ�ʵ��õĺ�����