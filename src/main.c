/**
 * aide - 主程序
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ai_assistant.h"

extern int personality_init(void);
extern int memory_init(void);
extern int voice_init(void);
extern int model_init(void);
extern int nlp_init(void);
extern int vision_init(void);
extern int config_init(void);
extern int log_init(const char *filename);
extern int http_get(const char *url, void *resp);
extern int http_post(const char *url, const char *data, void *resp);
extern int websocket_init(void);

int main(int argc, char *argv[]) {
    printf("===========================================\n");
    printf("  aide v%s\n", AI_ASSISTANT_VERSION);
    printf("  Build: %s\n", AI_ASSISTANT_BUILD);
    printf("  Platform: RK3568\n");
    printf("===========================================\n\n");

    log_init("/tmp/aide.log");
    ai_system_init();
    config_init();
    
    personality_init();
    memory_init();
    nlp_init();
    vision_init();
    voice_init();
    model_init();
    
    printf("\n--- Network ---\n");
    http_get("http://api.example.com/status", NULL);
    http_post("http://api.example.com/data", "{\"test\":1}", NULL);
    websocket_init();
    
    printf("\n[Main] aide running...\n");
    sleep(2);
    
    ai_system_stop();
    printf("[Main] Done.\n");
    return 0;
}
