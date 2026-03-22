/**
 * AI Assistant - 主程序
 * 基于RK3568的AI手机系统
 */

#include <stdio.h>
#include <stdlib.h>
#include "ai_assistant.h"

int main(int argc, char *argv[]) {
    printf("===========================================\n");
    printf("  AI Assistant v%s\n", AI_ASSISTANT_VERSION);
    printf("  Build: %s\n", AI_ASSISTANT_BUILD);
    printf("  Platform: RK3568\n");
    printf("===========================================\n\n");

    // 初始化系统
    printf("[System] Initializing...\n");
    if (ai_system_init() != 0) {
        fprintf(stderr, "[System] Init failed!\n");
        return -1;
    }
    printf("[System] Init OK\n");

    // 启动系统
    printf("[System] Starting...\n");
    if (ai_system_start() != 0) {
        fprintf(stderr, "[System] Start failed!\n");
        return -1;
    }
    printf("[System] Started OK\n");

    printf("[System] Running...\n");
    
    // 主循环 - 等待信号
    for (int i = 0; i < 3; i++) {
        printf("[System] Tick...\n"); sleep(1);
    }

    // 停止系统
    ai_system_stop();
    
    return 0;
}
