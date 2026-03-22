/**
 * UI界面模块
 */

#include <stdio.h>
#include <string.h>

// 颜色
#define C_RESET  "\033[0m"
#define C_RED    "\033[31m"
#define C_GREEN  "\033[32m"
#define C_YELLOW "\033[33m"
#define C_BLUE   "\033[34m"
#define C_CYAN   "\033[36m"

// 界面初始化
int ui_init(void) {
    printf("[UI] Framework initialized\n");
    return 0;
}

// 主菜单
void ui_main_menu(void) {
    printf(C_BLUE"\n╔══════════════════════════════════╗\n"C_RESET);
    printf(C_BLUE"║      AI助理 v0.1.0             ║\n"C_RESET);
    printf(C_BLUE"╠══════════════════════════════════╣\n"C_RESET);
    printf(C_BLUE"║  1. 🤖 对话                    ║\n"C_RESET);
    printf(C_BLUE"║  2. 📞 电话                    ║\n"C_RESET);
    printf(C_BLUE"║  3. 💬 消息                    ║\n"C_RESET);
    printf(C_BLUE"║  4. 🎵 音乐                    ║\n"C_RESET);
    printf(C_BLUE"║  5. ⚙️ 设置                    ║\n"C_RESET);
    printf(C_BLUE"║  0. 🚪 退出                    ║\n"C_RESET);
    printf(C_BLUE"╚══════════════════════════════════╝\n"C_RESET);
    printf("请选择: ");
}

// 对话界面
void ui_chat_interface(const char *msg) {
    printf(C_CYAN"\n👤 你: %s\n"C_RESET, msg);
    printf(C_GREEN"🤖 AI: 收到消息\n"C_RESET);
}

// 状态栏
void ui_status_bar(const char *status) {
    printf(C_YELLOW"\n[状态: %s]\n"C_RESET, status);
}

// 进度条
void ui_progress_bar(int percent) {
    printf("\r[");
    for (int i = 0; i < 20; i++) {
        if (i < percent / 5) printf("█");
        else printf(" ");
    }
    printf("] %d%%", percent);
    if (percent == 100) printf("\n");
}
