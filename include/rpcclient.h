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
	//�����û����õ�RPC���񷽷�����������ͬһ����
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
		//��ȡ�����������������
		//���û������ݽ��д��,���涨�õ����ݸ�ʽ���з�װ��ǰ4���ֽڰ��ֽ�д�������ַ�д
		MessageInfo headerInfo;
		headerInfo.set_service_name(service_name);
		headerInfo.set_method_name(method_name);

		//��servic_name��method_name�������������л�
		string header_str;
		headerInfo.SerializeToString(&header_str);

		

		string request_args_str;//����Ĳ���   service methodname args
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
	//������������ͻ�������Ϣ
	void onMassage(const TcpConnectionPtr& con, Buffer* buf, Timestamp time);

	TcpClient* client_;//����ʹ�õ���muduo��TcpClient��Ϊ���壬��������Ҫ�����������������,���а�����ip:port���Լ�eventloop����Щ��Ӧ���ڿͻ��˵Ĺ��캯���У���������û�и��ͻ���ʵ�ֹ��캯��������ֻ�ܶ����ָ��.
	EventLoop loop_;
	function<void(const TcpConnectionPtr& conn)> sendrequestCallBack;
	//Ԥ�Ʒ���rpc����Ļص�
	function<void(string str)> responseCallBack;
	//�����ͻ��˽������ݵķ���
};

#endif
//muduo�ⷢ�����ӣ��ʹ�����Ϣ����һ��