#include "rpcserver.h"
#include "service.pb.h"

//���ǲ����࣬����������д�Ŀ�ܵ��÷�ʾ����
class UserService :public UserServiceRpc
{
public:
	//��ΪLService���������������������麯��,����ڵ�ǰ����������д����
void login(::google::protobuf::RpcController* controller,
		const ::LoginRequest* request,
		::LoginResponse* response,
		::google::protobuf::Closure* done)
	{
		// ��Ҫ�����login����д�����е��ñ��ط���ķ���
		// ruquest���������RPC�н��ͻ��˴��ݵĲ���������
		// response����Ҫ���������õġ���login�����ķ���ֵд��response��
		// done��RPC���ע��Ļص�����
		string name = request->name();
		string pwd = request->pwd();
		string login_response = login(name, pwd);
		response->set_isloginsuccess(login_response);// ������ҵ��login�ķ���ֵд�����response��
		done->Run(); // ����RPCע��Ļص�������(�ص���������RPC�Է���ֵ��δ���)
	}
void reg(::google::protobuf::RpcController* controller,
	const ::RegRequest* request,
	::RegResponse* response,
	::google::protobuf::Closure* done)
{
	// �������ͬ��login����
	int id = request->id();
	string name = request->name();
	string pwd = request->pwd();
	string regis_response = regist(id, name, pwd);
	response->set_isregsuccess(regis_response);
	done->Run();
}
private:
	// ԭ�ȱ��صķ��񷽷���  Ҫ���䷢����rpc��������Ҫ�ڿ�ܵ�rpcserver��ע��һ��
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

	RpcServer* rs_ptr = RpcServer::getInstance(); //�û�ʹ��ʱ�����Ȼ�ȡһ��rpcserverʵ���������rpcserver�Ĵ���ϸ�ڲ���Ҫ�û�֪��
	rs_ptr->registerService
	(new UserService());
	rs_ptr->run();//ע������񣬽�rpcserver����վ����������

	return 0;
}