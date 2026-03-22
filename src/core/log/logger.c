/**
 * 日志系统
 */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

#define MAX_LOG_LEN 4096

typedef enum {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR
} log_level_t;

static log_level_t current_level = LOG_INFO;
static FILE *log_file = NULL;

// 初始化日志
int log_init(const char *filename) {
    if (filename) {
        log_file = fopen(filename, "a");
        printf("[Log] File: %s\n", filename);
    }
    printf("[Log] System initialized\n");
    return 0;
}

// 设置级别
void log_set_level(log_level_t level) {
    current_level = level;
}

// 写日志
void log_write(log_level_t level, const char *fmt, ...) {
    if (level < current_level) return;
    
    char buffer[MAX_LOG_LEN];
    time_t now = time(NULL);
    struct tm *tm = localtime(&now);
    
    char *level_str[] = {"DEBUG", "INFO", "WARN", "ERROR"};
    
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    
    char log_line[MAX_LOG_LEN];
    sprintf(log_line, "[%02d:%02d:%02d] [%s] %s\n",
            tm->tm_hour, tm->tm_min, tm->tm_sec,
            level_str[level], buffer);
    
    printf("%s", log_line);
    if (log_file) {
        fprintf(log_file, "%s", log_line);
        fflush(log_file);
    }
}

// 便捷函数
void log_debug(const char *fmt, ...) {
    char buffer[MAX_LOG_LEN];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    log_write(LOG_DEBUG, "%s", buffer);
}

void log_info(const char *fmt, ...) {
    char buffer[MAX_LOG_LEN];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    log_write(LOG_INFO, "%s", buffer);
}

void log_error(const char *fmt, ...) {
    char buffer[MAX_LOG_LEN];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    log_write(LOG_ERROR, "%s", buffer);
}
