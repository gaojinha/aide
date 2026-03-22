/**
 * aide - 主程序
 */

#include <stdio.h>
#include <unistd.h>
#include "ai_assistant.h"
#include "network.h"
#include "storage.h"

extern int personality_init(void);
extern int memory_init(void);
extern int voice_init(void);
extern int model_init(void);
extern int nlp_init(void);
extern int vision_init(void);
extern int config_init(void);
extern int log_init(const char *filename);
extern int http_get(const char *url, void *resp);
extern int websocket_init(void);
extern int storage_init(const char *path);
extern int storage_set_string(const char *key, const char *value);
extern int network_init(void);
extern int network_wifi_scan(wifi_ap_t *aps, int max);
extern int network_wifi_connect(const char *ssid, const char *pass);
extern int network_get_status(network_info_t *info);

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
    
    printf("\n--- Network Driver ---\n");
    network_init();
    
    wifi_ap_t aps[10];
    int count = network_wifi_scan(aps, 10);
    for (int i = 0; i < count; i++) {
        printf("  [%d] %s (信号: %d dBm)\n", i+1, aps[i].ssid, aps[i].rssi);
    }
    
    network_wifi_connect("MyWiFi", "password123");
    
    network_info_t info;
    network_get_status(&info);
    printf("  IP: %s\n", info.ip);
    
    printf("\n[Main] aide running...\n");
    sleep(2);
    
    ai_system_stop();
    printf("[Main] Done.\n");
    return 0;
}
