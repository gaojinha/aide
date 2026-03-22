cmake_minimum_required(VERSION 3.10)
project(AIAssistant VERSION 0.1.0 LANGUAGES C)

# 设置C标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 设置目标架构为ARM64
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

# 交叉编译工具链
set(CMAKE_C_COMPILER aarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++)

# 源码目录
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# 头文件路径
include_directories(${INCLUDE_DIR})

# 源文件列表
set(SOURCES
    ${SOURCE_DIR}/main.c
    ${SOURCE_DIR}/core/system.c
)

# 创建可执行文件
add_executable(ai_assistant ${SOURCES})

# 链接库
target_link_libraries(ai_assistant pthread)

# 安装
install(TARGETS ai_assistant DESTINATION bin)
