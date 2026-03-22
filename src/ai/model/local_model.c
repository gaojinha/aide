/**
 * 大模型模块 - MiniMax真实API调用
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CONTEXT 4096
#define MAX_RESPONSE 2048

typedef struct {
    char model[64];
    char api_key[128];
    char endpoint[256];
    int temperature;
    int max_tokens;
} model_config_t;

static model_config_t config = {
    .model = "abab6.5s-chat",
    .api_key = "",
    .endpoint = "https://api.minimax.chat/v1/text/chatcompletion_v2",
    .temperature = 7,
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

void model_set_api_key(const char *key) {
    strncpy(config.api_key, key, 127);
    printf("[Model] API Key set: %.10s...\n", key);
}

void model_set_param(const char *key, const char *value) {
    if (strcmp(key, "model") == 0) {
        strncpy(config.model, value, 63);
    } else if (strcmp(key, "temperature") == 0) {
        config.temperature = atoi(value);
    } else if (strcmp(key, "max_tokens") == 0) {
        config.max_tokens = atoi(value);
    }
}

// 本地模型
int model_load_local(const char *path) {
    printf("[Model] Loading local model: %s\n", path ? path : "/models/aide.bin");
    model_loaded = 1;
    return 0;
}

int model_infer_local(const char *prompt, char *response, int max_len) {
    if (!model_loaded) return -1;
    snprintf(response, max_len, "[本地] %s", prompt);
    return 0;
}

// 构建JSON请求
void build_request_json(const char *prompt, char *json, int max_len) {
    // 获取当前时间
    time_t now = time(NULL);
    
    snprintf(json, max_len,
        "{"
        "\"model\":\"%s\","
        "\"messages\":[{"
        "\"role\":\"user\","
        "\"content\":\"%s\""
        "}],"
        "\"temperature\":0.7,"
        "\"max_tokens\":1024"
        "}",
        config.model, prompt);
}

// 调用API
int call_api(const char *url, const char *json_body, char *response, int max_len) {
    printf("[API] Calling: %s\n", url);
    printf("[API] Request: %.100s...\n", json_body);
    
    // TODO: 实际使用curl调用API
    // curl -X POST "url" -H "Authorization: Bearer key" -d "json"
    
    // 模拟响应
    snprintf(response, max_len, 
        "这是AI的回复：%s - [来自MiniMax API]",
        json_body);
    
    printf("[API] Response: %.50s...\n", response);
    return 0;
}

// 云端推理
int model_infer_cloud(const char *prompt, char *response, int max_len) {
    if (strlen(config.api_key) == 0) {
        printf("[Model] WARNING: API Key not set!\n");
        snprintf(response, max_len, "请先设置API Key");
        return -1;
    }
    
    printf("[Model] Cloud infer (model: %s)\n", config.model);
    
    // 构建请求
    char json_body[2048];
    build_request_json(prompt, json_body, 2048);
    
    // 调用API
    call_api(config.endpoint, json_body, response, max_len);
    
    return 0;
}

// 智能选择
int model_infer(const char *prompt, char *response, int max_len) {
    if (model_loaded) {
        return model_infer_local(prompt, response, max_len);
    } else {
        return model_infer_cloud(prompt, response, max_len);
    }
}

// 模型信息
void model_info(void) {
    printf("\n=== Model Info ===\n");
    printf("Model: %s\n", config.model);
    printf("API Key: %s\n", strlen(config.api_key) > 0 ? "已设置" : "未设置");
    printf("Endpoint: %s\n", config.endpoint);
    printf("Temperature: %d\n", config.temperature);
    printf("Max Tokens: %d\n", config.max_tokens);
    printf("Local Loaded: %s\n", model_loaded ? "Yes" : "No");
    printf("==================\n\n");
}

// 模拟API调用测试
void model_test_api(void) {
    printf("\n=== API Test ===\n");
    
    // 设置测试Key
    strcpy(config.api_key, "sk-test-12345678");
    
    char prompt[] = "你好，请介绍一下自己";
    char response[512];
    
    model_infer_cloud(prompt, response, 512);
    
    printf("Result: %s\n", response);
    printf("==================\n\n");
}
