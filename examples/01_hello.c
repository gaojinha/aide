/**
 * 示例1: Hello World
 */

#include <stdio.h>
#include "ai_assistant.h"

int main(void) {
    printf("Hello, aide!\n");
    
    // 初始化系统
    ai_system_init();
    ai_system_start();
    
    printf("System running...\n");
    
    ai_system_stop();
    return 0;
}
