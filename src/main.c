/**
 * aide - 主程序
 */

#include <stdio.h>
#include <unistd.h>
#include "ai_assistant.h"

extern int personality_init(void);
extern int personality_chat(const char *input, char *output, int max_len);

extern int memory_init(void);
extern int nlp_init(void);
extern int vision_init(void);
extern int voice_init(void);
extern int model_init(void);
extern void model_set_api_key(const char *key);
extern void model_test_api(void);

extern int settings_init(void);

extern int ui_init(void);
extern void ui_splash(void);

int main(int argc, char *argv[]) {
    ui_splash();
    printf("  aide v%s\n\n", AI_ASSISTANT_VERSION);

    log_init("/tmp/aide.log");
    ai_system_init();
    
    personality_init();
    memory_init();
    nlp_init();
    vision_init();
    voice_init();
    model_init();
    settings_init();
    
    // 测试API
    model_test_api();
    
    // 测试人格问答
    printf("\n=== Chat Test ===\n");
    char output[512];
    personality_chat("你好", output, 512);
    printf("User: 你好\n");
    printf("aide: %s\n", output);
    
    printf("\n[Main] aide running...\n");
    sleep(2);
    
    ai_system_stop();
    printf("[Main] Done.\n");
    return 0;
}
