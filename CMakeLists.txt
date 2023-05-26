# cmake最低版本要求
cmake_minimum_required(VERSION 3.7)

# 设置工程的名字，生成的可执行文件也将使用该名称，如net.exe
project(net)
set(CMAKE_C_STANDARD 99)

# 头文件搜索路径，使得c文件中可以直接使用#include "xxx.h"，而不必加前缀
include_directories(
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/include
)

# 搜索src下面的所有源文件，生成文件列表
file(GLOB_RECURSE SOURCE_LIST  "src/*.c" "include/*.h")

# 将源文件列表加入到工程中
add_executable(${PROJECT_NAME} ${SOURCE_LIST})

# 与一些库进行编译链接，生成最终的程序
message(STATUS "current platform: ${CMAKE_HOST_SYSTEM_NAME}")
if(CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
    add_definitions(-DSYS_PLAT_WINDOWS)
    target_link_libraries(${PROJECT_NAME} wpcap packet Ws2_32)
else()
    # Linux和Mac上的特定配置
    add_definitions(-DSYS_PLAT_LINUX)
    target_link_libraries(${PROJECT_NAME} pthread pcap)
endif()


