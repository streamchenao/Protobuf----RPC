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
	// ���ͻ��ṩ�Ľӿڣ���RPC���ע�᱾�ط��񣬿��Է�����RPC����
	void registerService(google::protobuf::Service* service);//���serviceָ����Ǳ���userservice������󣬣� ���û�ʵ����һ�����ط���(�Ǽ̳���Service��)���뷢����RPC����ʱ�򣬾͵ð�
private:
	RpcServer(EventLoop* loop,
		const InetAddress& listenAddr,
		const string& nameArg);  //ʵ�ֳɵ���ģʽ�������캯��˽�л���

	// ���������Ӻ����ӶϿ�
	void onConnection(const TcpConnectionPtr& con);

	// �����շ���Ϣ
	void onMessage(const TcpConnectionPtr& con,Buffer* buf,Timestamp time);

	// RPC�����������Ժ���õĻص�����
	void sendResponseCallBack(const TcpConnectionPtr& con,
		google::protobuf::Message* response);

	TcpServer server_; // ���������� socketfd
	EventLoop* loop_; // �¼�ѭ��

	// ��֯service�����rpc method���񷽷�
	struct ServiceInfo
	{
		google::protobuf::Service* service;
		unordered_map<string, const google::protobuf::MethodDescriptor*> method_map;
	};
	unordered_map<string, ServiceInfo> service_map;

	static RpcServer* rpcServer_;

	//rpc���server��Ҳ��zk�Ŀͻ��ˣ�������Ҫ����һ��zk�ͻ��˵�ʵ��
	ZkClient _zkclient;
};





#endif
/*
class RPCserver
{
	//ʹ�õ���ģʽ
	RPCserver* getInstance()
	{

	}
// ��RPC���ע�᱾�ط��񣬿��Է�����RPC����
void registerService(google::protobuf::Service* service)//ָ��������
{
	// GetDescriptor���ṩ�������һЩ����   name()���ط������������    UserService  method_count()   method(i)
	
	//��serviceָ��ķ����������������
	ServiceInfo ser;
	ser.service = service;
     auto server_desc = service->GetDescriptor();//ServiceDescriptor*
	for (int i = 0; i < server_desc->; ++i)
	{
		auto meth = server_desc->method(i);//��ȡ������ķ���
		ser.method_map[meth->name()] = meth->method();
	}

	service_map[server_desc->name()] = ser;
}
// ��֯service�����rpc method���񷽷�


//protobuf�ﷴ���л����������ַ�������������з����������֣��Լ��÷��������ĸ�����ķ��������֡�

//����һ�������л��������ַ���string --����Ӧһ��������ϢServiceInfo(��������������Ͷ����о���ķ�������)

struct ServiceInfo
{
	google::protobuf::Service* service;//serviceָ����Ǿ���ķ������
	unordered_map<string, const google::protobuf::MethodDescriptor*> method_map;  //funtion1
	//������ string  --�� �������� MethodDescriptor*
};
unordered_map<string, ServiceInfo> service_map;
};
*/