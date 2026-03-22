#include <stdio.h>
#include <string.h>

// CPU频率等级
typedef enum {
    CPU_PERF,      // 性能模式
    CPU_BALANCED,  // 平衡模式
    CPU_ECO,       // 省电模式
    CPU_LOW,       // 低功耗
    CPU_MIN        // 最低功耗
} cpu_governor_t;

// 当前功耗状态
typedef struct {
    cpu_governor_t governor;
    int cpu_freq;       // MHz
    int cpu_temp;       // 摄氏度
    int gpu_freq;       // MHz
    int memory_freq;    // MHz
    int brightness;     // 0-100
    int auto_rotate;    // 自动旋转
} power_profile_t;

static power_profile_t current_profile = {
    .governor = CPU_BALANCED,
    .cpu_freq = 1800,
    .cpu_temp = 45,
    .gpu_freq = 800,
    .memory_freq = 1560,
    .brightness = 80,
    .auto_rotate = 1
};

// 设置CPU调速器
int set_cpu_governor(cpu_governor_t gov) {
    const char *gov_names[] = {"performance", "balanced", "powersave", "ondemand", "conservative"};
    if (gov < CPU_PERF || gov > CPU_MIN) return -1;
    
    current_profile.governor = gov;
    
    // 设置频率
    int freqs[] = {2000, 1800, 1400, 1000, 600};
    current_profile.cpu_freq = freqs[gov];
    
    printf("[PowerMgmt] CPU governor: %s (%d MHz)\n", gov_names[gov], current_profile.cpu_freq);
    return 0;
}

// 设置屏幕亮度
int set_brightness(int level) {
    if (level < 0) level = 0;
    if (level > 100) level = 100;
    current_profile.brightness = level;
    printf("[PowerMgmt] Brightness: %d%%\n", level);
    return 0;
}

// 温度监控
void check_temperature(void) {
    // 模拟读取温度
    current_profile.cpu_temp = 40 + rand() % 20;
    
    // 过热保护
    if (current_profile.cpu_temp > 80) {
        printf("[PowerMgmt] WARNING: Overheating! %d°C\n", current_profile.cpu_temp);
        if (current_profile.governor != CPU_ECO) {
            set_cpu_governor(CPU_ECO);
        }
    }
}

// 省电模式
void power_mgmt_eco_mode(void) {
    printf("[PowerMgmt] Entering ECO mode...\n");
    set_cpu_governor(CPU_ECO);
    set_brightness(50);
    // 关闭GPS/蓝牙
    printf("[PowerMgmt] GPS/Bluetooth disabled\n");
}

// 性能模式
void power_mgmt_perf_mode(void) {
    printf("[PowerMgmt] Entering PERFORMANCE mode...\n");
    set_cpu_governor(CPU_PERF);
    set_brightness(100);
    // 启用全部功能
    printf("[PowerMgmt] All features enabled\n");
}

// 状态显示
void power_mgmt_status(void) {
    const char *gov_names[] = {"PERF", "BALANCED", "ECO", "LOW", "MIN"};
    
    printf("\n=== Power Management ===\n");
    printf("Governor: %s\n", gov_names[current_profile.governor]);
    printf("CPU: %d MHz (temp: %d°C)\n", current_profile.cpu_freq, current_profile.cpu_temp);
    printf("GPU: %d MHz\n", current_profile.gpu_freq);
    printf("Memory: %d MHz\n", current_profile.memory_freq);
    printf("Brightness: %d%%\n", current_profile.brightness);
    printf("=========================\n\n");
}

// 测试
void power_mgmt_test(void) {
    printf("\n=== PowerMgmt Test ===\n");
    
    power_mgmt_status();
    
    printf("Testing profiles...\n");
    
    power_mgmt_perf_mode();
    power_mgmt_status();
    
    power_mgmt_eco_mode();
    power_mgmt_status();
    
    set_cpu_governor(CPU_BALANCED);
    set_brightness(70);
    power_mgmt_status();
    
    check_temperature();
    
    printf("==================\n\n");
}
