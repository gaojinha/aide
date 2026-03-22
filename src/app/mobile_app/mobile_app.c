#include <stdio.h>
#include <string.h>

#define MAX_DEVICES 10

// 设备信息
typedef struct {
    char id[32];
    char name[32];
    char platform[16];  // android/ios
    int online;
} mobile_device_t;

// API端点
typedef struct {
    char path[64];
    char method[8];  // GET/POST
    int (*handler)(void);
} api_endpoint_t;

static mobile_device_t devices[MAX_DEVICES];
static int device_count = 0;
static int api_port = 8080;

// 初始化
void mobile_app_init(void) {
    printf("[MobileApp] Initialized\n");
    printf("  API Port: %d\n", api_port);
    printf("  Protocol: RESTful + WebSocket\n");
    
    // 注册设备
    mobile_app_register("android-001", "高叔叔的P50", "android");
    mobile_app_register("iphone-001", "iPhone 15", "ios");
    
    printf("  Devices: %d\n", device_count);
}

// 注册设备
int mobile_app_register(const char *id, const char *name, const char *platform) {
    if (device_count >= MAX_DEVICES) return -1;
    
    mobile_device_t *d = &devices[device_count];
    strncpy(d->id, id, 31);
    strncpy(d->name, name, 31);
    strncpy(d->platform, platform, 15);
    d->online = 1;
    device_count++;
    
    printf("[MobileApp] Registered: %s (%s)\n", name, platform);
    return 0;
}

// 语音推送
int mobile_app_push_voice(const char *device_id, const char *text) {
    printf("[MobileApp] Push voice to %s: %s\n", device_id, text);
    return 0;
}

// 消息推送
int mobile_app_push_message(const char *device_id, const char *title, const char *body) {
    printf("[MobileApp] Push notification to %s\n", device_id);
    printf("  Title: %s\n", title);
    printf("  Body: %s\n", body);
    return 0;
}

// 远程控制
int mobile_app_control(const char *device_id, const char *cmd) {
    printf("[MobileApp] Remote control %s: %s\n", device_id, cmd);
    return 0;
}

// 获取状态
void mobile_app_status(void) {
    printf("\n=== Mobile App Status ===\n");
    printf("API Port: %d\n", api_port);
    printf("Protocol: RESTful + WebSocket\n");
    printf("Devices: %d\n\n", device_count);
    
    for (int i = 0; i < device_count; i++) {
        printf("%d. %s (%s) %s\n", i+1,
            devices[i].name,
            devices[i].platform,
            devices[i].online ? "[在线]" : "[离线]");
    }
    printf("=========================\n\n");
}

// API列表
void mobile_app_api_list(void) {
    printf("\n=== Mobile API Endpoints ===\n");
    printf("GET  /api/v1/status          - 系统状态\n");
    printf("POST /api/v1/voice          - 语音推送\n");
    printf("POST /api/v1/message        - 消息推送\n");
    printf("POST /api/v1/control        - 远程控制\n");
    printf("GET  /api/v1/sensors        - 传感器数据\n");
    printf("POST /api/v1/camera/snap    - 拍照\n");
    printf("GET  /api/v1/files          - 文件列表\n");
    printf("WS   /ws/stream             - 实时流\n");
    printf("===========================\n\n");
}

// 测试
void mobile_app_test(void) {
    printf("\n=== MobileApp Test ===\n");
    
    mobile_app_status();
    mobile_app_api_list();
    
    printf("Push voice:\n");
    mobile_app_push_voice("android-001", "你好，我是 aide");
    
    printf("\nPush notification:\n");
    mobile_app_push_message("iphone-001", "有新消息", "来自 aide");
    
    printf("\nRemote control:\n");
    mobile_app_control("android-001", "play_music");
    mobile_app_control("android-001", "take_photo");
    
    mobile_app_status();
    
    printf("==================\n\n");
}
