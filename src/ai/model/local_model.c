/**
 * 大模型模块 - 本地+云端
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CONTEXT 4096
#define MAX_RESPONSE 2048

typedef struct {
    char model[64];        // 模型名
    char api_key[128];    // API Key
    char endpoint[256];   // API端点
    int context_size;     // 上下文大小
    int temperature;      // 温度
    int max_tokens;       // 最大token
} model_config_t;

static model_config_t config = {
    .model = "abab6.5s-chat",
    .api_key = "",
    .endpoint = "https://api.minimax.chat/v1/text/chatcompletion_v2",
    .context_size = 4096,
    .temperature = 0.7,
    .max_tokens = 1024
};

static int model_loaded = 0;

// 初始化
int model_init(void) {
    printf("[Model] Initialized\n");
    printf("  Local: /models/aide.bin\n");
    printf("  Cloud: %s\n", config.endpoint);
    return 0;
}

// 设置API Key
void model_set_api_key(const char *key) {
    strncpy(config.api_key, key, 127);
    printf("[Model] API Key set\n");
}

// 设置模型参数
void model_set_param(const char *key, const char *value) {
    if (strcmp(key, "model") == 0) {
        strncpy(config.model, value, 63);
    } else if (strcmp(key, "temperature") == 0) {
        config.temperature = atoi(value);
    } else if (strcmp(key, "max_tokens") == 0) {
        config.max_tokens = atoi(value);
    }
    printf("[Model] Set %s = %s\n", key, value);
}

// 加载本地模型
int model_load_local(const char *path) {
    printf("[Model] Loading local model: %s\n", path ? path : "/models/aide.bin");
    // TODO: 实际加载llama.cpp模型
    model_loaded = 1;
    printf("[Model] Local model loaded\n");
    return 0;
}

// 本地推理
int model_infer_local(const char *prompt, char *response, int max_len) {
    if (!model_loaded) {
        printf("[Model] Local model not loaded!\n");
        return -1;
    }
    printf("[Model] Local infer...\n");
    snprintf(response, max_len, "[本地模型] %s", prompt);
    return 0;
}

// 云端推理 - 调用MiniMax API
int model_infer_cloud(const char *prompt, char *response, int max_len) {
    if (strlen(config.api_key) == 0) {
        printf("[Model] API Key not set!\n");
        snprintf(response, max_len, "请先设置API Key");
        return -1;
    }
    
    printf("[Model] Cloud infer (model: %s)...\n", config.model);
    printf("[Model] Prompt: %.50s...\n", prompt);
    
    // TODO: 实际调用API
    // curl -X POST "https://api.minimax.chat/v1/text/chatcompletion_v2" \
    //   -H "Authorization: Bearer $API_KEY" \
    //   -d '{"model":"abab6.5s-chat","messages":[{"role":"user","content":"$PROMPT"}]}'
    
    snprintf(response, max_len, "这是云端AI的回复: %s", prompt);
    printf("[Model] Response: %.50s...\n", response);
    return 0;
}

// 智能选择 - 本地优先
int model_infer(const char *prompt, char *response, int max_len) {
    if (model_loaded) {
        return model_infer_local(prompt, response, max_len);
    } else {
        return model_infer_cloud(prompt, response, max_len);
    }
}

// 流式推理
int model_infer_stream(const char *prompt, void (*callback)(const char *token)) {
    printf("[Model] Stream infer...\n");
    callback("这");
    callback("是");
    callback("流");
    callback("式");
    callback("输出");
    return 0;
}

// 卸载模型
int model_unload(void) {
    if (model_loaded) {
        printf("[Model] Local model unloaded\n");
        model_loaded = 0;
    }
    return 0;
}

// 获取模型信息
void model_info(void) {
    printf("\n=== Model Info ===\n");
    printf("Cloud Model: %s\n", config.model);
    printf("API Key: %s\n", strlen(config.api_key) > 0 ? "已设置" : "未设置");
    printf("Endpoint: %s\n", config.endpoint);
    printf("Temperature: %d\n", config.temperature);
    printf("Max Tokens: %d\n", config.max_tokens);
    printf("Local Loaded: %s\n", model_loaded ? "Yes" : "No");
    printf("==================\n\n");
}
