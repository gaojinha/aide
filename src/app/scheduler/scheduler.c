#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_TASKS 20

typedef enum { TASK_ALARM, TASK_REMINDER } task_type_t;
typedef enum { TASK_IDLE, TASK_ACTIVE, TASK_TRIGGERED } task_status_t;

typedef struct {
    int id;
    task_type_t type;
    task_status_t status;
    char title[64];
    char message[128];
    int hour, minute;
    int repeat;
    int enabled;
} schedule_task_t;

static schedule_task_t tasks[MAX_TASKS];
static int task_count = 0;

int scheduler_init(void) {
    printf("[Scheduler] Initialized\n");
    scheduler_add_alarm(7, 0, "起床闹钟", "该起床了！");
    scheduler_add_reminder(9, 0, "喝水提醒", "该喝水了");
    return 0;
}

int scheduler_add_alarm(int hour, int minute, const char *title, const char *msg) {
    if (task_count >= MAX_TASKS) return -1;
    tasks[task_count].id = task_count + 1;
    tasks[task_count].type = TASK_ALARM;
    tasks[task_count].status = TASK_ACTIVE;
    strncpy(tasks[task_count].title, title, 63);
    strncpy(tasks[task_count].message, msg, 127);
    tasks[task_count].hour = hour;
    tasks[task_count].minute = minute;
    tasks[task_count].enabled = 1;
    task_count++;
    printf("[Scheduler] Alarm: %02d:%02d - %s\n", hour, minute, title);
    return task_count;
}

int scheduler_add_reminder(int hour, int minute, const char *title, const char *msg) {
    if (task_count >= MAX_TASKS) return -1;
    tasks[task_count].id = task_count + 1;
    tasks[task_count].type = TASK_REMINDER;
    tasks[task_count].status = TASK_ACTIVE;
    strncpy(tasks[task_count].title, title, 63);
    strncpy(tasks[task_count].message, msg, 127);
    tasks[task_count].hour = hour;
    tasks[task_count].minute = minute;
    tasks[task_count].repeat = 1;
    tasks[task_count].enabled = 1;
    task_count++;
    printf("[Scheduler] Reminder: %02d:%02d - %s\n", hour, minute, title);
    return task_count;
}

void scheduler_list(void) {
    printf("\n=== Tasks (%d) ===\n", task_count);
    for (int i = 0; i < task_count; i++) {
        printf("%d. %02d:%02d - %s\n", tasks[i].id, tasks[i].hour, tasks[i].minute, tasks[i].title);
    }
    printf("==================\n\n");
}

void scheduler_test(void) {
    printf("\n=== Scheduler Test ===\n");
    scheduler_list();
    printf("=====================\n\n");
}
