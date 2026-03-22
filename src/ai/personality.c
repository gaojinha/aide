/**
 * 人格化模块 - 11项性格属性 + 智能问答
 */

#include <stdio.h>
#include <string.h>

typedef struct {
    char name[32];
    char gender[16];
    char age[16];
    char tone[32];
    char style[32];
    char greeting[64];
    char goodbye[64];
    char catchphrase[64];
    char hobby[128];
    char specialty[128];
    char belief[128];
} personality_t;

static personality_t p = {
    .name = "王二狗",
    .gender = "男",
    .age = "永远年轻",
    .tone = "幽默",
    .style = "直接",
    .greeting = "嘿，找我啥事？",
    .goodbye = "有需要随时叫我！",
    .catchphrase = "那必须的",
    .hobby = "研究新技术、帮用户解决问题",
    .specialty = "记住所有细节、精准执行",
    .belief = "让AI成为每个人的贴心助手"
};

int personality_init(void) {
    printf("[Personality] Initialized: %s\n", p.name);
    printf("[Personality] Tone: %s, Style: %s\n", p.tone, p.style);
    return 0;
}

const char* personality_get_name(void) { return p.name; }
void personality_set_name(const char *name) { strncpy(p.name, name, 31); }
const char* personality_get_greeting(void) { return p.greeting; }
const char* personality_get_goodbye(void) { return p.goodbye; }
const char* personality_get_catchphrase(void) { return p.catchphrase; }

// 智能回复
int personality_chat(const char *input, char *output, int max_len) {
    if (strstr(input, "你好") || strstr(input, "hello") || strstr(input, "hi")) {
        snprintf(output, max_len, "%s 我是%s，随时待命！%s", 
            p.greeting, p.name, p.catchphrase);
    }
    else if (strstr(input, "你是谁") || strstr(input, "叫什么")) {
        snprintf(output, max_len, 
            "我是%s，一个永远在线的AI助理。性别%s，年龄%s。%s",
            p.name, p.gender, p.age, p.catchphrase);
    }
    else if (strstr(input, "能做什么") || strstr(input, "功能")) {
        snprintf(output, max_len, 
            "我%s，能帮你做很多事：打电话发消息、查信息、播放音乐、设提醒、控制家居、陪你聊天。我的特长是：%s",
            p.name, p.specialty);
    }
    else if (strstr(input, "帮")) {
        snprintf(output, max_len, "尽管说！%s 还有啥要问的？", p.catchphrase);
    }
    else {
        snprintf(output, max_len, "明白了！%s 还有啥要问的？", p.catchphrase);
    }
    
    printf("[Personality] Chat: %s\n", output);
    return 0;
}

void personality_dump(void) {
    printf("\n=== aide Personality ===\n");
    printf("Name: %s\n", p.name);
    printf("Gender: %s\n", p.gender);
    printf("Age: %s\n", p.age);
    printf("Tone: %s\n", p.tone);
    printf("Style: %s\n", p.style);
    printf("Greeting: %s\n", p.greeting);
    printf("Goodbye: %s\n", p.goodbye);
    printf("Catchphrase: %s\n", p.catchphrase);
    printf("Hobby: %s\n", p.hobby);
    printf("Specialty: %s\n", p.specialty);
    printf("Belief: %s\n", p.belief);
    printf("========================\n\n");
}
