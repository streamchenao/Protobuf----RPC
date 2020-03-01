include_directories(${PROJECT_SOURCE_DIR}/thirdparty/tinyxml)
include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib/tinyxml)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib/myrpc) 


aux_source_directory(. SRC_)
add_library(myrpc  ${SRC_})
target_link_libraries(myrpc muduo_net muduo_base protobuf zookeeper_mt pthread tinyxml)