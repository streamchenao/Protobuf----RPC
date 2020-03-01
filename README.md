# myrpc
基于Google::protobuf 开发的一个RPC调用框架，网络部分采用muduo网络库，数据序列化和反序列化采用protobuf，服务配置中心采用zookeeper
Develop Language:C++语言

# 环境
需要预装muduo网络库及其依赖项boost库、protobuf、zookeeper以及tinyxml

# 项目文件介绍
bin：test文件夹测试代码生成的可执行文件  
lib：包含由RPC框架生成的静态库，可以直接进行链接使用  
build：Cmake编译生成的中间文件  
src：RPC框架源代码  
test：RPC框架测试代码  
thirdparty：第三方文件，包含第三方库等等，这里主要用到了tinyxml，用来解析xml格式的配置文件  

# 编译
项目整体采用Cmake编译，也可以在项目根目录执行下面一键编译  
./autobuild.sh  

# 运行
第一步.先启动zookeeper  
第二步.启动rpc_server，注意同级目录下需要加载配置文件rpc_cfg.xml，里面主要包含RpcServer和zookeeper的数据配置  
第三步.启动rpc_client，注意同级目录下需要加载配置文件rpc_cfg.xml，里面主要包含zookeeper的数据配置  

