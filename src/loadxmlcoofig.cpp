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
		//��ȡ����RpcServerͬ���Ľڵ�ָ�룬nullptrָ���Ǵ�previous(����ǰ�ڵ��ǰһ��)�ڵ�Ϊnullpter���Ǹ��ڵ㿪ʼ��˵���ǴӸ��ڵ㿪ʼ����
		const TiXmlNode* node = loadXMLcnf.RootElement()->IterateChildren("RpcServer", nullptr);
		const TiXmlNode* node_cnf = nullptr;
		// rpc clientû��RpcServer������
		if (node != nullptr)
		{
			node_cnf = node->IterateChildren("ip", nullptr);//�Ӹ��ڵ㿪ʼ�������ҵ���Ϊip�Ľڵ㣬����ȡ����ֵ
			_RpcServerIP = node_cnf->ToElement()->GetText();//����ֵ��const char *
			node_cnf = node->IterateChildren("port", nullptr);
			_RpcPort = atoi(node_cnf->ToElement()->GetText());
		}

		// rpc server��rpc client����zookeeper������
		node = loadXMLcnf.RootElement()->IterateChildren("zookeeper", nullptr);
		node_cnf = node->IterateChildren("host", nullptr);
		_ZKhost = node_cnf->ToElement()->GetText();
		node_cnf = node->IterateChildren("timeout", nullptr);
		_timeout = atoi(node_cnf->ToElement()->GetText());

		cout << "load rpc_cfg.xml success...����������" << endl;
	}
}