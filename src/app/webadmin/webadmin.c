#include <stdio.h>
#include <string.h>

// 页面类型
typedef enum {
    PAGE_DASHBOARD,
    PAGE_SETTINGS,
    PAGE_LOGS,
    PAGE_USERS,
    PAGE_NETWORK,
    PAGE_ABOUT
} page_type_t;

static int web_port = 8088;
static char web_title[64] = "aide Admin";

// 初始化
void webadmin_init(int port) {
    web_port = port;
    printf("[WebAdmin] Initialized\n");
    printf("  Port: %d\n", web_port);
    printf("  Title: %s\n", web_title);
}

// 仪表盘
void webadmin_dashboard(void) {
    printf("\n=== Web Dashboard ===\n");
    printf("╔═══════════════════════════════════════╗\n");
    printf("║           aide Admin Panel           ║\n");
    printf("╠═══════════════════════════════════════╣\n");
    printf("║ CPU:    ████████░░ 80%%              ║\n");
    printf("║ Memory: ██████░░░░ 60%%              ║\n");
    printf("║ Disk:   ████░░░░░░ 40%%              ║\n");
    printf("║ Battery: █████████░ 90%%              ║\n");
    printf("╠═══════════════════════════════════════╣\n");
    printf("║ Uptime: 2 days 5 hours              ║\n");
    printf("║ Status: Online                       ║\n");
    printf("╚═══════════════════════════════════════╝\n");
}

// 设置页面
void webadmin_settings(void) {
    printf("\n=== Web Settings ===\n");
    printf("Language: zh-CN\n");
    printf("Theme: dark\n");
    printf("API Key: ****\n");
    printf("Model: MiniMax\n");
    printf("Volume: 70%%\n");
    printf("Auto-answer: ON\n");
}

// 日志页面
void webadmin_logs(void) {
    printf("\n=== Web Logs ===\n");
    printf("2026-03-22 19:50 [INFO] System started\n");
    printf("2026-03-22 19:51 [INFO] WiFi connected\n");
    printf("2026-03-22 19:52 [WARN] Low memory\n");
    printf("2026-03-22 19:53 [INFO] User logged in\n");
    printf("2026-03-22 19:54 [ERROR] Network timeout\n");
}

// 用户管理
void webadmin_users(void) {
    printf("\n=== Web Users ===\n");
    printf("ID  Username  Role    Status\n");
    printf("1   admin    ADMIN   Active\n");
    printf("2   gao      OWNER   Active\n");
    printf("3   guest    GUEST  Active\n");
}

// 网络设置
void webadmin_network(void) {
    printf("\n=== Web Network ===\n");
    printf("WiFi: Connected (MyWiFi)\n");
    printf("IP: 192.168.1.100\n");
    printf("Bluetooth: ON\n");
    printf("Ethernet: Disconnected\n");
}

// 关于页面
void webadmin_about(void) {
    printf("\n=== Web About ===\n");
    printf("aide Admin Panel\n");
    printf("Version: 0.1.0\n");
    printf("Platform: RK3568\n");
    printf("Build: 2026-03-22\n");
    printf("Author: aide Team\n");
}

// 启动Web服务
void webadmin_start(void) {
    printf("[WebAdmin] Starting web server on port %d...\n", web_port);
    printf("[WebAdmin] Web UI available at http://localhost:%d\n", web_port);
}

// 测试
void webadmin_test(void) {
    printf("\n=== WebAdmin Test ===\n");
    
    webadmin_init(8088);
    webadmin_start();
    
    printf("\n--- Dashboard ---\n");
    webadmin_dashboard();
    
    printf("--- Settings ---\n");
    webadmin_settings();
    
    printf("--- Logs ---\n");
    webadmin_logs();
    
    printf("--- Users ---\n");
    webadmin_users();
    
    printf("--- Network ---\n");
    webadmin_network();
    
    printf("--- About ---\n");
    webadmin_about();
    
    printf("==================\n\n");
}
