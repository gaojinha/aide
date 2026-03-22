#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_PROCESSES 20

// 进程状态
typedef enum {
    PROC_RUNNING,
    PROC_STOPPED,
    PROC_CRASHED,
    PROC_RESTARTING
} proc_status_t;

// 被监控进程
typedef struct {
    char name[32];
    char path[128];
    pid_t pid;
    proc_status_t status;
    int auto_restart;
    int max_restarts;
    int restart_count;
    time_t last_check;
} monitored_proc_t;

static monitored_proc_t processes[MAX_PROCESSES];
static int proc_count = 0;
static int watchdog_enabled = 1;
static int check_interval = 5;  // 秒

// 初始化
int watchdog_init(void) {
    printf("[Watchdog] Initialized\n");
    printf("  Check interval: %ds\n", check_interval);
    printf("  Max processes: %d\n", MAX_PROCESSES);
    return 0;
}

// 添加监控
int watchdog_add_process(const char *name, const char *path, int auto_restart, int max_restarts) {
    if (proc_count >= MAX_PROCESSES) return -1;
    
    monitored_proc_t *p = &processes[proc_count];
    strncpy(p->name, name, 31);
    strncpy(p->path, path, 127);
    p->pid = 0;
    p->status = PROC_STOPPED;
    p->auto_restart = auto_restart;
    p->max_restarts = max_restarts;
    p->restart_count = 0;
    p->last_check = time(NULL);
    proc_count++;
    
    printf("[Watchdog] Added: %s (auto_restart=%d, max=%d)\n", 
        name, auto_restart, max_restarts);
    return 0;
}

// 启动进程
int watchdog_start(const char *name) {
    for (int i = 0; i < proc_count; i++) {
        if (strcmp(processes[i].name, name) == 0) {
            // 模拟启动
            processes[i].pid = 1000 + i;  // 模拟PID
            processes[i].status = PROC_RUNNING;
            processes[i].restart_count = 0;
            printf("[Watchdog] Started: %s (PID: %d)\n", name, processes[i].pid);
            return 0;
        }
    }
    return -1;
}

// 停止进程
int watchdog_stop(const char *name) {
    for (int i = 0; i < proc_count; i++) {
        if (strcmp(processes[i].name, name) == 0) {
            processes[i].pid = 0;
            processes[i].status = PROC_STOPPED;
            printf("[Watchdog] Stopped: %s\n", name);
            return 0;
        }
    }
    return -1;
}

// 检查进程 (模拟)
void watchdog_check(void) {
    if (!watchdog_enabled) return;
    
    for (int i = 0; i < proc_count; i++) {
        monitored_proc_t *p = &processes[i];
        if (p->status != PROC_RUNNING) continue;
        
        // 模拟检查: 随机模拟崩溃
        // 实际应该检查 /proc/PID 是否存在
        p->last_check = time(NULL);
        
        // 模拟: 如果进程名包含 "crash" 则模拟崩溃
        if (strstr(p->name, "crash") != NULL && rand() % 10 == 0) {
            p->status = PROC_CRASHED;
            printf("[Watchdog] %s CRASHED!\n", p->name);
            
            // 自动重启
            if (p->auto_restart && p->restart_count < p->max_restarts) {
                p->status = PROC_RESTARTING;
                printf("[Watchdog] Restarting %s (%d/%d)...\n", 
                    p->name, p->restart_count + 1, p->max_restarts);
                p->restart_count++;
                p->status = PROC_RUNNING;
            }
        }
    }
}

// 启用/禁用
int watchdog_enable(int enable) {
    watchdog_enabled = enable;
    printf("[Watchdog] %s\n", enable ? "Enabled" : "Disabled");
    return 0;
}

// 列出状态
void watchdog_status(void) {
    printf("\n=== Watchdog Status ===\n");
    printf("Enabled: %s\n", watchdog_enabled ? "YES" : "NO");
    printf("Check interval: %ds\n", check_interval);
    printf("Monitored: %d processes\n\n", proc_count);
    
    for (int i = 0; i < proc_count; i++) {
        monitored_proc_t *p = &processes[i];
        const char *status_str = 
            p->status == PROC_RUNNING ? "RUNNING" :
            p->status == PROC_STOPPED ? "STOPPED" :
            p->status == PROC_CRASHED ? "CRASHED" : "RESTARTING";
        
        printf("%d. %s: %s (PID: %d, restarts: %d/%d)\n",
            i+1, p->name, status_str, p->pid, p->restart_count, p->max_restarts);
    }
    printf("=========================\n\n");
}

// 测试
void watchdog_test(void) {
    printf("\n=== Watchdog Test ===\n");
    
    // 添加测试进程
    watchdog_add_process("aide-core", "/usr/bin/aide", 1, 3);
    watchdog_add_process("aide-voice", "/usr/bin/voice", 1, 2);
    watchdog_add_process("test-crash", "/tmp/test", 1, 2);
    
    watchdog_status();
    
    // 启动进程
    watchdog_start("aide-core");
    watchdog_start("aide-voice");
    watchdog_start("test-crash");
    
    watchdog_status();
    
    // 模拟检查多次
    printf("\nSimulating checks...\n");
    for (int i = 0; i < 5; i++) {
        watchdog_check();
        sleep(1);
    }
    
    watchdog_status();
    
    printf("==================\n\n");
}
