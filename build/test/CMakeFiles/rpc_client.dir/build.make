# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/build

# Include any dependencies generated for this target.
include test/CMakeFiles/rpc_client.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/rpc_client.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/rpc_client.dir/flags.make

test/CMakeFiles/rpc_client.dir/testRpcClient.cpp.o: test/CMakeFiles/rpc_client.dir/flags.make
test/CMakeFiles/rpc_client.dir/testRpcClient.cpp.o: ../test/testRpcClient.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/rpc_client.dir/testRpcClient.cpp.o"
	cd /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rpc_client.dir/testRpcClient.cpp.o -c /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/test/testRpcClient.cpp

test/CMakeFiles/rpc_client.dir/testRpcClient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rpc_client.dir/testRpcClient.cpp.i"
	cd /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/test/testRpcClient.cpp > CMakeFiles/rpc_client.dir/testRpcClient.cpp.i

test/CMakeFiles/rpc_client.dir/testRpcClient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rpc_client.dir/testRpcClient.cpp.s"
	cd /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/test/testRpcClient.cpp -o CMakeFiles/rpc_client.dir/testRpcClient.cpp.s

test/CMakeFiles/rpc_client.dir/testRpcClient.cpp.o.requires:

.PHONY : test/CMakeFiles/rpc_client.dir/testRpcClient.cpp.o.requires

test/CMakeFiles/rpc_client.dir/testRpcClient.cpp.o.provides: test/CMakeFiles/rpc_client.dir/testRpcClient.cpp.o.requires
	$(MAKE) -f test/CMakeFiles/rpc_client.dir/build.make test/CMakeFiles/rpc_client.dir/testRpcClient.cpp.o.provides.build
.PHONY : test/CMakeFiles/rpc_client.dir/testRpcClient.cpp.o.provides

test/CMakeFiles/rpc_client.dir/testRpcClient.cpp.o.provides.build: test/CMakeFiles/rpc_client.dir/testRpcClient.cpp.o


test/CMakeFiles/rpc_client.dir/service.pb.cc.o: test/CMakeFiles/rpc_client.dir/flags.make
test/CMakeFiles/rpc_client.dir/service.pb.cc.o: ../test/service.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object test/CMakeFiles/rpc_client.dir/service.pb.cc.o"
	cd /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rpc_client.dir/service.pb.cc.o -c /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/test/service.pb.cc

test/CMakeFiles/rpc_client.dir/service.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rpc_client.dir/service.pb.cc.i"
	cd /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/test/service.pb.cc > CMakeFiles/rpc_client.dir/service.pb.cc.i

test/CMakeFiles/rpc_client.dir/service.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rpc_client.dir/service.pb.cc.s"
	cd /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/test/service.pb.cc -o CMakeFiles/rpc_client.dir/service.pb.cc.s

test/CMakeFiles/rpc_client.dir/service.pb.cc.o.requires:

.PHONY : test/CMakeFiles/rpc_client.dir/service.pb.cc.o.requires

test/CMakeFiles/rpc_client.dir/service.pb.cc.o.provides: test/CMakeFiles/rpc_client.dir/service.pb.cc.o.requires
	$(MAKE) -f test/CMakeFiles/rpc_client.dir/build.make test/CMakeFiles/rpc_client.dir/service.pb.cc.o.provides.build
.PHONY : test/CMakeFiles/rpc_client.dir/service.pb.cc.o.provides

test/CMakeFiles/rpc_client.dir/service.pb.cc.o.provides.build: test/CMakeFiles/rpc_client.dir/service.pb.cc.o


# Object files for target rpc_client
rpc_client_OBJECTS = \
"CMakeFiles/rpc_client.dir/testRpcClient.cpp.o" \
"CMakeFiles/rpc_client.dir/service.pb.cc.o"

# External object files for target rpc_client
rpc_client_EXTERNAL_OBJECTS =

../bin/rpc_client: test/CMakeFiles/rpc_client.dir/testRpcClient.cpp.o
../bin/rpc_client: test/CMakeFiles/rpc_client.dir/service.pb.cc.o
../bin/rpc_client: test/CMakeFiles/rpc_client.dir/build.make
../bin/rpc_client: ../lib/myrpc/libmyrpc.a
../bin/rpc_client: ../lib/tinyxml/libtinyxml.so
../bin/rpc_client: test/CMakeFiles/rpc_client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ../../bin/rpc_client"
	cd /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rpc_client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/rpc_client.dir/build: ../bin/rpc_client

.PHONY : test/CMakeFiles/rpc_client.dir/build

test/CMakeFiles/rpc_client.dir/requires: test/CMakeFiles/rpc_client.dir/testRpcClient.cpp.o.requires
test/CMakeFiles/rpc_client.dir/requires: test/CMakeFiles/rpc_client.dir/service.pb.cc.o.requires

.PHONY : test/CMakeFiles/rpc_client.dir/requires

test/CMakeFiles/rpc_client.dir/clean:
	cd /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/build/test && $(CMAKE_COMMAND) -P CMakeFiles/rpc_client.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/rpc_client.dir/clean

test/CMakeFiles/rpc_client.dir/depend:
	cd /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/test /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/build /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/build/test /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/build/test/CMakeFiles/rpc_client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/rpc_client.dir/depend

