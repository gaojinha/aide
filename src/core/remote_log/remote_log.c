#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_LOGS 1000
#define LOG_SERVER "logs.aide.com"

typedef enum {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR
} log_level_t;

typedef struct {
    time_t timestamp;
    log_level_t level;
    char module[32];
    char message[256];
} remote_log_entry_t;

static remote_log_entry_t logs[MAX_LOGS];
static int log_count = 0;
static int enabled = 0;
static char server_url[128] = "";

// 初始化
void remote_log_init(const char *server) {
    if (server) {
        strncpy(server_url, server, 127);
    } else {
        strcpy(server_url, LOG_SERVER);
    }
    enabled = 1;
    log_count = 0;
    printf("[RemoteLog] Initialized\n");
    printf("  Server: %s\n", server_url);
}

// 发送日志
int remote_log_send(log_level_t level, const char *module, const char *msg) {
    if (!enabled) return -1;
    if (log_count >= MAX_LOGS) return -1;
    
    remote_log_entry_t *entry = &logs[log_count];
    entry->timestamp = time(NULL);
    entry->level = level;
    strncpy(entry->module, module, 31);
    strncpy(entry->message, msg, 255);
    log_count++;
    
    return 0;
}

// 上传日志
int remote_log_upload(void) {
    if (!enabled || log_count == 0) {
        printf("[RemoteLog] No logs to upload\n");
        return 0;
    }
    
    printf("[RemoteLog] Uploading %d logs to %s...\n", log_count, server_url);
    
    // 模拟上传
    for (int i = 0; i < log_count && i < 5; i++) {
        remote_log_entry_t *e = &logs[i];
        const char *level_str = 
            e->level == LOG_DEBUG ? "DEBUG" :
            e->level == LOG_INFO ? "INFO" :
            e->level == LOG_WARNING ? "WARN" : "ERROR";
        
        char time_str[32];
        struct tm *tm = localtime(&e->timestamp);
        strftime(time_str, 31, "%Y-%m-%d %H:%M:%S", tm);
        
        printf("  [%s] %s [%s] %s\n", time_str, level_str, e->module, e->message);
    }
    
    if (log_count > 5) {
        printf("  ... and %d more\n", log_count - 5);
    }
    
    printf("[RemoteLog] Uploaded: %d logs\n", log_count);
    
    // 清空本地日志
    log_count = 0;
    return 0;
}

// 查看日志
void remote_log_view(void) {
    printf("\n=== Remote Logs (%d) ===\n", log_count);
    
    for (int i = 0; i < log_count; i++) {
        remote_log_entry_t *e = &logs[i];
        const char *level_str = 
            e->level == LOG_DEBUG ? "DEBUG" :
            e->level == LOG_INFO ? "INFO" :
            e->level == LOG_WARNING ? "WARN" : "ERROR";
        
        char time_str[32];
        struct tm *tm = localtime(&e->timestamp);
        strftime(time_str, 31, "%H:%M:%S", tm);
        
        printf("[%s] %s [%s] %s\n", time_str, level_str, e->module, e->message);
    }
    printf("========================\n\n");
}

// 测试
void remote_log_test(void) {
    printf("\n=== RemoteLog Test ===\n");
    
    remote_log_init("https://logs.aide.com/api");
    
    remote_log_send(LOG_INFO, "System", "System started");
    remote_log_send(LOG_DEBUG, "WiFi", "Connected to network");
    remote_log_send(LOG_WARNING, "Power", "Battery low");
    remote_log_send(LOG_ERROR, "Network", "Connection timeout");
    remote_log_send(LOG_INFO, "App", "User logged in");
    
    remote_log_view();
    
    remote_log_upload();
    
    printf("==================\n\n");
}
