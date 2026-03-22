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
    ${SOURCE_DIR}/core/error/error.c
    ${SOURCE_DIR}/core/performance/performance.c
    ${SOURCE_DIR}/core/watchdog/watchdog.c
    ${SOURCE_DIR}/core/power_mgmt/power_mgmt.c
    ${SOURCE_DIR}/core/power_stats/power_stats.c
    ${SOURCE_DIR}/core/firmware/firmware.c
    ${SOURCE_DIR}/core/unit_test/unit_test.c
    ${SOURCE_DIR}/core/remote_log/remote_log.c
    ${SOURCE_DIR}/core/backup/backup.c
    ${SOURCE_DIR}/core/debug/debug.c
    ${SOURCE_DIR}/core/monitor/monitor.c
    ${SOURCE_DIR}/core/recovery/recovery.c
    ${SOURCE_DIR}/core/logrotate/logrotate.c
    ${SOURCE_DIR}/core/performance/mempool.c
    ${SOURCE_DIR}/core/performance/threadpool.c
    ${SOURCE_DIR}/core/performance/cache.c
    ${SOURCE_DIR}/core/auth.c
    ${SOURCE_DIR}/core/acl.c
    ${SOURCE_DIR}/core/biometric/biometric.c
    ${SOURCE_DIR}/core/secureboot.c
    ${SOURCE_DIR}/core/secure_storage.c
    ${SOURCE_DIR}/core/firewall.c
    ${SOURCE_DIR}/core/process.c
    ${SOURCE_DIR}/core/ipc.c
    ${SOURCE_DIR}/core/storage.c
    ${SOURCE_DIR}/core/security.c
    ${SOURCE_DIR}/core/protocol/http.c
    ${SOURCE_DIR}/core/protocol/websocket.c
    ${SOURCE_DIR}/core/config/config.c
    ${SOURCE_DIR}/core/log/logger.c
    ${SOURCE_DIR}/core/ntp/ntp.c
    ${SOURCE_DIR}/core/ota/ota.c
    ${SOURCE_DIR}/driver/camera/camera.c
    ${SOURCE_DIR}/driver/sensor/sensor.c
    ${SOURCE_DIR}/driver/gpio/gpio.c
    ${SOURCE_DIR}/driver/wifi/wifi.c
    ${SOURCE_DIR}/driver/bluetooth/bluetooth.c
    ${SOURCE_DIR}/driver/audio/audio.c
    ${SOURCE_DIR}/driver/video/video.c
    ${SOURCE_DIR}/driver/power/power.c
    ${SOURCE_DIR}/driver/ir/ir.c
    ${SOURCE_DIR}/driver/network/network_diag.c
    ${SOURCE_DIR}/driver/display/display.c
    ${SOURCE_DIR}/driver/network/network.c
    ${SOURCE_DIR}/app/phone/phone.c
    ${SOURCE_DIR}/app/contacts/contacts.c
    ${SOURCE_DIR}/app/messaging/messaging.c
    ${SOURCE_DIR}/app/settings/settings.c
    ${SOURCE_DIR}/app/scheduler/scheduler.c
    ${SOURCE_DIR}/app/push/push.c
    ${SOURCE_DIR}/app/settings/wizard.c
    ${SOURCE_DIR}/app/filemanager/file_manager.c
    ${SOURCE_DIR}/app/scene/scene.c
    ${SOURCE_DIR}/app/workflow/workflow.c
    ${SOURCE_DIR}/app/study/study.c
    ${SOURCE_DIR}/app/health/health.c
    ${SOURCE_DIR}/app/entertainment/entertainment.c
    ${SOURCE_DIR}/app/family/family.c
    ${SOURCE_DIR}/app/finance/finance.c
    ${SOURCE_DIR}/app/life/life.c
    ${SOURCE_DIR}/app/emergency/emergency.c
    ${SOURCE_DIR}/app/document/document.c
    ${SOURCE_DIR}/app/language/language.c
    ${SOURCE_DIR}/app/reading/reading.c
    ${SOURCE_DIR}/app/social/social.c
    ${SOURCE_DIR}/core/sdk/sdk.c
    ${SOURCE_DIR}/app/multidevice/multidevice.c
    ${SOURCE_DIR}/core/monitoring/monitoring.c
    ${SOURCE_DIR}/app/mobile_app/mobile_app.c
    ${SOURCE_DIR}/app/webadmin/webadmin.c
    ${SOURCE_DIR}/ai/skills/skills.c
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
