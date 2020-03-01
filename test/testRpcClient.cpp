#include "rpcclient.h"
#include "service.pb.h"
#include<iostream>
#include<string>
using namespace std;
int main()
{
	UserServiceRpc_Stub stub(new RpcClient());//UserServiceRpc_Stub是由用户所写的protobuf文件中service生成的给client使用的类
	LoginRequest request;
	//客户端登陆需要参数
	request.set_name("chen");
	request.set_pwd("111111");
	LoginResponse response;
	stub.login(nullptr,&request,&response,nullptr);

	string result;
	response.ParseFromString(result);

	cout << "From Server response: " << result << endl;
	return 0;
}