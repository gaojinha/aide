/**
 * aide - 主程序
 */

#include <stdio.h>
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
extern int storage_init(const char *path);
extern int storage_write(const char *key, const void *data, size_t len);
extern int storage_read(const char *key, void *data, size_t max_len);
extern int storage_delete(const char *key);

int main(int argc, char *argv[]) {
    printf("===========================================\n");
    printf("  aide v%s\n", AI_ASSISTANT_VERSION);
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
    websocket_init();
    
    printf("\n--- Storage ---\n");
    storage_init("/tmp/aide_data");
    storage_set_string("name", "王二狗");
    storage_set_string("age", "28");
    storage_set_string("city", "永济");
    
    char value[256];
    storage_get_string("name", value, 256);
    printf("[Main] Read: name=%s\n", value);
    
    storage_delete("age");
    
    printf("\n[Main] aide running...\n");
    sleep(2);
    
    ai_system_stop();
    printf("[Main] Done.\n");
    return 0;
}
