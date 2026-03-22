/**
 * aide - 主程序
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "ai_assistant.h"

extern int personality_init(void);
extern int personality_chat(const char *input, char *output, int max_len);

extern int memory_init(void);
extern int nlp_init(void);
extern int vision_init(void);
extern int voice_init(void);
extern void voice_test(void);

extern int model_init(void);
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
    
    // 语音测试
    voice_test();
    
    printf("\n[Main] aide running...\n");
    sleep(2);
    
    ai_system_stop();
    printf("[Main] Done.\n");
    return 0;
}
