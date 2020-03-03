# myrpc
基于Google::protobuf 开发的一个RPC调用框架，网络部分采用muduo网络库，数据序列化和反序列化采用protobuf，服务配置中心采用zookeeper
开发语言：C ++语言

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
项目整体采用Cmake编译，可以在build中执行cmake ..,然后再继续在lib中打包静态库，
也可以在项目根目录执行下面一键编译  ./autobuild.sh 

# 运行
第一步.先启动zookeeper 服务器 ./zkServer.sh start-foreground （可以以前台的形式启动）
第二步.启动rpc_server，注意别忘了位于同级目录下的配置文件，需要依靠配置文件的加载，来初始化zkServer和我们自己的RpcServer。     
第三步.启动rpc_client，这里也是同样的，虽然作为客户端不需要配置文件来加载ip:port，但是客户端仍然用到了zkServer，所以同样注意，需要配置文件。

