#include <stdio.h>
#include <string.h>

#define MAX_SKILLS 50

// 技能
typedef struct {
    char name[32];
    char trigger[32];  // 触发词
    char description[128];
    int enabled;
} skill_t;

static skill_t skills[MAX_SKILLS];
static int skill_count = 0;

// 注册技能
int skills_register(const char *name, const char *trigger, const char *desc) {
    if (skill_count >= MAX_SKILLS) return -1;
    
    skill_t *s = &skills[skill_count];
    strncpy(s->name, name, 31);
    strncpy(s->trigger, trigger, 31);
    strncpy(s->description, desc, 127);
    s->enabled = 1;
    skill_count++;
    
    return 0;
}

// 初始化
void skills_init(void) {
    printf("[Skills] Initialized\n");
    
    // 内置技能
    skills_register("天气查询", "天气", "查询指定城市天气");
    skills_register("音乐播放", "播放", "播放音乐");
    skills_register("讲故事", "讲故事", "讲一个有趣的故事");
    skills_register("设置闹钟", "闹钟", "设置提醒闹钟");
    skills_register("打开灯", "开灯", "控制GPIO灯");
    skills_register("关闭灯", "关灯", "关闭GPIO灯");
    skills_register("查百科", "什么是", "查询百科知识");
    skills_register("算数学", "计算", "数学计算");
    skills_register("翻译", "翻译", "中英互译");
    skills_register("新闻", "新闻", "播报最新新闻");
    
    printf("  Built-in skills: %d\n", skill_count);
}

// 匹配技能
const char* skills_match(const char *text) {
    for (int i = 0; i < skill_count; i++) {
        if (skills[i].enabled && strstr(text, skills[i].trigger)) {
            return skills[i].name;
        }
    }
    return NULL;
}

// 执行技能
int skills_execute(const char *skill_name, const char *params) {
    printf("\n=== Skill Execution ===\n");
    printf("Skill: %s\n", skill_name);
    printf("Params: %s\n", params ? params : "(none)");
    
    // 模拟执行
    if (strcmp(skill_name, "天气查询") == 0) {
        printf("Result: 永济今天天气晴, 20-28°C\n");
    } else if (strcmp(skill_name, "音乐播放") == 0) {
        printf("Result: 正在播放: 演员 - 薛之谦\n");
    } else if (strcmp(skill_name, "讲故事") == 0) {
        printf("Result: 从前有座山...\n");
    } else if (strcmp(skill_name, "设置闹钟") == 0) {
        printf("Result: 闹钟已设置为 07:00\n");
    } else if (strcmp(skill_name, "打开灯") == 0) {
        printf("Result: 灯已打开\n");
    } else if (strcmp(skill_name, "关闭灯") == 0) {
        printf("Result: 灯已关闭\n");
    } else {
        printf("Result: 技能执行完成\n");
    }
    
    printf("========================\n\n");
    return 0;
}

// 列出技能
void skills_list(void) {
    printf("\n=== Skills (%d) ===\n", skill_count);
    
    for (int i = 0; i < skill_count; i++) {
        printf("%d. [%s] %s: %s\n",
            i+1,
            skills[i].enabled ? "ON " : "OFF",
            skills[i].name,
            skills[i].description);
    }
    printf("=====================\n\n");
}

// 启用/禁用技能
int skills_enable(const char *name, int enable) {
    for (int i = 0; i < skill_count; i++) {
        if (strcmp(skills[i].name, name) == 0) {
            skills[i].enabled = enable;
            printf("[Skills] %s %s\n", name, enable ? "enabled" : "disabled");
            return 0;
        }
    }
    return -1;
}

// 测试
void skills_test(void) {
    printf("\n=== Skills Test ===\n");
    
    skills_init();
    skills_list();
    
    printf("Testing skill matching:\n");
    
    const char *texts[] = {
        "今天天气怎么样",
        "播放一首歌",
        "给我讲故事",
        "设置明天7点闹钟",
        "打开客厅灯"
    };
    
    for (int i = 0; i < 5; i++) {
        const char *skill = skills_match(texts[i]);
        if (skill) {
            printf("\nText: %s\n", texts[i]);
            printf("Matched: %s\n", skill);
            skills_execute(skill, "test params");
        }
    }
    
    printf("==================\n\n");
}
