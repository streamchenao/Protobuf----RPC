#ifndef RPCCLIENT_H
#define RPCCLIENT_H
#include "google/protobuf/service.h"
#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpClient.h>
#include<iostream>
#include<string>
#include<functional>
#include <thread>
#include "rpcserver.pb.h"

using namespace std;
using namespace placeholders;
using namespace muduo;
using namespace muduo::net;
using namespace google::protobuf;

class RpcClient :public RpcChannel
{
public:
	RpcClient();
	~RpcClient();
	//所有用户调用的RPC服务方法，都在这里同一处理
	void CallMethod(const MethodDescriptor* method,
		RpcController* controller, const Message* request,
		Message* response, Closure* done);
	/*void CallMethod(const MethodDescriptor* method,
		RpcController* controller, const Message* request,
		Message* response, Closure* done)
	{
		auto service = method->service();
		string service_name = service->name();
		string method_name=method->name();
		//获取服务对象名，方法名
		//将用户的数据进行打包,按规定好的数据格式进行封装，前4个字节按字节写，不按字符写
		MessageInfo headerInfo;
		headerInfo.set_service_name(service_name);
		headerInfo.set_method_name(method_name);

		//将servic_name和method_name这两个参数序列化
		string header_str;
		headerInfo.SerializeToString(&header_str);

		

		string request_args_str;//请求的参数   service methodname args
		request->SerializeToString(&request_args_str);
		
		string request_send_str;
		request_send_str.insert(0, string((char*)& request_send_str, 4));
		request_send_str += header_str;
		request_send_str += request_args_str;


		sendRpcCallBack = [&](const TcpConnectionPtr& con) {
			con->send(request_send_str); };

		client_ = new TcpClient(&loop_, InetAddress("127.0.0.1", 6000),"");

	}*/
private:
	void onConnection(const TcpConnectionPtr& con);
	//处理服务器发送回来的消息
	void onMassage(const TcpConnectionPtr& con, Buffer* buf, Timestamp time);

	TcpClient* client_;//这里使用的是muduo的TcpClient作为载体，但是其需要三个参数来构造对象,其中包括了ip:port，以及eventloop，这些本应该在客户端的构造函数中，但是我们没有给客户端实现构造函数，所以只能定义成指针.
	EventLoop loop_;
	function<void(const TcpConnectionPtr& conn)> sendrequestCallBack;
	//预制发送rpc请求的回调
	function<void(string str)> responseCallBack;
	//启动客户端进行数据的发送
};

#endif
//muduo库发起连接，和处理消息不在一起