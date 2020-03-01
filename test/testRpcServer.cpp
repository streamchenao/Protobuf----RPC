#include "rpcserver.h"
#include "service.pb.h"

//这是测试类，对于我们所写的框架的用法示例。
class UserService :public UserServiceRpc
{
public:
	//因为LService基类中有这两个函数的虚函数,因此在当前派生类中重写方法
void login(::google::protobuf::RpcController* controller,
		const ::LoginRequest* request,
		::LoginResponse* response,
		::google::protobuf::Closure* done)
	{
		// 需要在这个login的重写方法中调用本地服务的方法
		// ruquest参数将会从RPC中将客户端传递的参数带过来
		// response是需要服务器重置的、将login函数的返回值写入response中
		// done是RPC框架注册的回调函数
		string name = request->name();
		string pwd = request->pwd();
		string login_response = login(name, pwd);
		response->set_isloginsuccess(login_response);// 将本地业务login的返回值写入参数response中
		done->Run(); // 调用RPC注册的回调函数、(回调函数中是RPC对返回值如何处理)
	}
void reg(::google::protobuf::RpcController* controller,
	const ::RegRequest* request,
	::RegResponse* response,
	::google::protobuf::Closure* done)
{
	// 这个函数同理login函数
	int id = request->id();
	string name = request->name();
	string pwd = request->pwd();
	string regis_response = regist(id, name, pwd);
	response->set_isregsuccess(regis_response);
	done->Run();
}
private:
	// 原先本地的服务方法，  要将其发布成rpc方法，需要在框架的rpcserver上注册一下
	string login(string name, string pwd)
	{
		string result = "Login sucess";
		cout << "call UserService::login->";
		cout << "name:" << name << " ";
		cout << "pwd:" << pwd << endl;
		return "Login success";
	}
	string regist(int id, string name, string pwd)
	{
		cout << "call UserService::reg->";
		cout << "id:" << id << " ";
		cout << "name:" << name << " ";
		cout << "password:" << pwd << endl;
		return "Register success";
	}
};

int main()
{

	RpcServer* rs_ptr = RpcServer::getInstance(); //用户使用时，首先获取一个rpcserver实例，具体的rpcserver的创建细节不需要用户知道
	rs_ptr->registerService
	(new UserService());
	rs_ptr->run();//注册完服务，将rpcserver服务站点启动即可

	return 0;
}