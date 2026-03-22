#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_RECORDS 100

// 用电记录
typedef struct {
    time_t timestamp;
    int percentage;    // 电量
    int voltage;       // mV
    int current;       // mA
    int power;         // mW
    int temp;          // 摄氏度
    int screen_on;     // 屏幕状态
    int wifi_on;       // WiFi状态
    int bt_on;         // 蓝牙状态
} power_record_t;

static power_record_t records[MAX_RECORDS];
static int record_count = 0;

// 添加记录
void power_stats_add(void) {
    if (record_count >= MAX_RECORDS) return;
    
    power_record_t *r = &records[record_count];
    r->timestamp = time(NULL);
    r->percentage = 85 - record_count;  // 模拟
    r->voltage = 4200;
    r->current = -500;
    r->power = r->voltage * r->current / 1000 * -1;
    r->temp = 40 + (record_count % 10);
    r->screen_on = record_count % 3 != 0;
    r->wifi_on = record_count % 2 == 0;
    r->bt_on = record_count % 5 == 0;
    
    record_count++;
}

// 今日用电
void power_stats_today(void) {
    int total_mwh = 0;
    int screen_time = 0;
    int wifi_time = 0;
    int avg_temp = 0;
    
    for (int i = 0; i < record_count; i++) {
        total_mwh += records[i].power;
        if (records[i].screen_on) screen_time++;
        if (records[i].wifi_on) wifi_time++;
        avg_temp += records[i].temp;
    }
    
    printf("\n=== Today's Power Stats ===\n");
    printf("Records: %d\n", record_count);
    printf("Total: %d mWh\n", total_mwh);
    printf("Screen time: %d hours\n", screen_time);
    printf("WiFi time: %d hours\n", wifi_time);
    printf("Avg temp: %d°C\n", record_count > 0 ? avg_temp / record_count : 0);
    printf("==========================\n\n");
}

// 应用用电排行
void power_stats_apps(void) {
    printf("\n=== App Power Usage ===\n");
    printf("Rank  App          mWh    %%\n");
    printf("1.    AI Assistant  2500  35%%\n");
    printf("2.    Camera        1200  17%%\n");
    printf("3.    Voice         800   11%%\n");
    printf("4.    WiFi          750   10%%\n");
    printf("5.    Display       600   8%%\n");
    printf("6.    System        550   8%%\n");
    printf("7.    Bluetooth     350   5%%\n");
    printf("8.    Others        450   6%%\n");
    printf("--------------------------\n");
    printf("Total              7200 100%%\n");
    printf("=======================\n\n");
}

// 省电建议
void power_stats_tips(void) {
    printf("\n=== Power Saving Tips ===\n");
    printf("1. Reduce screen brightness (current: 80%%)\n");
    printf("2. Turn off WiFi when not in use\n");
    printf("3. Use airplane mode at night\n");
    printf("4. Close background apps\n");
    printf("5. Enable battery saver mode\n");
    printf("===========================\n\n");
}

// 电池健康
void power_stats_health(void) {
    printf("\n=== Battery Health ===\n");
    printf("Design capacity: 5000 mAh\n");
    printf("Current capacity: 4750 mAh (95%%)\n");
    printf("Cycle count: 150\n");
    printf("Health: GOOD\n");
    printf("Temperature: 35°C\n");
    printf("Voltage: 4.2V\n");
    printf("========================\n\n");
}

// 测试
void power_stats_test(void) {
    printf("\n=== Power Stats Test ===\n");
    
    // 模拟记录
    for (int i = 0; i < 10; i++) {
        power_stats_add();
    }
    
    power_stats_today();
    power_stats_apps();
    power_stats_health();
    power_stats_tips();
    
    printf("==================\n\n");
}
