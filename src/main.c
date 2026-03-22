/**
 * aide - 主程序
 * 基于RK3568的AI手机系统
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ai_assistant.h"

// 外部模块初始化函数声明
extern int personality_init(void);
extern int memory_init(void);
extern int voice_init(void);
extern int model_init(void);
extern int nlp_init(void);
extern int vision_init(void);
extern int config_init(void);
extern int log_init(const char *filename);

int main(int argc, char *argv[]) {
    printf("===========================================\n");
    printf("  aide v%s\n", AI_ASSISTANT_VERSION);
    printf("  Build: %s\n", AI_ASSISTANT_BUILD);
    printf("  Platform: RK3568\n");
    printf("===========================================\n\n");

    // 初始化日志
    printf("[Main] Initializing modules...\n");
    log_init("/tmp/aide.log");
    
    // 初始化系统核心
    printf("\n--- Core Modules ---\n");
    if (ai_system_init() != 0) {
        fprintf(stderr, "[Main] System init failed!\n");
        return -1;
    }
    
    // 初始化配置
    printf("[Main] Config init...\n");
    config_init();
    
    // 初始化AI模块
    printf("\n--- AI Modules ---\n");
    personality_init();
    memory_init();
    nlp_init();
    vision_init();
    voice_init();
    model_init();
    
    printf("\n[Main] All modules initialized OK\n");
    
    // 启动系统
    printf("\n[Main] Starting system...\n");
    if (ai_system_start() != 0) {
        fprintf(stderr, "[Main] System start failed!\n");
        return -1;
    }
    
    printf("\n[Main] aide is running!\n");
    printf("[Main] Press Ctrl+C to stop\n\n");
    
    // 主循环
    for (int i = 0; i < 3; i++) {
        printf("[Main] Tick %d/3...\n", i+1);
        sleep(1);
    }

    // 停止系统
    printf("\n[Main] Stopping...\n");
    ai_system_stop();
    printf("[Main] Stopped.\n");
    
    return 0;
}
