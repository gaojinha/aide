/**
 * 示例2: 人格化使用
 */

#include <stdio.h>
#include <string.h>
#include "personality.h"

int main(void) {
    // 初始化人格
    personality_init();
    
    // 设置人格
    personality_set("name", "王二狗");
    personality_set("age", "28");
    personality_set("tone", "俏皮");
    
    // 显示人格
    personality_show();
    
    // 生成回复
    char response[128];
    personality_generate("你好", response);
    printf("回复: %s\n", response);
    
    return 0;
}
