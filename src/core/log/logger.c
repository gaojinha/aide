/**
 * 日志系统
 */

#include <stdio.h>
#include <string.h>
#include <time.h>

typedef enum {
    LOG_DEBUG = 0,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR
} log_level_t;

static log_level_t current_level = LOG_INFO;
static FILE *log_file = NULL;

int log_init(const char *path) {
    log_file = fopen(path ? path : "/tmp/aide.log", "a");
    printf("[Log] Initialized\n");
    return log_file ? 0 : -1;
}

void log_set_level(log_level_t level) { current_level = level; }

void log_write(log_level_t level, const char *msg) {
    if (level < current_level) return;
    
    const char *names[] = {"DEBUG", "INFO", "WARN", "ERROR"};
    printf("[%s] %s\n", names[level], msg);
    
    if (log_file) {
        fprintf(log_file, "[%s] %s\n", names[level], msg);
        fflush(log_file);
    }
}

#define LOG_DEBUG(msg) log_write(LOG_DEBUG, msg)
#define LOG_INFO(msg)  log_write(LOG_INFO, msg)
#define LOG_WARN(msg)  log_write(LOG_WARN, msg)
#define LOG_ERROR(msg) log_write(LOG_ERROR, msg)

void log_close(void) { if (log_file) fclose(log_file); }

void log_test(void) {
    printf("\n=== Log Test ===\n");
    LOG_INFO("Info message");
    LOG_WARN("Warning message");
    LOG_ERROR("Error message");
    printf("==================\n\n");
}
