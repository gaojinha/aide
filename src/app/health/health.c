#include <stdio.h>
#include <time.h>
#include <string.h>

#define MAX_EXERCISES 20
#define MAX_SLEEPS 30
#define MAX_MEALS 50

typedef struct { char name[32]; int duration; int calories; } exercise_t;
typedef struct { int quality; int duration; } sleep_t;
typedef struct { char food[64]; int calories; } meal_t;

static exercise_t exercises[MAX_EXERCISES];
static int exercise_count = 0;
static sleep_t sleeps[MAX_SLEEPS];
static int sleep_count = 0;
static meal_t meals[MAX_MEALS];
static int meal_count = 0;

void health_exercise_init(void) {
    printf("[Health] Exercise initialized\n");
    exercise_t *e = &exercises[exercise_count++];
    strcpy(e->name, "跑步"); e->duration = 30; e->calories = 300;
    e = &exercises[exercise_count++];
    strcpy(e->name, "瑜伽"); e->duration = 45; e->calories = 150;
    printf("  Exercises: %d\n", exercise_count);
}

void health_exercise_list(void) {
    printf("\n=== Exercises (%d) ===\n", exercise_count);
    for (int i = 0; i < exercise_count; i++) {
        printf("%d. %s: %d分钟, %d卡\n", i+1, exercises[i].name, exercises[i].duration, exercises[i].calories);
    }
    printf("======================\n\n");
}

void health_sleep_init(void) { printf("[Health] Sleep tracking\n"); sleep_count = 7; printf("  Records: %d\n", sleep_count); }
void health_sleep_stats(void) {
    printf("\n=== Sleep (7 days) ===\n");
    printf("Avg: 7.5小时, 质量: 85%%\n");
    printf("2026-03-22: 7小时\n");
    printf("2026-03-21: 8小时\n");
    printf("=====================\n\n");
}

void health_diet_init(void) {
    printf("[Health] Diet tracking\n");
    meal_t *m = &meals[meal_count++]; strcpy(m->food, "早餐: 豆浆+油条"); m->calories = 400;
    m = &meals[meal_count++]; strcpy(m->food, "午餐: 米饭+菜"); m->calories = 600;
    m = &meals[meal_count++]; strcpy(m->food, "晚餐: 粥+小菜"); m->calories = 300;
    printf("  Meals: %d\n", meal_count);
}
void health_diet_stats(void) {
    printf("\n=== Diet Today ===\n");
    printf("摄入: 1300卡\n");
    printf("消耗: 800卡\n");
    printf("------------------------\n");
    printf("余额: -500卡 (健康)\n");
    printf("====================\n\n");
}

void health_heart_rate(void) {
    printf("\n=== Heart Rate ===\n");
    printf("当前: 72 BPM\n");
    printf("静息: 68 BPM\n");
    printf("最大: 140 BPM (运动)\n");
    printf("====================\n\n");
}

void health_dashboard(void) {
    printf("\n");
    printf("╔═══════════════════════════════════════╗\n");
    printf("║         Health Dashboard             ║\n");
    printf("╠═══════════════════════════════════════╣\n");
    printf("║ ❤️ 心率: 72 BPM                      ║\n");
    printf("║ 👟 今日步数: 8500                    ║\n");
    printf("║ 😴 睡眠: 7.5小时 (85%%)              ║\n");
    printf("║ 🍽️ 摄入: 1300卡                     ║\n");
    printf("║ 💧 喝水: 1500ml                       ║\n");
    printf("║ ⏱️ 运动: 45分钟                      ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");
}

void health_test(void) {
    printf("\n=== Health Test ===\n");
    health_exercise_init(); health_exercise_list();
    health_sleep_init(); health_sleep_stats();
    health_diet_init(); health_diet_stats();
    health_heart_rate();
    health_dashboard();
    printf("==================\n\n");
}
