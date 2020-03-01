#include "zookeeperutil.h"
#include "loadxmlconfig.h"
#include <thread>
#include <chrono>
using namespace std;

sem_t ZkClient::_sem;
string ZkClient::_rootNodePath = "/RpcService";

ZkClient::ZkClient()
	:_zhandle(nullptr)
{
	sem_init(&_sem, 0, 0);
}
//����ǰѹ��캯����Ƶļ򵥵㣬������Ҫ�����ܷ����쳣�Ĵ���д�ڹ��캯����
ZkClient::~ZkClient()
{
	sem_destroy(&_sem);//�����ź���
	if (_zhandle != nullptr)
	{
		zookeeper_close(_zhandle);
	}

}



// �����ṩ���û��Ľӿڣ����û��������ô��RPC����ĸ��ڵ�����
void ZkClient::setRootPath(string path)
{
	_rootNodePath = path;
}

string ZkClient::getRootPath()
{
	return _rootNodePath;
}

void ZkClient::start()
{
	// zookeeper_init()���ӵ�zkServer��������session��һ���첽�Ĺ��̡��������Ӻ󣬼�������ִ�У����õȴ����ӵĽ����ú��������ִ�С������ӽ����ɹ�֮�����˻᷵�أ�����������ע��õ�watcher��
	//��ȡ�����ļ��е���Ϣ
	const char* host = XmlConfig::getInstance().getZookeeperHost().c_str();
	auto timeout = XmlConfig::getInstance().getTimeout();//

	_zhandle = zookeeper_init(host, global_watcher,timeout, nullptr, nullptr, 0); //��ʾ��������
	//zookeeper_init�ķ���ֵ�����ܴ������ӳɹ���������ʧ�ܣ�����������ص��ǿ�ָ��֤��һ��������ʧ�ܵ�
	if (_zhandle == nullptr)
	{
		cout << "connecting zookeeper server error..." << endl;
		exit(EXIT_FAILURE);
	}
	// �����ȴ����ӳɹ����ٷ���   sem_wait��Ӧ��P��������Դ����-1�Ĳ��� 
	sem_wait(&_sem);//��Դ������ʼ����0���ò�����Դ������������������ȴ������߳�֪ͨ��ص���.ȷ�����Ӽ����ͻ��������ִ��
	cout << "connecting zookeeper success..." << endl;
}

// zk�����ڵ�  zk�Ϲ���Ľڵ���znodeҲ���Ǹ��ָ�����·��
void ZkClient::create(const char* path, const char* data, int datalen, int state)//�ڵ�·�������ݣ����ݳ��ȣ��ڵ�״̬(E/P)
{
	char path_buffer[128];
	int bufferlen = sizeof(path_buffer);
	// �ж�znode�ڵ��Ƿ���ڣ������ڴ���
	int flag;
	flag = zoo_exists(_zhandle, path, 0, nullptr);//������������watch 0��ʾ��֪ͨwatcher 1��ʾ֪ͨ.��watch�ĵط����ᱻ�ص�����ͨ��state�������������¼���
	
	if (ZNONODE == flag)
	{
		// ��ʾ��znode�ڵ㲻����ʱ���ʹ�����ʱ�ڵ�
		flag = zoo_create(_zhandle, path, data, datalen,
			&ZOO_OPEN_ACL_UNSAFE, state, path_buffer, bufferlen);
		if (flag == ZOK)
		{
			cout << "znode create success... path:" << path << endl;
		}
		else
		{
			cout << "flag:" << flag << endl;
			cout << "znode create error... path:" << path << endl;
			exit(EXIT_FAILURE);
		}
	}
}

// get znode�ڵ��ֵ,ʵ����Ҳ����һ��path�ַ�������rpcclient��ȡ��֮����Ҫ����path�е�ip��port
string ZkClient::get(const char* path)
{
	char buffer[64];
	int bufferlen = sizeof(buffer);
	int flag = zoo_get(_zhandle, path, 0, buffer, &bufferlen, nullptr);//���е�zk�йص�API��Ҫ����_zhandle���������
	if (flag != ZOK)//û�鵽��Ϊservice_name�Ľڵ�
	{
		cout << "get znode error... path:" << path << endl;
		return "";
	}
	else
	{
		return buffer;
	}
}

// ���������������÷���ʲô���ݣ��򵥽��н�������
void ZkClient::sendHeartBeat()
{
	//rpcserver��������������һ����ѭ�������ģ�������Ҫ�ٵ�������һ���߳�����
	// �����̷߳���zk������ά��session
	thread t([&]() {
		for (;;)
		{
			// ����ʱ������Ϊtimeoutʱ���1/3
			auto timeout = XmlConfig::getInstance().getTimeout();
			int time = timeout * 1.0 / 3;
			this_thread::sleep_for(chrono::seconds(time));
			//�򵥽�������������������鿴һ�¸��ڵ��״̬
			zoo_exists(_zhandle, _rootNodePath.c_str(), 0, nullptr);
		}
		});
	t.detach();
}

//�������ø��ּ����watcher

// ���watcher��ȫ�ֵĻص�,����zkclient�����ǵ��ã�����ֻ��Ҫ���ü��ɡ�ֻҪ���ڵ���б䶯����ʱ��zkclient�ͻ������ǵ���
void ZkClient::global_watcher(zhandle_t* zh, int type,
	int state, const char* path, void* watcherCtx)
{
	cout << "watcher type:" << type << endl;
	cout << "watcher state:" << state << endl;
	if (type == ZOO_SESSION_EVENT) // ��session�Ự�йص��¼�
	{
		if (state == ZOO_CONNECTED_STATE) // session�����ɹ���,Ҳ�ͱ�ʾ���ӳɹ���
		{
			sem_post(&_sem); // ���ź�������Դ����+1��֪ͨ�����߳����ӳɹ�,�����������ӳɹ��Ժ���ܴ����ڵ�
		}
		else if (state == ZOO_EXPIRED_SESSION_STATE) // ��ʾsession��ʱ���ỰʧЧ
		{
			cout << "this session is timeout" << endl;
		}
	}
}