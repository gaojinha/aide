/**
 * 用户记忆模块 - 习惯学习
 */

#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_MEMORIES 1000
#define MAX_KEY_LEN 64
#define MAX_VALUE_LEN 256

// 记忆条目
typedef struct {
    char key[MAX_KEY_LEN];
    char value[MAX_VALUE_LEN];
    int count;          // 出现次数
    time_t last_time;   // 最后更新时间
} memory_t;

// 记忆库
static memory_t memories[MAX_MEMORIES];
static int memory_count = 0;

// 初始化记忆
int memory_init(void) {
    printf("[Memory] User memory initialized\n");
    return 0;
}

// 保存记忆
int memory_remember(const char *key, const char *value) {
    // 查找是否已存在
    for (int i = 0; i < memory_count; i++) {
        if (strcmp(memories[i].key, key) == 0) {
            strncpy(memories[i].value, value, MAX_VALUE_LEN - 1);
            memories[i].count++;
            memories[i].last_time = time(NULL);
            printf("[Memory] Updated: %s = %s (count: %d)\n", 
                   key, value, memories[i].count);
            return 0;
        }
    }
    
    // 新增记忆
    if (memory_count < MAX_MEMORIES) {
        strncpy(memories[memory_count].key, key, MAX_KEY_LEN - 1);
        strncpy(memories[memory_count].value, value, MAX_VALUE_LEN - 1);
        memories[memory_count].count = 1;
        memories[memory_count].last_time = time(NULL);
        memory_count++;
        printf("[Memory] Remembered: %s = %s\n", key, value);
    }
    return 0;
}

// 回忆
int memory_recall(const char *key, char *value) {
    for (int i = 0; i < memory_count; i++) {
        if (strcmp(memories[i].key, key) == 0) {
            strcpy(value, memories[i].value);
            printf("[Memory] Recalled: %s = %s\n", key, value);
            return 0;
        }
    }
    return -1;  // 未找到
}

// 遗忘
int memory_forget(const char *key) {
    for (int i = 0; i < memory_count; i++) {
        if (strcmp(memories[i].key, key) == 0) {
            // 删除并前移
            for (int j = i; j < memory_count - 1; j++) {
                memories[j] = memories[j + 1];
            }
            memory_count--;
            printf("[Memory] Forgot: %s\n", key);
            return 0;
        }
    }
    return -1;
}

// 学习习惯
int memory_learn_habit(const char *action, const char *time) {
    char key[128];
    sprintf(key, "habit_%s", action);
    memory_remember(key, time);
    return 0;
}

// 获取习惯
int memory_get_habit(const char *action, char *time) {
    char key[128];
    sprintf(key, "habit_%s", action);
    return memory_recall(key, time);
}

// 列出所有记忆
void memory_list(void) {
    printf("\n=== User Memories (%d) ===\n", memory_count);
    for (int i = 0; i < memory_count; i++) {
        printf("[%d] %s = %s (count: %d)\n", 
               i+1, memories[i].key, memories[i].value, memories[i].count);
    }
    printf("==========================\n\n");
}
