/**
 * 设置模块
 */

#include <stdio.h>
#include <string.h>

#define MAX_SETTING 100
#define MAX_VALUE 256

typedef struct {
    char key[64];
    char value[MAX_VALUE];
    char type[16];  // string, int, bool
} setting_t;

static setting_t settings[MAX_SETTING];
static int setting_count = 0;

// 初始化设置
int settings_init(void) {
    printf("[Settings] Initialized\n");
    
    // 默认设置
    settings_set_string("language", "zh-CN");
    settings_set_string("theme", "dark");
    settings_set_int("volume", 70);
    settings_set_int("brightness", 80);
    settings_set_string("wake_word", "你好 aide");
    settings_set_bool("auto_answer", 1);
    settings_set_string("api_key", "");
    
    return 0;
}

// 设置字符串
int settings_set_string(const char *key, const char *value) {
    // 查找是否已存在
    for (int i = 0; i < setting_count; i++) {
        if (strcmp(settings[i].key, key) == 0) {
            strncpy(settings[i].value, value, MAX_VALUE - 1);
            printf("[Settings] %s = %s\n", key, value);
            return 0;
        }
    }
    // 新增
    if (setting_count < MAX_SETTING) {
        strncpy(settings[setting_count].key, key, 63);
        strncpy(settings[setting_count].value, value, MAX_VALUE - 1);
        strcpy(settings[setting_count].type, "string");
        setting_count++;
        printf("[Settings] %s = %s\n", key, value);
    }
    return 0;
}

// 设置整数
int settings_set_int(const char *key, int value) {
    char val[32];
    snprintf(val, 32, "%d", value);
    return settings_set_string(key, val);
}

// 设置布尔
int settings_set_bool(const char *key, int value) {
    return settings_set_string(key, value ? "true" : "false");
}

// 获取字符串
const char* settings_get_string(const char *key) {
    for (int i = 0; i < setting_count; i++) {
        if (strcmp(settings[i].key, key) == 0) {
            return settings[i].value;
        }
    }
    return NULL;
}

// 获取整数
int settings_get_int(const char *key) {
    const char *val = settings_get_string(key);
    return val ? atoi(val) : 0;
}

// 获取布尔
int settings_get_bool(const char *key) {
    const char *val = settings_get_string(key);
    return val && strcmp(val, "true") == 0;
}

// 删除设置
int settings_delete(const char *key) {
    for (int i = 0; i < setting_count; i++) {
        if (strcmp(settings[i].key, key) == 0) {
            // 前移
            for (int j = i; j < setting_count - 1; j++) {
                settings[j] = settings[j + 1];
            }
            setting_count--;
            printf("[Settings] Deleted: %s\n", key);
            return 0;
        }
    }
    return -1;
}

// 重置为默认
int settings_reset(void) {
    printf("[Settings] Reset to defaults\n");
    setting_count = 0;
    return settings_init();
}

// 列出所有设置
void settings_list(void) {
    printf("\n=== Settings (%d) ===\n", setting_count);
    for (int i = 0; i < setting_count; i++) {
        printf("%s = %s (type: %s)\n", 
               settings[i].key, settings[i].value, settings[i].type);
    }
    printf("======================\n\n");
}

// 保存到文件
int settings_save(const char *filename) {
    printf("[Settings] Saving to %s\n", filename);
    // TODO: 实际保存到文件
    return 0;
}

// 从文件加载
int settings_load(const char *filename) {
    printf("[Settings] Loading from %s\n", filename);
    // TODO: 实际从文件加载
    return 0;
}
