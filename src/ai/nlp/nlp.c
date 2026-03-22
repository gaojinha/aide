/**
 * NLP模块 - 自然语言理解
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

// 意图类型
typedef enum {
    INTENT_GREETING,     // 问候
    INTENT_QUERY,        // 查询
    INTENT_COMMAND,      // 命令
    INTENT_CHAT,        // 聊天
    INTENT_UNKNOWN       // 未知
} intent_t;

// 实体
typedef struct {
    char type[32];
    char value[128];
} entity_t;

// 解析结果
typedef struct {
    intent_t intent;
    char text[256];
    entity_t entities[5];
    int entity_count;
    double confidence;
} parse_result_t;

// 关键词匹配表
static const char* greeting_words[] = {"你好", "hi", "hello", "嗨", "早上好", "晚上好"};
static const char* query_words[] = {"什么是", "怎么", "如何", "为什么", "多少", "哪里"};
static const char* command_words[] = {"打开", "关闭", "播放", "停止", "设置", "帮"};

int nlp_init(void) {
    printf("[NLP] Initialized\n");
    return 0;
}

// 文本预处理
void nlp_preprocess(char *text) {
    // 去除首尾空格
    while (*text == ' ') text++;
    char *end = text + strlen(text) - 1;
    while (end > text && *end == ' ') *end-- = '\0';
    
    // 转小写(英文)
    for (int i = 0; text[i]; i++) {
        text[i] = tolower(text[i]);
    }
}

// 意图识别
intent_t nlp_recognize_intent(const char *text) {
    char lower[256];
    strncpy(lower, text, 255);
    nlp_preprocess(lower);
    
    for (int i = 0; i < sizeof(greeting_words)/sizeof(greeting_words[0]); i++) {
        if (strstr(lower, greeting_words[i])) return INTENT_GREETING;
    }
    for (int i = 0; i < sizeof(query_words)/sizeof(query_words[0]); i++) {
        if (strstr(lower, query_words[i])) return INTENT_QUERY;
    }
    for (int i = 0; i < sizeof(command_words)/sizeof(command_words[0]); i++) {
        if (strstr(lower, command_words[i])) return INTENT_COMMAND;
    }
    return INTENT_CHAT;
}

// 实体提取
int nlp_extract_entities(const char *text, entity_t *entities, int max) {
    int count = 0;
    char temp[256];
    strncpy(temp, text, 255);
    
    // 提取时间
    if (strstr(temp, "今天")) {
        strcpy(entities[count].type, "time");
        strcpy(entities[count].value, "today");
        count++;
    }
    if (strstr(temp, "明天")) {
        strcpy(entities[count].type, "time");
        strcpy(entities[count].value, "tomorrow");
        count++;
    }
    
    // 提取地点
    if (strstr(temp, "北京")) {
        strcpy(entities[count].type, "location");
        strcpy(entities[count].value, "beijing");
        count++;
    }
    if (strstr(temp, "上海")) {
        strcpy(entities[count].type, "location");
        strcpy(entities[count].value, "shanghai");
        count++;
    }
    
    return count;
}

// 解析文本
int nlp_understand(const char *text, parse_result_t *result) {
    printf("[NLP] Understanding: %s\n", text);
    
    strncpy(result->text, text, 255);
    result->intent = nlp_recognize_intent(text);
    result->entity_count = nlp_extract_entities(text, result->entities, 5);
    result->confidence = 0.85;
    
    const char *intent_names[] = {"greeting", "query", "command", "chat", "unknown"};
    printf("[NLP] Intent: %s (confidence: %.2f)\n", intent_names[result->intent], result->confidence);
    
    return 0;
}

// 生成回复
int nlp_generate(const char *input, const parse_result_t *ctx, char *response) {
    switch (ctx->intent) {
        case INTENT_GREETING:
            sprintf(response, "你好！有什么可以帮你的吗？");
            break;
        case INTENT_QUERY:
            sprintf(response, "让我帮你查一下...");
            break;
        case INTENT_COMMAND:
            sprintf(response, "好的，我来帮你处理。");
            break;
        case INTENT_CHAT:
            sprintf(response, "嗯，我在听。");
            break;
        default:
            sprintf(response, "我不太明白你说的。");
    }
    return 0;
}
