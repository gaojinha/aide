/**
 * 人格化模块 - 11项性格属性
 */

#include <stdio.h>
#include <string.h>

// 11项性格属性
typedef struct {
    // 基础信息
    char name[32];           // 名字
    char gender[16];         // 性别
    char age[16];            // 年龄
    
    // 性格特征
    char tone[32];          // 语气
    char style[32];         // 风格
    
    // 说话方式
    char greeting[64];      // 打招呼
    char goodbye[64];       // 告别
    char catchphrase[64];   // 口头禅
    
    // 价值观
    char hobby[128];        // 爱好
    char specialty[128];    // 特长
    char belief[128];       // 信念
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
