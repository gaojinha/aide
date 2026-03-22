/**
 * 配置系统 - JSON配置解析
 */

#include <stdio.h>
#include <string.h>

#define MAX_KEYS 100
#define MAX_VALUE_LEN 256

typedef struct {
    char key[MAX_KEYS][64];
    char value[MAX_KEYS][MAX_VALUE_LEN];
    int count;
} config_t;

static config_t config;

// 初始化配置
int config_init(void) {
    config.count = 0;
    printf("[Config] System initialized\n");
    return 0;
}

// 加载配置
int config_load(const char *filename) {
    printf("[Config] Loading: %s\n", filename);
    // TODO: 解析JSON
    config.count = 0;
    return 0;
}

// 保存配置
int config_save(const char *filename) {
    printf("[Config] Saving: %s\n", filename);
    // TODO: 保存JSON
    return 0;
}

// 设置值
int config_set(const char *key, const char *value) {
    // 查找是否已存在
    for (int i = 0; i < config.count; i++) {
        if (strcmp(config.key[i], key) == 0) {
            strncpy(config.value[i], value, MAX_VALUE_LEN - 1);
            printf("[Config] Set %s = %s\n", key, value);
            return 0;
        }
    }
    // 新增
    if (config.count < MAX_KEYS) {
        strncpy(config.key[config.count], key, 63);
        strncpy(config.value[config.count], value, MAX_VALUE_LEN - 1);
        config.count++;
        printf("[Config] Added %s = %s\n", key, value);
    }
    return 0;
}

// 获取值
const char* config_get(const char *key) {
    for (int i = 0; i < config.count; i++) {
        if (strcmp(config.key[i], key) == 0) {
            return config.value[i];
        }
    }
    return NULL;
}

// 打印所有配置
void config_list(void) {
    printf("\n=== Config ===\n");
    for (int i = 0; i < config.count; i++) {
        printf("%s = %s\n", config.key[i], config.value[i]);
    }
    printf("==============\n\n");
}
