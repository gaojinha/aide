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
extern int sensor_init(void);
extern int gpio_init(void);
extern int scheduler_init(void);
extern int ntp_init(void);
extern int push_init(void);
extern int ota_init(void);
extern int security_init(void);
extern int auth_init(void);
extern int acl_init(void);
extern int secureboot_init(void);
extern int secure_storage_init(void);
extern int firewall_init(void);
extern int wifi_init(void);
extern int bluetooth_init(void);
extern int audio_init(void);
extern int video_init(void);
extern int power_init(void);
extern int ir_init(void);
extern int file_manager_init(void);
extern void mobile_app_init(void);
extern void mobile_app_test(void);
extern void webadmin_init(int port);
extern void webadmin_test(void);
extern void skills_init(void);
extern void skills_test(void);
extern void scene_test(void);
extern void workflow_test(void);
extern void study_test(void);
extern void health_test(void);
extern void ent_test(void);
extern void family_test(void);
extern void finance_test(void);
extern void life_test(void);

extern void emergency_test(void);
extern void document_test(void);
extern void language_test(void);
extern void reading_test(void);
extern void social_test(void);
extern void sdk_test(void);
extern void multidevice_test(void);
extern void monitoring_test(void);
extern void biometric_test(void);
extern void contacts_test(void);
extern void imagegen_test(void);
extern void knowledge_test(void);
extern void vector_test(void);
extern void ussd_test(void);
extern void ftp_test(void);
extern void email_test(void);

extern int ui_init(void);
extern void ui_splash(void);

int main(int argc, char *argv[]) {
    ui_splash();
    printf("  aide v%s\n\n", AI_ASSISTANT_VERSION);

    log_init("/tmp/aide.log");
    config_init();
    sensor_init();
    gpio_init();
    scheduler_init();
    ntp_init();
    push_init();
    ota_init();
    security_init();
    auth_init();
    acl_init();
    secureboot_init();
    secure_storage_init();
    firewall_init();
    wifi_init();
    bluetooth_init();
    audio_init();
    video_init();
    power_init();
    ir_init();
    file_manager_init();
    mobile_app_init();
    mobile_app_test();
    webadmin_init(8088);
    webadmin_test();
    skills_init();
    skills_test();
    scene_test();
    workflow_test();
    study_test();
    health_test();
    ent_test();
    family_test();
    finance_test();
    life_test();
    
    emergency_test();
    document_test();
    language_test();
    reading_test();
    social_test();
    sdk_test();
    multidevice_test();
    monitoring_test();
    biometric_test();
    contacts_test();
    imagegen_test();
    knowledge_test();
    vector_test();
    ussd_test();
    ftp_test();
    email_test();
    
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
