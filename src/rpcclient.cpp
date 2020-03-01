#include "rpcclient.h"
#include "zookeeperutil.h"

RpcClient::RpcClient()
	:client_(nullptr)
{}

RpcClient::~RpcClient()
{
	delete client_;
	client_ = nullptr;
}
void RpcClient::CallMethod(const MethodDescriptor* method,
	RpcController* controller, const Message* request,
	Message* response, Closure* done)
{
	//1.�õ��ͻ��˷�����method��method�ǿ��Ի�ȡ����������ĸ�service
	string method_name = method->name();
	auto service = method->service();
	string service_name = service->name();

	// ͨ��zkclient����rpc�����Ƿ����
	ZkClient zk;
	zk.start(); 
	string path = ZkClient::getRootPath() + "/" + service_name + "/" + method_name;//��װ·��
	string host = zk.get(path.c_str());
	if (host.size() == 0) // û�ҵ�����rpc�����host
	{
		// ����Ӧ��д�������Ϣ�������ظ�rpcclient
		int errcode = 2;
		cout << "RPC host that we found not exist" << endl;
		return ;
	}

	//��������ʼ��װ�ͻ��˵������ַ���
	string send_str;
	//���Ⱦ�����Ϣ��
	MessageInfo request_msg;
	request_msg.set_method_name(method_name);
	request_msg.set_service_name(service_name);

	string request_body;
	request_msg.SerializeToString(&request_body);
	int request_body_size = request_body.size();
	//Ȼ�������Ϣͷ����Ϣͷ�����ݾ�����Ϣ��Ĵ�С

	string request_args;
	request->SerializeToString(&request_args);
	//����Ҫ���͵��ַ���
	string send_request_str;
	//�Ƚ���Ϣ��ĳ��ȷŵ�ǰ4���ֽ���
	send_request_str.insert(0, string((char*)& request_body_size, 4));//��ָ����С����һ��string���󲢲��뵽�����ַ�����
	send_request_str += request_body;
	send_request_str += request_args;

	//��¼һ����־���Ա���
	LOG_INFO << "request_body_size:" << request_body_size ;
	LOG_INFO << "request_body:" << request_body;
	LOG_INFO << "service_name:" << service_name ;
	LOG_INFO << "method_name:" << method_name ;
	LOG_INFO << "request_args:" << request_args ;
	
	//��װ���ַ�����Ҫ��ʼ������
	//1.����newһ��client2.���������ص�3.������������4.�����¼�ѭ��

	//������д����server�˵�ip:port�������Ǵ�zk�����������Ļ�ȡ
	//����ԭ����ip+port����ip:port������ʽ���ַ�������Ҫ�ָ�
	int index = host.find(":");
	string ip = host.substr(0,index);
	unsigned short port = atoi(host.substr(index + 1).c_str());

	//client_ = new TcpClient(&loop_, InetAddress("127.0.0.1", 10000), "server");
	client_ = new TcpClient(&loop_, InetAddress(ip, port), "");
	client_->setConnectionCallback(bind(&RpcClient::onConnection,this,_1));
	client_->setMessageCallback(bind(&RpcClient::onMassage, this, _1, _2, _3));

	//������Ԥ�Ʒ����ַ����Ļص�����
	sendrequestCallBack = [&](const TcpConnectionPtr& con) {con->send(send_request_str); };
	responseCallBack = [&](string message) {response->ParseFromString(message); };

	//�����������󲢿����¼�ѭ��
	client_->connect();//client_fd->connect(),epoll_ctl��client_fd��ӵ�epoll_wait��
	loop_.loop();//����epoll_wait
}
/*
������Ƶĺ���̶�
1.������·��������˵����Ϊ�����̣߳�һ����IO�̣߳�һ����worker�̡߳�
IO�̣߳������������û���worker�̣߳������������û���RW�¼���
����muduo��ķ������˿��������߳�����
���ڿͻ�����˵ֻ��һ���̣߳�IO��worker��ͬһ���̡߳��ͻ��˵����Ӻ���Ϣ���շ�������һ���߳��

*/


#if 0
// rpc client�����е�rpc���񷽷��������ն���������
void RpcClient::CallMethod(const MethodDescriptor* method,
	RpcController* controller, const Message* request,
	Message* response, Closure* done)
{
	// ��֯rpc client���͵���Ϣ
	auto service = method->service();
	string service_name = service->name();
	string method_name = method->name();

	// ͨ��zkclient����rpc�����Ƿ����
	ZkClient zk;
	zk.start();
	string path = ZkClient::getRootPath() + "/" + service_name + "/" + method_name;
	string host = zk.get(path.c_str());
	if (host.size() == 0) // û�ҵ�rpc�����host
	{
		// ����Ӧ��д�������Ϣ��ֱ�ӷ���
		return;
	}

	// ��װRPC�����ַ���
	MessageInfo header;
	header.set_service_name(service_name);
	header.set_method_name(method_name);
	string rpc_header_str;
	header.SerializeToString(&rpc_header_str);
	int header_size = rpc_header_str.size();

	string rpc_args_str;
	request->SerializeToString(&rpc_args_str);

	string request_send_str;
	request_send_str.insert(0, string((char*)& header_size, 4));
	request_send_str += rpc_header_str;
	request_send_str += rpc_args_str;

	cout << "============================================" << endl;
	cout << "header_size:" << header_size << endl;
	cout << "rpc_header_str:" << rpc_header_str << endl;
	cout << "service_name:" << service_name << endl;
	cout << "method_name:" << method_name << endl;
	cout << "rpc_args_str:" << rpc_args_str << endl;
	cout << "============================================" << endl;

	// Ԥ��һ���ص���������RpcServer�ɹ�������RPC�����ַ���
	sendRpcCallBack = [&](const TcpConnectionPtr& con) {
		con->send(request_send_str);
	};

	// Ԥ��һ���ص������첽���յ�rpc server��Ӧ��ʱ�򣬵��ûص�
	responseCallBack_ = [&](string message) {
		response->ParseFromString(message);
	};

	// �������¼���֪ͨ����
	client_->setConnectionCallback(bind(&RpcClient::onConnection, this, _1));
	// ����Ϣ�¼���֪ͨ����
	client_->setMessageCallback(bind(&RpcClient::onMassage, this, _1, _2, _3));
	client_->connect();
	loop_.loop();
}
#endif
// ���ӻص� - ��client���ӻ��߶Ͽ����ӣ��ú��������
void RpcClient::onConnection(const TcpConnectionPtr& conn)
{
	if (conn->connected()) // ��ʾ�����Ӵ���
	{//���ӳɹ���Ȼ��ʼ���������ַ���������Ϊ�����ַ�����CallMethod�û�취��������ã�������Ҫ���ûص�����

		// ���ӳɹ���������ִ��rpc�����ص�
		sendrequestCallBack(conn);
	}
	else//��ʾrpc��ܴ������ҵ������ˣ�rpc�����Ͽ�������
	{
		conn->shutdown(); // �ر�����
		loop_.quit(); // ����rpc��������� �˳��¼�ѭ��
	}
}
//������������ͻ�������Ϣ
// ��Ϣ�ص�
void RpcClient::onMassage(const TcpConnectionPtr& conn,
	Buffer* buf, Timestamp time)
{
	// �������rpcԶ�̵��÷���������server�ķ���ֵ���õ��������ø��˼��û����ؽ����
	//���û�ֻ���õ�response����������Ҳ��Ҫ���ûص�,��messageд��response��ȥ
	string message = buf->retrieveAllAsString();//����·��Я�������ݷ�װ��buf�У��������ַ����ٷ����л�д��response
	cout <<"response_str's message:  " <<message << endl;
    // ���û�����RPC���õĽ��
	responseCallBack(message);
}