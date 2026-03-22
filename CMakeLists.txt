cmake_minimum_required(VERSION 3.10)
project(AIAssistant VERSION 0.1.0 LANGUAGES C)

# 设置C标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# ARM64交叉编译
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)
set(CMAKE_C_COMPILER aarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++)

# 目录
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

include_directories(${INCLUDE_DIR})

# 主程序源文件
set(MAIN_SOURCES
    ${SOURCE_DIR}/main.c
    ${SOURCE_DIR}/core/system.c
    ${SOURCE_DIR}/core/process.c
    ${SOURCE_DIR}/core/ipc.c
    ${SOURCE_DIR}/core/storage.c
    ${SOURCE_DIR}/core/security.c
    ${SOURCE_DIR}/driver/camera/camera.c
    ${SOURCE_DIR}/driver/sensor/sensor.c
    ${SOURCE_DIR}/driver/display/display.c
    ${SOURCE_DIR}/driver/network/network.c
    ${SOURCE_DIR}/app/phone/phone.c
    ${SOURCE_DIR}/app/messaging/messaging.c
    ${SOURCE_DIR}/app/settings/settings.c
)

add_executable(ai_assistant ${MAIN_SOURCES})
target_link_libraries(ai_assistant pthread)

# 单元测试
enable_testing()

add_executable(test_core test/unit/test_core.c
    ${SOURCE_DIR}/core/process.c
    ${SOURCE_DIR}/core/ipc.c
    ${SOURCE_DIR}/core/storage.c
    ${SOURCE_DIR}/core/security.c
)
target_link_libraries(test_core pthread)

add_executable(test_ai test/unit/test_ai.c)

add_test(NAME core_test COMMAND test_core)
add_test(NAME ai_test COMMAND test_ai)

install(TARGETS ai_assistant DESTINATION bin)
