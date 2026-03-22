/**
 * 示例3: 记忆系统
 */

#include <stdio.h>
#include "user_memory.h"

int main(void) {
    // 初始化记忆
    memory_init();
    
    // 记住一些东西
    memory_remember("favorite_food", "火锅");
    memory_remember("favorite_music", "周杰伦");
    
    // 学习习惯
    memory_learn_context("跑步", "早上8点", "公园");
    
    // 回忆
    char value[128];
    if (memory_recall("favorite_food", value) == 0) {
        printf("你喜欢的食物: %s\n", value);
    }
    
    // 获取建议
    char suggestion[128];
    memory_suggest(suggestion);
    printf("建议: %s\n", suggestion);
    
    return 0;
}
