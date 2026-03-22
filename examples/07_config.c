/**
 * 示例7: 配置使用
 */

#include <stdio.h>
#include "config.h"

int main(void) {
    // 初始化
    config_init();
    
    // 设置配置
    config_set("language", "zh-CN");
    config_set("theme", "dark");
    config_set("ai_name", "王二狗");
    config_set("api_key", "sk-xxx");
    
    // 读取配置
    printf("语言: %s\n", config_get("language"));
    printf("主题: %s\n", config_get("theme"));
    printf("AI名字: %s\n", config_get("ai_name"));
    
    // 保存配置
    config_save("/data/config.txt");
    
    return 0;
}
