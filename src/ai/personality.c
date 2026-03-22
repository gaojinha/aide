/**
 * 人格化模块 - AI个性化配置
 */

#include <stdio.h>
#include <string.h>

typedef struct {
    char name[64];
    char gender[16];
    int age;
    char birthday[32];
    char personality[32];
    char hobbies[256];
    char skills[256];
    char expertise[256];
    char address[128];
    char tone[32];
    char catchphrase[64];
    char age_str[16];  // 用于返回
} personality_t;

static personality_t current;

int personality_init(void) {
    strcpy(current.name, "王二狗");
    strcpy(current.gender, "男");
    current.age = 28;
    strcpy(current.birthday, "1998年5月15日");
    strcpy(current.personality, "稳重幽默");
    strcpy(current.hobbies, "科技、美食、旅行");
    strcpy(current.skills, "解决问题、聊天陪伴");
    strcpy(current.expertise, "编程、烹饪");
    strcpy(current.address, "山西省永济市");
    strcpy(current.tone, "俏皮");
    strcpy(current.catchphrase, "没问题，包在我身上");
    sprintf(current.age_str, "%d", current.age);
    printf("[Personality] Initialized: %s\n", current.name);
    return 0;
}

int personality_set(const char *key, const char *value) {
    if (strcmp(key, "name") == 0) strcpy(current.name, value);
    else if (strcmp(key, "gender") == 0) strcpy(current.gender, value);
    else if (strcmp(key, "age") == 0) { current.age = atoi(value); sprintf(current.age_str, "%d", current.age); }
    else if (strcmp(key, "birthday") == 0) strcpy(current.birthday, value);
    else if (strcmp(key, "personality") == 0) strcpy(current.personality, value);
    else if (strcmp(key, "hobbies") == 0) strcpy(current.hobbies, value);
    else if (strcmp(key, "skills") == 0) strcpy(current.skills, value);
    else if (strcmp(key, "expertise") == 0) strcpy(current.expertise, value);
    else if (strcmp(key, "address") == 0) strcpy(current.address, value);
    else if (strcmp(key, "tone") == 0) strcpy(current.tone, value);
    else if (strcmp(key, "catchphrase") == 0) strcpy(current.catchphrase, value);
    printf("[Personality] Set %s = %s\n", key, value);
    return 0;
}

const char* personality_get(const char *key) {
    if (strcmp(key, "name") == 0) return current.name;
    if (strcmp(key, "gender") == 0) return current.gender;
    if (strcmp(key, "age") == 0) return current.age_str;
    if (strcmp(key, "birthday") == 0) return current.birthday;
    if (strcmp(key, "personality") == 0) return current.personality;
    if (strcmp(key, "hobbies") == 0) return current.hobbies;
    if (strcmp(key, "skills") == 0) return current.skills;
    if (strcmp(key, "expertise") == 0) return current.expertise;
    if (strcmp(key, "address") == 0) return current.address;
    if (strcmp(key, "tone") == 0) return current.tone;
    if (strcmp(key, "catchphrase") == 0) return current.catchphrase;
    return NULL;
}

void personality_show(void) {
    printf("\n=== 人格信息 ===\n");
    printf("名字: %s\n", current.name);
    printf("性别: %s\n", current.gender);
    printf("年龄: %s岁\n", current.age_str);
    printf("出生日期: %s\n", current.birthday);
    printf("性格: %s\n", current.personality);
    printf("爱好: %s\n", current.hobbies);
    printf("擅长: %s\n", current.skills);
    printf("特长: %s\n", current.expertise);
    printf("地址: %s\n", current.address);
    printf("语气: %s\n", current.tone);
    printf("口头禅: %s\n", current.catchphrase);
    printf("================\n\n");
}

int personality_generate(const char *input, char *output) {
    if (strcmp(current.tone, "俏皮") == 0) {
        sprintf(output, "%s %s", current.catchphrase, input);
    } else {
        sprintf(output, "收到: %s", input);
    }
    return 0;
}

// 保存配置到文件
int personality_save(const char *filename) {
    FILE *f = fopen(filename, "w");
    if (!f) return -1;
    fprintf(f, "name=%s\n", current.name);
    fprintf(f, "gender=%s\n", current.gender);
    fprintf(f, "age=%s\n", current.age_str);
    fprintf(f, "birthday=%s\n", current.birthday);
    fprintf(f, "personality=%s\n", current.personality);
    fprintf(f, "hobbies=%s\n", current.hobbies);
    fprintf(f, "skills=%s\n", current.skills);
    fprintf(f, "expertise=%s\n", current.expertise);
    fprintf(f, "address=%s\n", current.address);
    fprintf(f, "tone=%s\n", current.tone);
    fprintf(f, "catchphrase=%s\n", current.catchphrase);
    fclose(f);
    printf("[Personality] Saved to %s\n", filename);
    return 0;
}

// 从文件加载配置
int personality_load(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) return -1;
    
    char line[256];
    while (fgets(line, sizeof(line), f)) {
        char key[64], value[128];
        if (sscanf(line, "%63[^=]=%127[^\n]", key, value) == 2) {
            personality_set(key, value);
        }
    }
    fclose(f);
    printf("[Personality] Loaded from %s\n", filename);
    return 0;
}
