#ifndef RPCSERVER_H
#define RPCSERVER_H

#include<iostream>
#include<unordered_map>
#include<string>
using namespace std;
#include "google/protobuf/service.h"
#include "rpcserver.pb.h"
#include<muduo/net/TcpServer.h>
#include<muduo/net/EventLoop.h>
#include<muduo/base/Logging.h>
#include"zookeeperutil.h"
using namespace muduo;
using namespace muduo::net;
using namespace google::protobuf;
using namespace placeholders;


class RpcServer
{
public:
	static RpcServer* getInstance();
	void run();
	/*
	// "UserService" + "login" + args
	*/
	// 给客户提供的接口，向RPC框架注册本地服务，可以发布成RPC服务。
	void registerService(google::protobuf::Service* service);//这个service指向的是本地userservice服务对象，， 当用户实现了一个本地服务(是继承自Service的)，想发布成RPC服务时候，就得把
private:
	RpcServer(EventLoop* loop,
		const InetAddress& listenAddr,
		const string& nameArg);  //实现成单例模式，将构造函数私有化。

	// 处理新连接和连接断开
	void onConnection(const TcpConnectionPtr& con);

	// 处理收发消息
	void onMessage(const TcpConnectionPtr& con,Buffer* buf,Timestamp time);

	// RPC方法处理完以后调用的回调方法
	void sendResponseCallBack(const TcpConnectionPtr& con,
		google::protobuf::Message* response);

	TcpServer server_; // 服务器对象 socketfd
	EventLoop* loop_; // 事件循环

	// 组织service对象和rpc method服务方法
	struct ServiceInfo
	{
		google::protobuf::Service* service;
		unordered_map<string, const google::protobuf::MethodDescriptor*> method_map;
	};
	unordered_map<string, ServiceInfo> service_map;

	static RpcServer* rpcServer_;

	//rpc框架server端也是zk的客户端，所以需要创建一个zk客户端的实例
	ZkClient _zkclient;
};





#endif
/*
class RPCserver
{
	//使用单例模式
	RPCserver* getInstance()
	{

	}
// 向RPC框架注册本地服务，可以发布成RPC服务
void registerService(google::protobuf::Service* service)//指向服务对象
{
	// GetDescriptor中提供了下面的一些方法   name()返回方法对象的名字    UserService  method_count()   method(i)
	
	//往service指向的服务对象里面填内容
	ServiceInfo ser;
	ser.service = service;
     auto server_desc = service->GetDescriptor();//ServiceDescriptor*
	for (int i = 0; i < server_desc->; ++i)
	{
		auto meth = server_desc->method(i);//获取到具体的方法
		ser.method_map[meth->name()] = meth->method();
	}

	service_map[server_desc->name()] = ser;
}
// 组织service对象和rpc method服务方法


//protobuf里反序列化出来的是字符串，里面包含有服务对象的名字，以及该服务对象的哪个具体的方法的名字。

//所以一个反序列化出来的字符串string --》对应一个服务信息ServiceInfo(包括服务对象名和对象中具体的方法描述)

struct ServiceInfo
{
	google::protobuf::Service* service;//service指向的是具体的服务对象
	unordered_map<string, const google::protobuf::MethodDescriptor*> method_map;  //funtion1
	//方法名 string  --》 方法描述 MethodDescriptor*
};
unordered_map<string, ServiceInfo> service_map;
};
*/