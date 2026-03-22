cmake_minimum_required(VERSION 3.10)
project(aide VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 根据架构选择编译器
if(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
    set(CMAKE_C_COMPILER aarch64-linux-gnu-gcc)
    set(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++)
    message(STATUS "Cross-compiling for ARM64")
else()
    message(STATUS "Building for host")
endif()

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
include_directories(${INCLUDE_DIR})

set(MAIN_SOURCES
    ${SOURCE_DIR}/main.c
    ${SOURCE_DIR}/core/system.c
    ${SOURCE_DIR}/core/process.c
    ${SOURCE_DIR}/core/ipc.c
    ${SOURCE_DIR}/core/storage.c
    ${SOURCE_DIR}/core/security.c
    ${SOURCE_DIR}/core/protocol/http.c
    ${SOURCE_DIR}/core/protocol/websocket.c
    ${SOURCE_DIR}/core/config/config.c
    ${SOURCE_DIR}/core/log/logger.c
    ${SOURCE_DIR}/driver/camera/camera.c
    ${SOURCE_DIR}/driver/sensor/sensor.c
    ${SOURCE_DIR}/driver/gpio/gpio.c
    ${SOURCE_DIR}/driver/display/display.c
    ${SOURCE_DIR}/driver/network/network.c
    ${SOURCE_DIR}/app/phone/phone.c
    ${SOURCE_DIR}/app/messaging/messaging.c
    ${SOURCE_DIR}/app/settings/settings.c
    ${SOURCE_DIR}/app/settings/wizard.c
    ${SOURCE_DIR}/ui/ui.c
    ${SOURCE_DIR}/ai/personality.c
    ${SOURCE_DIR}/ai/nlp/nlp.c
    ${SOURCE_DIR}/ai/vision/vision.c
    ${SOURCE_DIR}/ai/memory/user_memory.c
    ${SOURCE_DIR}/ai/speech/voice.c
    ${SOURCE_DIR}/ai/model/local_model.c
    ${SOURCE_DIR}/simulator/simulator.c
)

add_executable(aide ${MAIN_SOURCES})
target_link_libraries(aide pthread)

install(TARGETS aide DESTINATION bin)
