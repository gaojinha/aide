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
extern int settings_init(void);
extern int wizard_run(void);
extern int wizard_is_done(void);

// 语音播报实现
void wizard_speak(const char *text) {
    printf("[Voice] 🔊 %s\n", text);
}

extern int ui_init(void);
extern void ui_splash(void);

int main(int argc, char *argv[]) {
    // 首次设置
    if (!wizard_is_done()) {
        printf("\n=== First Time Setup ===\n");
        wizard_run();
        wizard_run();
        wizard_run();
        wizard_run();
        wizard_run();
        wizard_run();
    }
    
    ui_splash();
    printf("  aide v%s\n", AI_ASSISTANT_VERSION);

    log_init("/tmp/aide.log");
    ai_system_init();
    
    personality_init();
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
