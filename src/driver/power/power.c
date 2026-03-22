#include <stdio.h>
#include <string.h>

// 电源状态
typedef enum {
    POWER_BATTERY,      // 电池供电
    POWER_AC,           // 接交流电
    POWER_CHARGING,     // 充电中
    POWER_LOW,          // 低电量
    POWER_CRITICAL      // 临界低电
} power_state_t;

// 电池信息
typedef struct {
    int percentage;     // 0-100%
    int voltage;        // mV
    int current;       // mA
    int temperature;   // 摄氏度
    int capacity;      // mAh
    int cycles;        // 充电循环次数
} battery_info_t;

static power_state_t power_state = POWER_AC;
static battery_info_t battery = {
    .percentage = 85,
    .voltage = 4200,
    .current = -500,
    .temperature = 28,
    .capacity = 5000,
    .cycles = 150
};

// 初始化
int power_init(void) {
    printf("[Power] Initialized\n");
    printf("  Battery: 5000mAh\n");
    printf("  Adapter: 65W\n");
    return 0;
}

// 获取电池信息
int power_get_battery(battery_info_t *info) {
    *info = battery;
    return 0;
}

// 获取电源状态
power_state_t power_get_state(void) {
    return power_state;
}

// 获取电量百分比
int power_get_percentage(void) {
    return battery.percentage;
}

// 设置电量百分比(模拟)
void power_set_percentage(int pct) {
    battery.percentage = pct;
    if (pct > 20) power_state = POWER_BATTERY;
    if (pct <= 20) power_state = POWER_LOW;
    if (pct <= 5) power_state = POWER_CRITICAL;
}

// 开始充电
int power_start_charging(void) {
    power_state = POWER_CHARGING;
    printf("[Power] Charging started\n");
    return 0;
}

// 停止充电
int power_stop_charging(void) {
    power_state = POWER_AC;
    printf("[Power] Charging stopped\n");
    return 0;
}

// 休眠
int power_suspend(void) {
    printf("[Power] Suspending to RAM...\n");
    printf("[Power] Suspended\n");
    return 0;
}

// 关机
int power_shutdown(void) {
    printf("[Power] Shutting down...\n");
    return 0;
}

// 重启
int power_reboot(void) {
    printf("[Power] Rebooting...\n");
    return 0;
}

// 省电模式
int power_set_eco_mode(int enable) {
    printf("[Power] Eco mode: %s\n", enable ? "ON" : "OFF");
    return 0;
}

// 显示状态
void power_status(void) {
    printf("\n=== Power Status ===\n");
    printf("State: %s\n", 
        power_state == POWER_BATTERY ? "On Battery" :
        power_state == POWER_AC ? "AC Power" :
        power_state == POWER_CHARGING ? "Charging" :
        power_state == POWER_LOW ? "Low Battery" : "Critical!");
    printf("Battery: %d%%\n", battery.percentage);
    printf("Voltage: %d mV\n", battery.voltage);
    printf("Temperature: %d°C\n", battery.temperature);
    printf("Cycles: %d\n", battery.cycles);
    printf("=====================\n\n");
}

// 测试
void power_test(void) {
    printf("\n=== Power Test ===\n");
    
    power_status();
    
    power_set_percentage(15);
    power_status();
    
    power_start_charging();
    power_status();
    
    power_set_percentage(100);
    power_status();
    
    power_set_eco_mode(1);
    power_suspend();
    
    printf("==================\n\n");
}
