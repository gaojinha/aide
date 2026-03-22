/**
 * 配置管理 - 文件读写
 */

#include <stdio.h>
#include <string.h>

#define MAX_KEYS 50
#define MAX_VALUE 256
#define CONFIG_FILE "/etc/aide/config.json"

typedef struct {
    char key[64];
    char value[MAX_VALUE];
} config_item_t;

static config_item_t configs[MAX_KEYS];
static int config_count = 0;

// 初始化
int config_init(void) {
    printf("[Config] Initialized\n");
    // 默认配置
    config_set("language", "zh-CN");
    config_set("theme", "dark");
    config_set("api_key", "");
    config_set("model", "abab6.5s-chat");
    config_set("wake_word", "你好 aide");
    config_set("voice", "zh-CN-XiaoxiaoNeural");
    config_set("volume", "70");
    config_set("brightness", "80");
    config_set("auto_answer", "true");
    return 0;
}

// 设置配置
int config_set(const char *key, const char *value) {
    // 查找是否已存在
    for (int i = 0; i < config_count; i++) {
        if (strcmp(configs[i].key, key) == 0) {
            strncpy(configs[i].value, value, MAX_VALUE - 1);
            printf("[Config] %s = %s\n", key, value);
            return 0;
        }
    }
    // 新增
    if (config_count < MAX_KEYS) {
        strncpy(configs[config_count].key, key, 63);
        strncpy(configs[config_count].value, value, MAX_VALUE - 1);
        config_count++;
        printf("[Config] %s = %s\n", key, value);
    }
    return 0;
}

// 获取配置
const char* config_get(const char *key) {
    for (int i = 0; i < config_count; i++) {
        if (strcmp(configs[i].key, key) == 0) {
            return configs[i].value;
        }
    }
    return NULL;
}

// 删除配置
int config_delete(const char *key) {
    for (int i = 0; i < config_count; i++) {
        if (strcmp(configs[i].key, key) == 0) {
            for (int j = i; j < config_count - 1; j++) {
                configs[j] = configs[j + 1];
            }
            config_count--;
            return 0;
        }
    }
    return -1;
}

// 保存到文件
int config_save(const char *filename) {
    FILE *f = fopen(filename ? filename : CONFIG_FILE, "w");
    if (!f) {
        printf("[Config] Save failed\n");
        return -1;
    }
    
    fprintf(f, "{\n");
    for (int i = 0; i < config_count; i++) {
        fprintf(f, "  \"%s\": \"%s\"%s\n", 
            configs[i].key, configs[i].value,
            i < config_count - 1 ? "," : "");
    }
    fprintf(f, "}\n");
    
    fclose(f);
    printf("[Config] Saved to %s\n", filename ? filename : CONFIG_FILE);
    return 0;
}

// 从文件加载
int config_load(const char *filename) {
    printf("[Config] Loading from %s\n", filename ? filename : CONFIG_FILE);
    // TODO: 实际解析JSON
    // 使用cJSON或手动解析
    return 0;
}

// 列出所有配置
void config_list(void) {
    printf("\n=== aide Config (%d) ===\n", config_count);
    for (int i = 0; i < config_count; i++) {
        printf("%s = %s\n", configs[i].key, configs[i].value);
    }
    printf("=======================\n\n");
}

// 配置测试
void config_test(void) {
    printf("\n=== Config Test ===\n");
    
    config_set("test_key", "test_value");
    const char *val = config_get("test_key");
    printf("Get test_key: %s\n", val ? val : "NULL");
    
    config_set("test_key", "new_value");
    val = config_get("test_key");
    printf("Get test_key again: %s\n", val);
    
    config_save("/tmp/aide_config_test.json");
    
    printf("===================\n\n");
}
