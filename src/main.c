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
extern int camera_init(void);
extern void log_test(void);
extern int config_init(void);
extern void config_list(void);
extern int sensor_init(void);
extern void sensor_test(void);

extern int gpio_init(void);
extern void gpio_test(void);

extern int ui_init(void);
extern void ui_splash(void);

int main(int argc, char *argv[]) {
    ui_splash();
    printf("  aide v%s\n\n", AI_ASSISTANT_VERSION);

    log_init("/tmp/aide.log");
    config_init();
    sensor_init();
    
    printf("\n=== GPIO Test ===\n");
    gpio_init();
    gpio_test();
    
    ai_system_init();
    ui_init();
    
    personality_init();
    memory_init();
    nlp_init();
    vision_init();
    voice_init();
    model_init();
    settings_init();
    camera_init();
    
    printf("\n[Main] aide running...\n");
    sleep(2);
    
    ai_system_stop();
    log_close();
    printf("[Main] Done.\n");
    return 0;
}
