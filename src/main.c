/**
 * aide - 主程序
 */

#include <stdio.h>
#include <unistd.h>
#include "ai_assistant.h"

extern int personality_init(void);
extern void personality_dump(void);
extern int personality_chat(const char *input, char *output, int max_len);

extern int memory_init(void);
extern int nlp_init(void);
extern int vision_init(void);
extern int voice_init(void);
extern int model_init(void);
extern int settings_init(void);
extern int wizard_run(void);
extern int wizard_is_done(void);

extern int ui_init(void);
extern void ui_splash(void);

void test_chat(const char *input) {
    char output[512];
    personality_chat(input, output, 512);
    printf("\n👤 你: %s\n", input);
    printf("🤖 aide: %s\n", output);
}

int main(int argc, char *argv[]) {
    ui_splash();
    printf("  aide v%s\n\n", AI_ASSISTANT_VERSION);

    log_init("/tmp/aide.log");
    ai_system_init();
    
    personality_init();
    personality_dump();
    
    // 测试人格问答
    printf("\n=== 人格问答测试 ===\n");
    test_chat("你好");
    test_chat("你是谁");
    test_chat("你能做什么");
    test_chat("帮帮我");
    
    memory_init();
    nlp_init();
    vision_init();
    voice_init();
    model_init();
    settings_init();
    
    printf("\n[Main] aide running...\n");
    sleep(2);
    
    ai_system_stop();
    printf("[Main] Done.\n");
    return 0;
}
