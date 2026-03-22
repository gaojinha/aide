/**
 * 示例9: UI使用
 */

#include <stdio.h>
#include "ui.h"

int main(void) {
    // 初始化UI
    ui_init();
    
    // 显示主菜单
    ui_main_menu();
    
    // 对话
    ui_chat_interface("你好");
    ui_chat_interface("今天天气怎么样？");
    
    // 状态
    ui_status_bar("在线");
    
    // 进度条
    for (int i = 0; i <= 100; i += 10) {
        ui_progress_bar(i);
    }
    
    return 0;
}
