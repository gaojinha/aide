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
extern void model_set_api_key(const char *key);
extern void model_set_param(const char *key, const char *value);
extern int model_infer(const char *prompt, char *resp, int max);
extern void model_info(void);
extern int settings_init(void);
extern int settings_set_string(const char *key, const char *value);
extern int settings_set_int(const char *key, int value);
extern const char* settings_get_string(const char *key);
extern int settings_get_int(const char *key);
extern void settings_list(void);

extern int ui_init(void);
extern void ui_splash(void);
extern void ui_chat(const char *role, const char *msg);

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
    
    printf("\n--- Settings ---\n");
    settings_init();
    settings_set_string("api_key", "sk-xxx");
    settings_set_int("volume", 75);
    settings_set_string("wake_word", "你好 aide");
    settings_list();
    
    printf("\n--- Model ---\n");
    model_set_api_key("sk-test-key");
    model_set_param("temperature", "0.7");
    model_info();
    
    // 测试对话
    printf("\n--- AI Chat ---\n");
    char response[512];
    model_infer("你好，请介绍一下自己", response, 512);
    ui_chat("user", "你好，请介绍一下自己");
    ui_chat("aide", response);
    
    printf("\n[Main] aide running...\n");
    sleep(2);
    
    ai_system_stop();
    printf("[Main] Done.\n");
    return 0;
}
