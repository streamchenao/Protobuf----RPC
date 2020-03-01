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
	//1.拿到客户端发来的method，method是可以获取到其从属于哪个service
	string method_name = method->name();
	auto service = method->service();
	string service_name = service->name();

	// 通过zkclient查找rpc服务是否存在
	ZkClient zk;
	zk.start(); 
	string path = ZkClient::getRootPath() + "/" + service_name + "/" + method_name;//组装路径
	string host = zk.get(path.c_str());
	if (host.size() == 0) // 没找到发布rpc服务的host
	{
		// 这里应该写入错误信息，并返回给rpcclient
		int errcode = 2;
		cout << "RPC host that we found not exist" << endl;
		return ;
	}

	//接下来开始组装客户端的请求字符串
	string send_str;
	//首先具有消息体
	MessageInfo request_msg;
	request_msg.set_method_name(method_name);
	request_msg.set_service_name(service_name);

	string request_body;
	request_msg.SerializeToString(&request_body);
	int request_body_size = request_body.size();
	//然后加上消息头，消息头的内容就是消息体的大小

	string request_args;
	request->SerializeToString(&request_args);
	//最终要发送的字符串
	string send_request_str;
	//先将消息体的长度放到前4个字节里
	send_request_str.insert(0, string((char*)& request_body_size, 4));//按指定大小构造一个string对象并插入到发送字符串中
	send_request_str += request_body;
	send_request_str += request_args;

	//记录一下日志，以便查错
	LOG_INFO << "request_body_size:" << request_body_size ;
	LOG_INFO << "request_body:" << request_body;
	LOG_INFO << "service_name:" << service_name ;
	LOG_INFO << "method_name:" << method_name ;
	LOG_INFO << "request_args:" << request_args ;
	
	//组装好字符串就要开始发送了
	//1.首先new一个client2.设置两个回调3.发送连接请求4.启动事件循环

	//本来是写死的server端的ip:port，现在是从zk服务配置中心获取
	//由于原本的ip+port是以ip:port这样形式的字符串，需要分割
	int index = host.find(":");
	string ip = host.substr(0,index);
	unsigned short port = atoi(host.substr(index + 1).c_str());

	//client_ = new TcpClient(&loop_, InetAddress("127.0.0.1", 10000), "server");
	client_ = new TcpClient(&loop_, InetAddress(ip, port), "");
	client_->setConnectionCallback(bind(&RpcClient::onConnection,this,_1));
	client_->setMessageCallback(bind(&RpcClient::onMassage, this, _1, _2, _3));

	//在这里预制发送字符串的回调函数
	sendrequestCallBack = [&](const TcpConnectionPtr& con) {con->send(send_request_str); };
	responseCallBack = [&](string message) {response->ParseFromString(message); };

	//发起连接请求并开启事件循环
	client_->connect();//client_fd->connect(),epoll_ctl将client_fd添加到epoll_wait中
	loop_.loop();//启动epoll_wait
}
/*
考虑设计的合理程度
1.对于网路服务器来说都分为两类线程，一类是IO线程，一类是worker线程。
IO线程：负责新连接用户，worker线程：负责已连接用户的RW事件。
对于muduo库的服务器端可以设置线程数量
对于客户端来说只有一个线程，IO和worker是同一个线程。客户端的连接和消息的收发都放在一个线程里。

*/


#if 0
// rpc client端所有的rpc服务方法调用最终都到达这里
void RpcClient::CallMethod(const MethodDescriptor* method,
	RpcController* controller, const Message* request,
	Message* response, Closure* done)
{
	// 组织rpc client发送的消息
	auto service = method->service();
	string service_name = service->name();
	string method_name = method->name();

	// 通过zkclient查找rpc服务是否存在
	ZkClient zk;
	zk.start();
	string path = ZkClient::getRootPath() + "/" + service_name + "/" + method_name;
	string host = zk.get(path.c_str());
	if (host.size() == 0) // 没找到rpc服务的host
	{
		// 这里应该写入错误信息，直接返回
		return;
	}

	// 组装RPC请求字符串
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

	// 预设一个回调，当连接RpcServer成功，发送RPC请求字符串
	sendRpcCallBack = [&](const TcpConnectionPtr& con) {
		con->send(request_send_str);
	};

	// 预设一个回调，当异步接收到rpc server响应的时候，调用回调
	responseCallBack_ = [&](string message) {
		response->ParseFromString(message);
	};

	// 绑定连接事件的通知函数
	client_->setConnectionCallback(bind(&RpcClient::onConnection, this, _1));
	// 绑定消息事件的通知函数
	client_->setMessageCallback(bind(&RpcClient::onMassage, this, _1, _2, _3));
	client_->connect();
	loop_.loop();
}
#endif
// 连接回调 - 有client连接或者断开连接，该函数会调用
void RpcClient::onConnection(const TcpConnectionPtr& conn)
{
	if (conn->connected()) // 表示新连接创建
	{//连接成功，然后开始发送请求字符串，又因为请求字符串在CallMethod里，没办法在这里调用，所以需要设置回调函数

		// 连接成功，在这里执行rpc方法回调
		sendrequestCallBack(conn);
	}
	else//表示rpc框架处理完我的请求了，rpc主动断开连接了
	{
		conn->shutdown(); // 关闭连接
		loop_.quit(); // 本次rpc请求结束了 退出事件循环
	}
}
//处理服务器发送回来的消息
// 消息回调
void RpcClient::onMassage(const TcpConnectionPtr& conn,
	Buffer* buf, Timestamp time)
{
	// 这里接收rpc远程调用方法后来自server的返回值，拿到结果后你得给人家用户返回结果，
	//而用户只能拿到response所以在这里也需要设置回调,将message写到response中去
	string message = buf->retrieveAllAsString();//从网路中携带的数据封装在buf中，解析成字符串再反序列化写入response
	cout <<"response_str's message:  " <<message << endl;
    // 给用户返回RPC调用的结果
	responseCallBack(message);
}