#ifndef ZOOKEEPERUTILS_H
#define ZOOKEEPERUTILS_H

#include <zookeeper/zookeeper.h>
#include <string>
#include <iostream>
#include <vector>
#include <semaphore.h>
using namespace std;

class ZkClient
{
public:
	ZkClient();
	~ZkClient();
	void start();
	// zk创建节点
	void create(const char* path, const char* data, int datalen, int state = 0);

	// get znode节点的值
	string get(const char* path);

	// 发送心跳
	void sendHeartBeat();

	// 设置存放RPC服务的根节点名称
	static void setRootPath(string path);

	static string getRootPath();

	// 这个watcher是一个全局的回调。watcher是事件监听器，当有事件发生时，就会被调用
	static void global_watcher(zhandle_t* zh, int type,
		int state, const char* path, void* watcherCtx);

private:
	// zkclient和zkserver通信用的句柄
	zhandle_t* _zhandle;
	// 同步session创建成功
	static sem_t _sem;
	// 设置zk上存放RPC服务的根节点名称，代码上写死成  /RpcService不灵活
	static string _rootNodePath;
};

#endif
