#ifndef LOADXMLCONFIG
#define LOADXMLCONFIG
#include <string>
#include <iostream>
using namespace std;

// Ĭ�ϴ�rpc_config.xml�м��������������ֻ��һ�ݣ���Ƴɵ����ȽϺ�
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
	XmlConfig(const XmlConfig&) = delete;//�������죬��ֵ��������ؿ������ó�ɾ������
	XmlConfig& operator=(const XmlConfig&) = delete;
	
	string _RpcServerIP;
	unsigned short _RpcPort; // ��Ҫ�ṩ��Ӧ��get���������ⲿ��ȡ����Ӧ��ֵ
	string _ZKhost;
	int _timeout;
};

#endif
