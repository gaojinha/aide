/**
 * 示例8: 日志使用
 */

#include <stdio.h>
#include "logger.h"

int main(void) {
    // 初始化日志
    log_init("/tmp/ai_assistant.log");
    log_set_level(LOG_DEBUG);
    
    // 写日志
    log_debug("调试信息");
    log_info("程序启动");
    log_info("用户: %s", "张三");
    log_error("发生错误: %d", 404);
    
    printf("日志示例完成\n");
    return 0;
}
