#include <stdio.h>
#include <string.h>

// 系统信息
typedef struct {
    float cpu_usage;    // %
    int cpu_temp;       // °C
    int memory_total;  // MB
    int memory_used;    // MB
    int disk_total;     // MB
    int disk_used;      // MB
    int processes;     // 数量
    int uptime;         // 秒
} system_info_t;

static system_info_t sys_info = {0};

// 初始化
void monitor_init(void) {
    printf("[Monitor] Initialized\n");
}

// 更新状态
void monitor_update(void) {
    // 模拟数据
    sys_info.cpu_usage = 20.0 + rand() % 30;
    sys_info.cpu_temp = 45 + rand() % 15;
    sys_info.memory_total = 2048;
    sys_info.memory_used = 800 + rand() % 500;
    sys_info.disk_total = 32000;
    sys_info.disk_used = 12000 + rand() % 5000;
    sys_info.processes = 50 + rand() % 30;
    sys_info.uptime = 3600 + rand() * 100;
}

// CPU使用率
void monitor_cpu(void) {
    monitor_update();
    printf("\n=== CPU Usage ===\n");
    printf("Total: %.1f%%\n", sys_info.cpu_usage);
    printf("Core 0: %.1f%%\n", sys_info.cpu_usage - 5);
    printf("Core 1: %.1f%%\n", sys_info.cpu_usage);
    printf("Core 2: %.1f%%\n", sys_info.cpu_usage + 5);
    printf("Core 3: %.1f%%\n", sys_info.cpu_usage - 3);
    printf("Temperature: %d°C\n", sys_info.cpu_temp);
    printf("==================\n\n");
}

// 内存使用
void monitor_memory(void) {
    monitor_update();
    int free = sys_info.memory_total - sys_info.memory_used;
    
    printf("\n=== Memory Usage ===\n");
    printf("Total: %d MB\n", sys_info.memory_total);
    printf("Used: %d MB (%.1f%%)\n", 
        sys_info.memory_used, 100.0*sys_info.memory_used/sys_info.memory_total);
    printf("Free: %d MB (%.1f%%)\n", 
        free, 100.0*free/sys_info.memory_total);
    printf("====================\n\n");
}

// 磁盘使用
void monitor_disk(void) {
    monitor_update();
    int free = sys_info.disk_total - sys_info.disk_used;
    
    printf("\n=== Disk Usage ===\n");
    printf("/ (root): %d / %d MB (%.1f%%)\n",
        sys_info.disk_used, sys_info.disk_total, 
        100.0*sys_info.disk_used/sys_info.disk_total);
    printf("/data:   %d / %d MB (%.1f%%)\n",
        sys_info.disk_used/2, sys_info.disk_total/2,
        100.0*sys_info.disk_used/2/(sys_info.disk_total/2));
    printf("/tmp:    %d / %d MB (%.1f%%)\n",
        500, 4096, 500.0*100/4096);
    printf("====================\n\n");
}

// 进程列表
void monitor_processes(void) {
    monitor_update();
    printf("\n=== Processes (%d) ===\n", sys_info.processes);
    printf("PID   USER    %%CPU  %%MEM  COMMAND\n");
    printf("1     root    0.0   0.2   init\n");
    printf("100   root    1.2   0.5   aide\n");
    printf("101   root    0.8   1.2   voice\n");
    printf("102   root    0.3   0.8   camera\n");
    printf("103   root    0.1   0.3   wifi\n");
    printf("...\n");
    printf("======================\n\n");
}

// 系统概览
void monitor_overview(void) {
    monitor_update();
    printf("\n");
    printf("╔═══════════════════════════════════════╗\n");
    printf("║         System Monitor               ║\n");
    printf("╠═══════════════════════════════════════╣\n");
    printf("║ CPU:   %5.1f%%  (Temp: %d°C)      ║\n", sys_info.cpu_usage, sys_info.cpu_temp);
    printf("║ Memory: %d / %d MB (%d%%)         ║\n", 
        sys_info.memory_used, sys_info.memory_total,
        100*sys_info.memory_used/sys_info.memory_total);
    printf("║ Disk:  %d / %d MB (%d%%)         ║\n",
        sys_info.disk_used, sys_info.disk_total,
        100*sys_info.disk_used/sys_info.disk_total);
    printf("║ Procs: %d                         ║\n", sys_info.processes);
    printf("║ Uptime: %d hours                 ║\n", sys_info.uptime/3600);
    printf("╚═══════════════════════════════════════╝\n\n");
}

// 测试
void monitor_test(void) {
    printf("\n=== Monitor Test ===\n");
    
    monitor_overview();
    monitor_cpu();
    monitor_memory();
    monitor_disk();
    monitor_processes();
    
    printf("==================\n\n");
}
