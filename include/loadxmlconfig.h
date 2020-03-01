#ifndef LOADXMLCONFIG
#define LOADXMLCONFIG
#include <string>
#include <iostream>
using namespace std;

// 默认从rpc_config.xml中加载配置项，配置项只有一份，设计成单例比较好
class XmlConfig
{
public:
	static XmlConfig& getInstance();

	string getZookeeperHost();
	int getTimeout();

	string getRpcServerIp();
	unsigned short getRpcServerPort();
private:
	XmlConfig();
	XmlConfig(const XmlConfig&) = delete;//拷贝构造，赋值运算符重载可以设置成删除函数
	XmlConfig& operator=(const XmlConfig&) = delete;
	
	string _RpcServerIP;
	unsigned short _RpcPort; // 需要提供相应的get方法，让外部获取到相应的值
	string _ZKhost;
	int _timeout;
};

#endif
