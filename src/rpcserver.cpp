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
	// 设置回调函数
	server_.setConnectionCallback(bind(&RpcServer::onConnection, this, _1));
	server_.setMessageCallback(bind(&RpcServer::onMessage, this, _1, _2, _3));

	// 设置线程数量
	server_.setThreadNum(4);

	// 连接zookeeper
	_zkclient.start();
	// 当连接成功之后就开始向zkserver发送心跳，维护session
	_zkclient.sendHeartBeat();
}
//设计成单例的好处就是，把创建服务器的细节封装在了对象创建的过程中，用户使用的时候就不需要关注。
RpcServer* RpcServer::getInstance()//把服务器的启动放到获取单例这儿。
{
	if (nullptr == rpcServer_)
	{
		static EventLoop loop;
		string IP = XmlConfig::getInstance().getRpcServerIp();
		unsigned short Port = XmlConfig::getInstance().getRpcServerPort();
		//static InetAddress addr("127.0.0.1", 10000);//可以从配置文件加载ip+port
		static InetAddress addr(IP,Port);
		rpcServer_ = new RpcServer(&loop, addr, "server");//启动一个rpc站点，把本地的6000端口绑定到rpcserver上。
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

	//创建服务节点znode
	string path = _zkclient.getRootPath();
	path += "/" + service_name;
	_zkclient.create(path.c_str(), nullptr, -1);

	for (int i = 0; i < _count; ++i)
	{
		const google::protobuf::MethodDescriptor* method = _descriptor->method(i);
		string method_name = method->name();
		_info.method_map.insert({ method_name ,method});

		//当注册服务的时候也需要将该服务节点创建在zk上
		string method_path;
		method_path += ( path + "/" + method_name);
		_zkclient.create(method_path.c_str(), server_.ipPort().c_str(), server_.ipPort().size(), ZOO_EPHEMERAL);
	}
    service_map[_descriptor->name()] = _info;
	cout << "call RpcServer::registerService succeed!!!" << endl;
}

void RpcServer::run()
{
	server_.start();//通过epoll_add将listen_fd添加到epoll中
	loop_->loop();//启动epoll_wait
}

// 处理新连接和连接断开
//void RpcServer::onConnection(const TcpConnectionPtr& con)
//{
	//处理rpcclient的连接事件和断开事件
	//当有新连接来时，或者旧的连接要断开时，该回调函数会被触发
	//cout << "客户端 ：" << con->peerAddress().toIpPort();
	//有新连接到来时，打印客户端的ip+port
	//由于服务器采取短链接来处理，当响应完客户端的请求以后就主动断开连接了，所以不用对连接断开(这里的连接)做相应的处理。
//}
void RpcServer::onConnection(const TcpConnectionPtr& con)
{
	 //当执行完回调之后服务端主动断开连接。所以不用处理连接断开事件，只关心连接建立事件
	if (con->connected())
	{
		cout << "来自客户端 " << con->peerAddress().toIpPort() << " 的连接";
	}
}
void  RpcServer::onMessage(const TcpConnectionPtr& con, Buffer* buf, Timestamp time)
{
	//1.解析buf中的数据,按格式剥离数据，2.查询map表找到对应的方法  3.调用该方法
	string message = buf->retrieveAllAsString();
	//前四字节的size   中间是service_name+method_name  最后是args
	int MessageInfo_size = 0;
	message.copy((char*)&MessageInfo_size, sizeof(int), 0);//copy函数的作用是从string对象中取出若干字符存放到数组s中。其中，s是字符数组，len表示要取出字符的个数，pos表示要取出字符的开始位置

	string FromClientRequest;
	FromClientRequest = message.substr(4, MessageInfo_size);
	//该字符串时protobuf对Message序列化之后的结果，所以我们需要反序列化拿到request参数中的service_name和method_name
	
	MessageInfo request_info;//在proto文件中定义好的交互参数的打包类型
	request_info.ParseFromString(FromClientRequest);

	//调用protobuf为我们生成的get/set方法中的get方法获取数据
	string service_name = request_info.service_name();
	string method_name = request_info.method_name();

	//接下来做第二件事情，查询服务和方法是否存在
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
	//如果在map表中查询到了已存在的service和method，该如何调用呢？首先需要明确的是作为框架一定是通过callMethod来调用到本地方法的
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

	//done是我们预制的回调函数
	auto done = google::protobuf::NewCallback
		<RpcServer, const TcpConnectionPtr& , google::protobuf::Message*>
		(this,&RpcServer::sendResponseCallBack,con,response);

	//最终的目的是让框架能调用到本地业务，也就是框架通过CallMethod调用到本地proto文件中定义的rpc服务
	_service->CallMethod(method,nullptr,request, response, done);
}

/* done是protobuf给我们预留的回调接口，使用protobuf库提供的定义回调的函数NewCallback()
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
// 处理收发消息,当有消息到来时该函数会被调用
void RpcServer::onMessage(const TcpConnectionPtr& con, Buffer* buf, Timestamp time)
{
	// 提取头部信息的前四个字节
	string message = buf->retrieveAllAsString(); // 读取客户端发送的序列化的数据
   // 读取message的前四个字节的整数
	int header_size = 0;
	message.copy((char*)& header_size, sizeof(int));
	// 读取服务类型和方法
	string service_method;
	service_method = message.substr(4, header_size); // 参数1是截取开始、参数2是截取长度
    // 将数据反序列化
	MessageInfo headerInfo;
	headerInfo.ParseFromString(service_method);
	string service_name = headerInfo.service_name(); // 获取服务类名
	string method_name = headerInfo.method_name(); // 获取具体的方法名
	// 读取参数
	string method_args;
	method_args = message.substr(4 + header_size);
	// 在RPC框架上注册的服务类中寻找所要调用的服务类名
	auto  service_info = service_map.find(service_name);
	Buffer buff;//用于回给client的消息
	if (service_info == service_map.end())// 没找到，说明该服务未发布
	{
		buff.append("service not exist");
		con->send(&buff);
	}
	// 在服务类中寻找所需要调用的方法
	auto method = service_map[service_name].method_map.find(method_name);
	if (method == service_map[service_name].method_map.end())// 没找到，说明该服务上未发布该方法
	{
		buff.append("method not exist in this service");
		con->send(&buff);
	}
	// 获取该方法的proto定义的参数类型格式
	// 参数格式指针
	auto request = service_info->second.service->GetRequestPrototype(method->second).New();
	request->ParseFromString(method_args); // 将参数反序列化
	// 返回值格式指针
	auto response = service_info->second.service->GetResponsePrototype(method->second).New();
	// 当RPC方法调用完成后，给框架设置的回调
	auto done = google::protobuf::NewCallback
		<RpcServer, const TcpConnectionPtr&, google::protobuf::Message*>
		(this, &RpcServer::sendResponseCallBack, con, response);
	// 由框架来为我们去调用具体的方法
	auto service = service_map[service_name].service;
	service->CallMethod(method->second, nullptr, request, response, done);
}
#endif


// RPC方法处理完以后调用的回调方法
void RpcServer::sendResponseCallBack(const TcpConnectionPtr& con,
	google::protobuf::Message* response)
{
	// 将response返回给客户端
	string response_str;
	response->SerializeToString(&response_str);
	con->send(response_str);
	con->shutdown();// 采取短链接的方式,由服务器断开连接
}
//这就是testrpcserver调用done->Run()时，实际调用的函数。