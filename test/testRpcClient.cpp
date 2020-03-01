#include "rpcclient.h"
#include "service.pb.h"
#include<iostream>
#include<string>
using namespace std;
int main()
{
	UserServiceRpc_Stub stub(new RpcClient());//UserServiceRpc_Stub�����û���д��protobuf�ļ���service���ɵĸ�clientʹ�õ���
	LoginRequest request;
	//�ͻ��˵�½��Ҫ����
	request.set_name("chen");
	request.set_pwd("111111");
	LoginResponse response;
	stub.login(nullptr,&request,&response,nullptr);

	string result;
	response.ParseFromString(result);

	cout << "From Server response: " << result << endl;
	return 0;
}