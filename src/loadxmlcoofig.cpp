#include "loadxmlconfig.h"
#include "tinyxml.h"

XmlConfig& XmlConfig::getInstance()
{
	static XmlConfig xml;
	return xml;
}
string XmlConfig::getZookeeperHost()
{
	return _ZKhost;
}
string XmlConfig::getRpcServerIp()
{
	return _RpcServerIP;
}
unsigned short XmlConfig::getRpcServerPort()
{
	return _RpcPort;
}
int XmlConfig::getTimeout()
{
	return _timeout;
}

XmlConfig::XmlConfig()
{
	TiXmlDocument loadXMLcnf;
	if (!loadXMLcnf.LoadFile("rpc_cfg.xml"))
	{
		cout << "load zookeeper config file error...Please check rpc_cfg.xml is right?" << endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		//获取到与RpcServer同名的节点指针，nullptr指明是从previous(即当前节点的前一个)节点为nullpter的那个节点开始，说明是从根节点开始遍历
		const TiXmlNode* node = loadXMLcnf.RootElement()->IterateChildren("RpcServer", nullptr);
		const TiXmlNode* node_cnf = nullptr;
		// rpc client没有RpcServer配置项
		if (node != nullptr)
		{
			node_cnf = node->IterateChildren("ip", nullptr);//从根节点开始遍历，找到名为ip的节点，并获取它的值
			_RpcServerIP = node_cnf->ToElement()->GetText();//返回值是const char *
			node_cnf = node->IterateChildren("port", nullptr);
			_RpcPort = atoi(node_cnf->ToElement()->GetText());
		}

		// rpc server和rpc client都有zookeeper配置项
		node = loadXMLcnf.RootElement()->IterateChildren("zookeeper", nullptr);
		node_cnf = node->IterateChildren("host", nullptr);
		_ZKhost = node_cnf->ToElement()->GetText();
		node_cnf = node->IterateChildren("timeout", nullptr);
		_timeout = atoi(node_cnf->ToElement()->GetText());

		cout << "load rpc_cfg.xml success...！！！！！" << endl;
	}
}