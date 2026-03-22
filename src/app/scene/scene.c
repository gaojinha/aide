#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_SCENES 20

// 场景类型
typedef enum {
    SCENE_MORNING,    // 晨间
    SCENE_WORK,       // 工作
    SCENE_EVENING,    // 晚间
    SCENE_HOME,       // 居家
    SCENE_OUTSIDE,    // 外出
    SCENE_DRIVING,    // 驾驶
    SCENE_MEETING,    // 会议
    SCENE_SPORT,      // 运动
    SCENE_STUDY,      // 学习
    SCENE_RELAX,      // 休闲
    SCENE_HEALTH,     // 健康
    SCENE_EMERGENCY   // 紧急
} scene_type_t;

// 场景
typedef struct {
    scene_type_t type;
    char name[32];
    char trigger[64];  // 触发条件
    int brightness;   // 屏幕亮度
    int volume;       // 音量
    int wifi_on;      // WiFi
    int bt_on;        // 蓝牙
    int auto_answer;  // 自动应答
} scene_t;

static scene_t scenes[MAX_SCENES];
static int scene_count = 0;
static scene_type_t current_scene = SCENE_HOME;

// 初始化场景
void scene_init(void) {
    printf("[Scene] Initialized\n");
    
    // 晨间场景
    scene_t *s = &scenes[scene_count++];
    s->type = SCENE_MORNING;
    strcpy(s->name, "晨间");
    strcpy(s->trigger, "06:00-08:00");
    s->brightness = 50;
    s->volume = 60;
    s->wifi_on = 1;
    s->bt_on = 0;
    s->auto_answer = 1;
    
    // 工作场景
    s = &scenes[scene_count++];
    s->type = SCENE_WORK;
    strcpy(s->name, "工作");
    strcpy(s->trigger, "09:00-18:00 + 公司WiFi");
    s->brightness = 80;
    s->volume = 40;
    s->wifi_on = 1;
    s->bt_on = 1;
    s->auto_answer = 0;
    
    // 晚间场景
    s = &scenes[scene_count++];
    s->type = SCENE_EVENING;
    strcpy(s->name, "晚间");
    strcpy(s->trigger, "19:00-23:00");
    s->brightness = 30;
    s->volume = 50;
    s->wifi_on = 1;
    s->bt_on = 1;
    s->auto_answer = 1;
    
    // 居家场景
    s = &scenes[scene_count++];
    s->type = SCENE_HOME;
    strcpy(s->name, "居家");
    strcpy(s->trigger, "GPS=家");
    s->brightness = 60;
    s->volume = 70;
    s->wifi_on = 1;
    s->bt_on = 1;
    s->auto_answer = 1;
    
    // 外出场景
    s = &scenes[scene_count++];
    s->type = SCENE_OUTSIDE;
    strcpy(s->name, "外出");
    strcpy(s->trigger, "GPS!=家 && GPS!=公司");
    s->brightness = 100;
    s->volume = 100;
    s->wifi_on = 1;
    s->bt_on = 0;
    s->auto_answer = 0;
    
    // 驾驶场景
    s = &scenes[scene_count++];
    s->type = SCENE_DRIVING;
    strcpy(s->name, "驾驶");
    strcpy(s->trigger, "加速度+车速>30km/h");
    s->brightness = 100;
    s->volume = 80;
    s->wifi_on = 1;
    s->bt_on = 1;
    s->auto_answer = 1;
    
    // 会议场景
    s = &scenes[scene_count++];
    s->type = SCENE_MEETING;
    strcpy(s->name, "会议");
    strcpy(s->trigger, "日历事件=会议");
    s->brightness = 50;
    s->volume = 0;
    s->wifi_on = 1;
    s->bt_on = 0;
    s->auto_answer = 0;
    
    // 运动场景
    s = &scenes[scene_count++];
    s->type = SCENE_SPORT;
    strcpy(s->name, "运动");
    strcpy(s->trigger, "心率>120 + 加速度");
    s->brightness = 50;
    s->volume = 100;
    s->wifi_on = 0;
    s->bt_on = 1;
    s->auto_answer = 0;
    
    // 学习场景
    s = &scenes[scene_count++];
    s->type = SCENE_STUDY;
    strcpy(s->name, "学习");
    strcpy(s->trigger, "APP=学习");
    s->brightness = 100;
    s->volume = 30;
    s->wifi_on = 1;
    s->bt_on = 0;
    s->auto_answer = 0;
    
    // 省电场景
    s = &scenes[scene_count++];
    s->type = SCENE_HEALTH;
    strcpy(s->name, "健康/省电");
    strcpy(s->trigger, "电量<20%");
    s->brightness = 20;
    s->volume = 30;
    s->wifi_on = 0;
    s->bt_on = 0;
    s->auto_answer = 0;
    
    printf("  Scenes: %d\n", scene_count);
}

// 切换场景
int scene_switch(scene_type_t type) {
    if (type < 0 || type >= scene_count) return -1;
    
    scene_t *s = &scenes[type];
    printf("[Scene] Switching to: %s\n", s->name);
    printf("[Scene] Trigger: %s\n", s->trigger);
    
    // 应用场景设置
    printf("[Scene] Setting: brightness=%d, volume=%d\n", s->brightness, s->volume);
    printf("[Scene] WiFi: %s, BT: %s, AutoAnswer: %s\n",
        s->wifi_on ? "ON" : "OFF",
        s->bt_on ? "ON" : "OFF",
        s->auto_answer ? "ON" : "OFF");
    
    current_scene = type;
    return 0;
}

// 自动检测场景
void scene_auto_detect(void) {
    time_t now = time(NULL);
    struct tm *tm = localtime(&now);
    int hour = tm->tm_hour;
    
    printf("\n[Scene] Auto-detecting...\n");
    printf("  Time: %02d:%02d\n", hour, tm->tm_min);
    
    // 时间判断
    if (hour >= 6 && hour < 9) {
        scene_switch(SCENE_MORNING);
    } else if (hour >= 9 && hour < 18) {
        scene_switch(SCENE_WORK);
    } else if (hour >= 18 && hour < 23) {
        scene_switch(SCENE_EVENING);
    } else {
        // 夜间
        printf("[Scene] Night time - keeping current scene\n");
    }
}

// 列出场景
void scene_list(void) {
    const char *type_names[] = {
        "晨间", "工作", "晚间", "居家", "外出",
        "驾驶", "会议", "运动", "学习", "健康", "紧急"
    };
    
    printf("\n=== Scenes (%d) ===\n", scene_count);
    printf("Current: %s\n\n", type_names[current_scene]);
    
    for (int i = 0; i < scene_count; i++) {
        printf("%d. %s\n", i+1, scenes[i].name);
        printf("   触发: %s\n", scenes[i].trigger);
        printf("   亮度:%d%% 音量:%d%% WiFi:%s BT:%s\n",
            scenes[i].brightness, scenes[i].volume,
            scenes[i].wifi_on ? "ON" : "OFF",
            scenes[i].bt_on ? "ON" : "OFF");
    }
    printf("==================\n\n");
}

// 场景联动
void scene_link(const char *trigger, const char *action) {
    printf("[Scene] Link: %s -> %s\n", trigger, action);
}

// 测试
void scene_test(void) {
    printf("\n=== Scene Test ===\n");
    
    scene_init();
    scene_list();
    
    printf("Auto detection:\n");
    scene_auto_detect();
    
    printf("\nManual switch:\n");
    scene_switch(SCENE_MEETING);
    scene_switch(SCENE_DRIVING);
    scene_switch(SCENE_HOME);
    
    printf("\nScene links:\n");
    scene_link("GPS=家", "开灯");
    scene_link("电量<20%", "省电模式");
    scene_link("进入公司", "关闭声音");
    
    printf("==================\n\n");
}
