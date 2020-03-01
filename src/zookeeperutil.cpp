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
//最好是把构造函数设计的简单点，尽量不要将可能发生异常的代码写在构造函数中
ZkClient::~ZkClient()
{
	sem_destroy(&_sem);//销毁信号量
	if (_zhandle != nullptr)
	{
		zookeeper_close(_zhandle);
	}

}



// 可以提供给用户的接口：让用户随意设置存放RPC服务的根节点名称
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
	// zookeeper_init()连接到zkServer并创建好session是一个异步的过程。发起连接后，继续往下执行，不用等待连接的建立好后才能往下执行。当连接建立成功之后服务端会返回，并调用事先注册好的watcher。
	//读取配置文件中的信息
	const char* host = XmlConfig::getInstance().getZookeeperHost().c_str();
	auto timeout = XmlConfig::getInstance().getTimeout();//

	_zhandle = zookeeper_init(host, global_watcher,timeout, nullptr, nullptr, 0); //表示发起连接
	//zookeeper_init的返回值并不能代表连接成功或者连接失败，但是如果返回的是空指针证明一定是连接失败的
	if (_zhandle == nullptr)
	{
		cout << "connecting zookeeper server error..." << endl;
		exit(EXIT_FAILURE);
	}
	// 阻塞等待连接成功，再返回   sem_wait对应与P操作对资源计数-1的操作 
	sem_wait(&_sem);//资源计数初始化是0，拿不到资源，所以阻塞在这儿。等待调用线程通知完回调后.确认连接简历就会继续往下执行
	cout << "connecting zookeeper success..." << endl;
}

// zk创建节点  zk上管理的节点是znode也就是各种各样的路径
void ZkClient::create(const char* path, const char* data, int datalen, int state)//节点路径，数据，数据长度，节点状态(E/P)
{
	char path_buffer[128];
	int bufferlen = sizeof(path_buffer);
	// 判断znode节点是否存在，不能在创建
	int flag;
	flag = zoo_exists(_zhandle, path, 0, nullptr);//第三个参数是watch 0表示不通知watcher 1表示通知.有watch的地方都会被回调，是通过state来区分是哪种事件的
	
	if (ZNONODE == flag)
	{
		// 表示当znode节点不存在时，就创建临时节点
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

// get znode节点的值,实际上也就是一个path字符串，当rpcclient获取到之后，需要分离path中的ip和port
string ZkClient::get(const char* path)
{
	char buffer[64];
	int bufferlen = sizeof(buffer);
	int flag = zoo_get(_zhandle, path, 0, buffer, &bufferlen, nullptr);//所有的zk有关的API都要依赖_zhandle句柄来调用
	if (flag != ZOK)//没查到名为service_name的节点
	{
		cout << "get znode error... path:" << path << endl;
		return "";
	}
	else
	{
		return buffer;
	}
}

// 发送心跳包，不用发送什么数据，简单进行交互就行
void ZkClient::sendHeartBeat()
{
	//rpcserver发送心跳包是用一个死循环来做的，所以需要再单独开启一个线程来做
	// 启动线程发送zk心跳，维护session
	thread t([&]() {
		for (;;)
		{
			// 心跳时间设置为timeout时间的1/3
			auto timeout = XmlConfig::getInstance().getTimeout();
			int time = timeout * 1.0 / 3;
			this_thread::sleep_for(chrono::seconds(time));
			//简单交互由这个函数来做，查看一下根节点的状态
			zoo_exists(_zhandle, _rootNodePath.c_str(), 0, nullptr);
		}
		});
	t.detach();
}

//可以设置各种级别的watcher

// 这个watcher是全局的回调,是由zkclient替我们调用，我们只需要设置即可。只要当节点的有变动发生时，zkclient就会替我们调用
void ZkClient::global_watcher(zhandle_t* zh, int type,
	int state, const char* path, void* watcherCtx)
{
	cout << "watcher type:" << type << endl;
	cout << "watcher state:" << state << endl;
	if (type == ZOO_SESSION_EVENT) // 与session会话有关的事件
	{
		if (state == ZOO_CONNECTED_STATE) // session创建成功了,也就表示连接成功了
		{
			sem_post(&_sem); // 给信号量的资源计数+1，通知调用线程连接成功,真真正正连接成功以后才能创建节点
		}
		else if (state == ZOO_EXPIRED_SESSION_STATE) // 表示session超时，会话失效
		{
			cout << "this session is timeout" << endl;
		}
	}
}