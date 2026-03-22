/**
 * aide - 主程序
 */

#include <stdio.h>
#include <unistd.h>
#include "ai_assistant.h"

extern int personality_init(void);
extern int memory_init(void);
extern int nlp_init(void);
extern int vision_init(void);
extern int voice_init(void);
extern int model_init(void);
extern int log_init(const char *filename);

// UI函数
extern int ui_init(void);
extern void ui_splash(void);
extern void ui_status_bar(void);
extern void ui_chat(const char *role, const char *msg);
extern void ui_progress(const char *label, int percent);

int main(int argc, char *argv[]) {
    ui_splash();
    printf("  aide v%s\n\n", AI_ASSISTANT_VERSION);

    log_init("/tmp/aide.log");
    ai_system_init();
    ui_init();
    
    personality_init();
    memory_init();
    nlp_init();
    vision_init();
    voice_init();
    model_init();
    
    printf("\n");
    ui_progress("Loading modules", 30);
    sleep(1);
    ui_progress("Loading AI", 70);
    sleep(1);
    ui_progress("Starting", 100);
    printf("\n\n");
    
    ui_status_bar();
    
    printf("\n");
    ui_chat("user", "你好！");
    ui_chat("aide", "你好！我是 aide，很高兴为你服务！");
    ui_chat("user", "今天天气怎么样？");
    ui_chat("aide", "今天天气晴朗，温度25°C！");
    
    printf("\n[Main] aide running...\n");
    sleep(2);
    
    ai_system_stop();
    printf("[Main] Done.\n");
    return 0;
}
