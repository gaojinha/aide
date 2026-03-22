#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_LOG_FILES 10

typedef struct {
    char name[64];
    int size;        // KB
    int rotate_count;
} log_file_t;

static log_file_t logs[MAX_LOG_FILES];
static int log_count = 0;
static int max_size = 10240;  // 10MB
static int max_files = 5;

// 初始化
void logrotate_init(int size_kb, int keep) {
    max_size = size_kb;
    max_files = keep;
    log_count = 0;
    printf("[LogRotate] Initialized\n");
    printf("  Max size: %d KB\n", max_size);
    printf("  Keep files: %d\n", max_files);
}

// 添加日志文件
int logrotate_add(const char *name) {
    if (log_count >= MAX_LOG_FILES) return -1;
    
    strncpy(logs[log_count].name, name, 63);
    logs[log_count].size = 0;
    logs[log_count].rotate_count = 0;
    log_count++;
    
    return 0;
}

// 轮转
int logrotate_rotate(const char *name) {
    for (int i = 0; i < log_count; i++) {
        if (strcmp(logs[i].name, name) == 0) {
            logs[i].rotate_count++;
            int old_size = logs[i].size;
            logs[i].size = 0;
            printf("[LogRotate] Rotated: %s.%d (%d KB -> %s.%d)\n",
                name, logs[i].rotate_count - 1, old_size,
                name, logs[i].rotate_count);
            return 0;
        }
    }
    return -1;
}

// 检查并轮转
void logrotate_check(void) {
    printf("[LogRotate] Checking logs...\n");
    
    for (int i = 0; i < log_count; i++) {
        // 模拟大小
        logs[i].size = max_size * (50 + rand() % 100) / 100;
        
        if (logs[i].size > max_size) {
            logrotate_rotate(logs[i].name);
        }
    }
}

// 清理旧日志
void logrotate_clean(void) {
    printf("[LogRotate] Cleaning old logs...\n");
    
    for (int i = 0; i < log_count; i++) {
        if (logs[i].rotate_count > max_files) {
            int to_delete = logs[i].rotate_count - max_files;
            printf("[LogRotate] Deleting %d old %s logs\n", to_delete, logs[i].name);
            logs[i].rotate_count = max_files;
        }
    }
}

// 状态
void logrotate_status(void) {
    printf("\n=== LogRotate Status ===\n");
    printf("Max size: %d KB\n", max_size);
    printf("Keep: %d files\n\n", max_files);
    
    for (int i = 0; i < log_count; i++) {
        printf("%s: %d KB (rotated %d times)\n",
            logs[i].name, logs[i].size, logs[i].rotate_count);
    }
    printf("========================\n\n");
}

// 测试
void logrotate_test(void) {
    printf("\n=== LogRotate Test ===\n");
    
    logrotate_init(10240, 5);
    
    logrotate_add("aide.log");
    logrotate_add("system.log");
    logrotate_add("error.log");
    
    logrotate_status();
    
    printf("Checking:\n");
    logrotate_check();
    logrotate_status();
    
    printf("Cleaning:\n");
    logrotate_clean();
    logrotate_status();
    
    printf("====================\n\n");
}
