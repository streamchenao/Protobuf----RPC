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
include thirdparty/tinyxml/CMakeFiles/tinyxml.dir/depend.make

# Include the progress variables for this target.
include thirdparty/tinyxml/CMakeFiles/tinyxml.dir/progress.make

# Include the compile flags for this target's objects.
include thirdparty/tinyxml/CMakeFiles/tinyxml.dir/flags.make

thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinystr.cpp.o: thirdparty/tinyxml/CMakeFiles/tinyxml.dir/flags.make
thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinystr.cpp.o: ../thirdparty/tinyxml/tinystr.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinystr.cpp.o"
	cd /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/build/thirdparty/tinyxml && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tinyxml.dir/tinystr.cpp.o -c /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/thirdparty/tinyxml/tinystr.cpp

thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinystr.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tinyxml.dir/tinystr.cpp.i"
	cd /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/build/thirdparty/tinyxml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/thirdparty/tinyxml/tinystr.cpp > CMakeFiles/tinyxml.dir/tinystr.cpp.i

thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinystr.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tinyxml.dir/tinystr.cpp.s"
	cd /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/build/thirdparty/tinyxml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/thirdparty/tinyxml/tinystr.cpp -o CMakeFiles/tinyxml.dir/tinystr.cpp.s

thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinystr.cpp.o.requires:

.PHONY : thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinystr.cpp.o.requires

thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinystr.cpp.o.provides: thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinystr.cpp.o.requires
	$(MAKE) -f thirdparty/tinyxml/CMakeFiles/tinyxml.dir/build.make thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinystr.cpp.o.provides.build
.PHONY : thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinystr.cpp.o.provides

thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinystr.cpp.o.provides.build: thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinystr.cpp.o


thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxml.cpp.o: thirdparty/tinyxml/CMakeFiles/tinyxml.dir/flags.make
thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxml.cpp.o: ../thirdparty/tinyxml/tinyxml.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxml.cpp.o"
	cd /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/build/thirdparty/tinyxml && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tinyxml.dir/tinyxml.cpp.o -c /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/thirdparty/tinyxml/tinyxml.cpp

thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxml.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tinyxml.dir/tinyxml.cpp.i"
	cd /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/build/thirdparty/tinyxml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/thirdparty/tinyxml/tinyxml.cpp > CMakeFiles/tinyxml.dir/tinyxml.cpp.i

thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxml.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tinyxml.dir/tinyxml.cpp.s"
	cd /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/build/thirdparty/tinyxml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/thirdparty/tinyxml/tinyxml.cpp -o CMakeFiles/tinyxml.dir/tinyxml.cpp.s

thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxml.cpp.o.requires:

.PHONY : thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxml.cpp.o.requires

thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxml.cpp.o.provides: thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxml.cpp.o.requires
	$(MAKE) -f thirdparty/tinyxml/CMakeFiles/tinyxml.dir/build.make thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxml.cpp.o.provides.build
.PHONY : thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxml.cpp.o.provides

thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxml.cpp.o.provides.build: thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxml.cpp.o


thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxmlerror.cpp.o: thirdparty/tinyxml/CMakeFiles/tinyxml.dir/flags.make
thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxmlerror.cpp.o: ../thirdparty/tinyxml/tinyxmlerror.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxmlerror.cpp.o"
	cd /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/build/thirdparty/tinyxml && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tinyxml.dir/tinyxmlerror.cpp.o -c /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/thirdparty/tinyxml/tinyxmlerror.cpp

thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxmlerror.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tinyxml.dir/tinyxmlerror.cpp.i"
	cd /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/build/thirdparty/tinyxml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/thirdparty/tinyxml/tinyxmlerror.cpp > CMakeFiles/tinyxml.dir/tinyxmlerror.cpp.i

thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxmlerror.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tinyxml.dir/tinyxmlerror.cpp.s"
	cd /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/build/thirdparty/tinyxml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/thirdparty/tinyxml/tinyxmlerror.cpp -o CMakeFiles/tinyxml.dir/tinyxmlerror.cpp.s

thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxmlerror.cpp.o.requires:

.PHONY : thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxmlerror.cpp.o.requires

thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxmlerror.cpp.o.provides: thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxmlerror.cpp.o.requires
	$(MAKE) -f thirdparty/tinyxml/CMakeFiles/tinyxml.dir/build.make thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxmlerror.cpp.o.provides.build
.PHONY : thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxmlerror.cpp.o.provides

thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxmlerror.cpp.o.provides.build: thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxmlerror.cpp.o


thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxmlparser.cpp.o: thirdparty/tinyxml/CMakeFiles/tinyxml.dir/flags.make
thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxmlparser.cpp.o: ../thirdparty/tinyxml/tinyxmlparser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxmlparser.cpp.o"
	cd /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/build/thirdparty/tinyxml && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tinyxml.dir/tinyxmlparser.cpp.o -c /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/thirdparty/tinyxml/tinyxmlparser.cpp

thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxmlparser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tinyxml.dir/tinyxmlparser.cpp.i"
	cd /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/build/thirdparty/tinyxml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/thirdparty/tinyxml/tinyxmlparser.cpp > CMakeFiles/tinyxml.dir/tinyxmlparser.cpp.i

thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxmlparser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tinyxml.dir/tinyxmlparser.cpp.s"
	cd /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/build/thirdparty/tinyxml && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/thirdparty/tinyxml/tinyxmlparser.cpp -o CMakeFiles/tinyxml.dir/tinyxmlparser.cpp.s

thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxmlparser.cpp.o.requires:

.PHONY : thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxmlparser.cpp.o.requires

thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxmlparser.cpp.o.provides: thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxmlparser.cpp.o.requires
	$(MAKE) -f thirdparty/tinyxml/CMakeFiles/tinyxml.dir/build.make thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxmlparser.cpp.o.provides.build
.PHONY : thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxmlparser.cpp.o.provides

thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxmlparser.cpp.o.provides.build: thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxmlparser.cpp.o


# Object files for target tinyxml
tinyxml_OBJECTS = \
"CMakeFiles/tinyxml.dir/tinystr.cpp.o" \
"CMakeFiles/tinyxml.dir/tinyxml.cpp.o" \
"CMakeFiles/tinyxml.dir/tinyxmlerror.cpp.o" \
"CMakeFiles/tinyxml.dir/tinyxmlparser.cpp.o"

# External object files for target tinyxml
tinyxml_EXTERNAL_OBJECTS =

../lib/tinyxml/libtinyxml.so: thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinystr.cpp.o
../lib/tinyxml/libtinyxml.so: thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxml.cpp.o
../lib/tinyxml/libtinyxml.so: thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxmlerror.cpp.o
../lib/tinyxml/libtinyxml.so: thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxmlparser.cpp.o
../lib/tinyxml/libtinyxml.so: thirdparty/tinyxml/CMakeFiles/tinyxml.dir/build.make
../lib/tinyxml/libtinyxml.so: thirdparty/tinyxml/CMakeFiles/tinyxml.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX shared library ../../../lib/tinyxml/libtinyxml.so"
	cd /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/build/thirdparty/tinyxml && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tinyxml.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
thirdparty/tinyxml/CMakeFiles/tinyxml.dir/build: ../lib/tinyxml/libtinyxml.so

.PHONY : thirdparty/tinyxml/CMakeFiles/tinyxml.dir/build

thirdparty/tinyxml/CMakeFiles/tinyxml.dir/requires: thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinystr.cpp.o.requires
thirdparty/tinyxml/CMakeFiles/tinyxml.dir/requires: thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxml.cpp.o.requires
thirdparty/tinyxml/CMakeFiles/tinyxml.dir/requires: thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxmlerror.cpp.o.requires
thirdparty/tinyxml/CMakeFiles/tinyxml.dir/requires: thirdparty/tinyxml/CMakeFiles/tinyxml.dir/tinyxmlparser.cpp.o.requires

.PHONY : thirdparty/tinyxml/CMakeFiles/tinyxml.dir/requires

thirdparty/tinyxml/CMakeFiles/tinyxml.dir/clean:
	cd /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/build/thirdparty/tinyxml && $(CMAKE_COMMAND) -P CMakeFiles/tinyxml.dir/cmake_clean.cmake
.PHONY : thirdparty/tinyxml/CMakeFiles/tinyxml.dir/clean

thirdparty/tinyxml/CMakeFiles/tinyxml.dir/depend:
	cd /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/thirdparty/tinyxml /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/build /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/build/thirdparty/tinyxml /home/chen/projects/RPCserver/我的代码/RPC分布式网络通信/RPCtest/RPC--git/build/thirdparty/tinyxml/CMakeFiles/tinyxml.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : thirdparty/tinyxml/CMakeFiles/tinyxml.dir/depend

