/**
 * aide - 主程序
 */

#include <stdio.h>
#include <unistd.h>
#include "ai_assistant.h"

extern int personality_init(void);
extern void personality_dump(void);
extern const char* personality_get_greeting(void);
extern const char* personality_get_catchphrase(void);

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

int main(int argc, char *argv[]) {
    if (!wizard_is_done()) {
        printf("\n=== Setup ===\n");
        for (int i = 0; i < 6; i++) wizard_run();
    }
    
    ui_splash();
    printf("  aide v%s\n", AI_ASSISTANT_VERSION);

    log_init("/tmp/aide.log");
    ai_system_init();
    ui_init();
    
    personality_init();
    personality_dump();
    
    memory_init();
    nlp_init();
    vision_init();
    voice_init();
    model_init();
    settings_init();
    
    printf("\n=== Demo ===\n");
    printf("User: 你好\n");
    printf("aide: %s\n", personality_get_greeting());
    printf("User: 今天天气\n");
    printf("aide: 晴天，25度。%s\n", personality_get_catchphrase());
    
    printf("\n[Main] aide running...\n");
    sleep(2);
    
    ai_system_stop();
    printf("[Main] Done.\n");
    return 0;
}
