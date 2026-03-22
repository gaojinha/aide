/**
 * UI模块 - 控制台界面
 */

#include <stdio.h>
#include <string.h>
#include <time.h>

// 颜色
#define C_RESET  "\033[0m"
#define C_RED    "\033[31m"
#define C_GREEN  "\033[32m"
#define C_YELLOW "\033[33m"
#define C_BLUE   "\033[34m"
#define C_CYAN   "\033[36m"
#define C_BOLD   "\033[1m"

// UI状态
typedef struct {
    char status[32];      // 在线/离线/忙碌
    int battery;          // 电量
    char network[16];     // WiFi/4G
    int volume;           // 音量
    int brightness;       // 亮度
} ui_status_t;

static ui_status_t ui_status = {
    .status = "在线",
    .battery = 85,
    .network = "WiFi",
    .volume = 70,
    .brightness = 80
};

// 初始化UI
int ui_init(void) {
    printf("[UI] Framework initialized\n");
    return 0;
}

// 标题栏
void ui_header(const char *title) {
    printf(C_BLUE"\n╔═══════════════════════════════════╗\n"C_RESET);
    printf(C_BLUE"║  %-33s║\n"C_RESET, title);
    printf(C_BLUE"╚═══════════════════════════════════╝\n"C_RESET);
}

// 主菜单
int ui_main_menu(void) {
    printf(C_BLUE"\n╔═══════════════════════════════════╗\n"C_RESET);
    printf(C_BLUE"║       aide v0.1.0              ║\n"C_RESET);
    printf(C_BLUE"╠═══════════════════════════════════╣\n"C_RESET);
    printf(C_BLUE"║  1. 🤖 AI对话                 ║\n"C_RESET);
    printf(C_BLUE"║  2. 📞 电话                   ║\n"C_RESET);
    printf(C_BLUE"║  3. 💬 消息                   ║\n"C_RESET);
    printf(C_BLUE"║  4. 🎵 音乐                   ║\n"C_RESET);
    printf(C_BLUE"║  5. 🌐 浏览器                 ║\n"C_RESET);
    printf(C_BLUE"║  6. ⚙️ 设置                   ║\n"C_RESET);
    printf(C_BLUE"║  0. 🚪 退出                   ║\n"C_RESET);
    printf(C_BLUE"╚═══════════════════════════════════╝\n"C_RESET);
    printf("请选择: ");
    return 0;
}

// 状态栏
void ui_status_bar(void) {
    time_t now = time(NULL);
    struct tm *tm = localtime(&now);
    
    printf(C_YELLOW"\n┌─ aide ─────────────────────┐\n"C_RESET);
    printf(C_YELLOW"│ %02d:%02d │ %s │ 🔋%d%% │ %s │\n"C_RESET,
           tm->tm_hour, tm->tm_min,
           ui_status.status,
           ui_status.battery,
           ui_status.network);
    printf(C_YELLOW"└──────────────────────────────┘\n"C_RESET);
}

// 对话界面
void ui_chat(const char *role, const char *msg) {
    if (strcmp(role, "user") == 0) {
        printf(C_CYAN"\n👤 你:\n"C_RESET);
    } else {
        printf(C_GREEN"\n🤖 aide:\n"C_RESET);
    }
    printf("  %s\n", msg);
}

// 消息提示
void ui_notify(const char *title, const char *msg) {
    printf(C_GREEN"\n📢 %s\n"C_RESET, title);
    printf("   %s\n", msg);
}

// 确认对话框
int ui_confirm(const char *prompt) {
    printf(C_YELLOW"\n❓ %s (y/n): "C_RESET, prompt);
    char c = getchar();
    return (c == 'y' || c == 'Y') ? 1 : 0;
}

// 进度条
void ui_progress(const char *label, int percent) {
    printf("\r%s: [", label);
    int bars = percent / 5;
    for (int i = 0; i < 20; i++) {
        if (i < bars) printf("█");
        else printf(" ");
    }
    printf("] %d%%", percent);
    if (percent >= 100) printf("\n");
    fflush(stdout);
}

// 设置状态
void ui_set_status(const char *status) {
    strncpy(ui_status.status, status, 31);
}

void ui_set_battery(int percent) {
    ui_status.battery = percent;
}

void ui_set_network(const char *net) {
    strncpy(ui_status.network, net, 15);
}

// 显示启动画面
void ui_splash(void) {
    printf(C_BLUE"\n");
    printf("  ██████╗ ███████╗███████╗██╗     ██╗███╗   ██╗███████╗\n");
    printf("  ██╔══██╗██╔════╝██╔════╝██║     ██║████╗  ██║██╔════╝\n");
    printf("  ██║  ██║█████╗  █████╗  ██║     ██║██╔██╗ ██║█████╗  \n");
    printf("  ██║  ██║██╔══╝  ██╔══╝  ██║     ██║██║╚██╗██║██╔══╝  \n");
    printf("  ██████╔╝███████╗███████╗███████╗██║██║ ╚████║███████╗\n");
    printf("  ╚═════╝ ╚══════╝╚══════╝╚══════╝╚═╝╚═╝  ╚═══╝╚══════╝\n");
    printf(C_RESET);
    printf("    Your AI Assistant\n");
    printf("    Loading...\n\n");
}
