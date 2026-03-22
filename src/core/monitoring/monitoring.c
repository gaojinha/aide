#include <stdio.h>
#include <string.h>

// ===== 系统监控 =====
void mon_system_init(void) { printf("[Monitoring] System monitoring initialized\n"); }
void mon_system_cpu(void) {
    printf("\n=== CPU Monitor ===\n");
    printf("使用率: 45%%\n");
    printf("核心: 4核\n");
    printf("温度: 45°C\n");
    printf("进程: 50个\n");
    printf("====================\n\n");
}
void mon_system_memory(void) {
    printf("\n=== Memory Monitor ===\n");
    printf("已用: 2GB / 8GB\n");
    printf("使用率: 25%%\n");
    printf("Swap: 0MB / 4GB\n");
    printf("====================\n\n");
}
void mon_system_disk(void) {
    printf("\n=== Disk Monitor ===\n");
    printf("已用: 20GB / 64GB\n");
    printf("使用率: 31%%\n");
    printf("IO: 10MB/s\n");
    printf("====================\n\n");
}
void mon_system_network(void) {
    printf("\n=== Network Monitor ===\n");
    printf("WiFi: 100Mbps (正常)\n");
    printf("流量: ↑5MB ↓20MB\n");
    printf("延迟: 20ms\n");
    printf("====================\n\n");
}

// ===== 业务监控 =====
void mon_business_init(void) { printf("[Monitoring] Business monitoring initialized\n"); }
void mon_business_api(void) {
    printf("\n=== API Monitor ===\n");
    printf("请求: 1,000/小时\n");
    printf("成功率: 99.5%%\n");
    printf("延迟: 50ms (P95)\n");
    printf("错误: 5次\n");
    printf("====================\n\n");
}
void mon_business_users(void) {
    printf("\n=== User Monitor ===\n");
    printf("在线: 100人\n");
    printf("活跃: 80人\n");
    printf("新增: 10人/天\n");
    printf("留存: 70%%\n");
    printf("====================\n\n");
}
void mon_business_ai(void) {
    printf("\n=== AI Monitor ===\n");
    printf("对话: 500次/天\n");
    printf("成功率: 98%%\n");
    printf("平均响应: 1s\n");
    printf("Token消耗: 100K\n");
    printf("====================\n\n");
}

// ===== 告警 =====
void mon_alert_init(void) { printf("[Monitoring] Alert initialized\n"); }
void mon_alert_rules(void) {
    printf("\n=== Alert Rules ===\n");
    printf("1. CPU > 90%% -> 告警\n");
    printf("2. 内存 > 85%% -> 告警\n");
    printf("3. 磁盘 > 90%% -> 告警\n");
    printf("4. API错误 > 5%% -> 告警\n");
    printf("=====================\n\n");
}
void mon_alert_trigger(void) {
    printf("\n=== Alerts ===\n");
    printf("⚠️  12:00 CPU 95%%\n");
    printf("✓  已通知管理员\n");
    printf("✓  已自动处理\n");
    printf("====================\n\n");
}
void mon_alert_history(void) {
    printf("\n=== Alert History ===\n");
    printf("2026-03-22 12:00 CPU过高\n");
    printf("2026-03-22 10:00 内存过高\n");
    printf("2026-03-21 20:00 网络断开\n");
    printf("======================\n\n");
}

// ===== 日志聚合 =====
void mon_log_init(void) { printf("[Monitoring] Log aggregation initialized\n"); }
void mon_log_query(void) {
    printf("\n=== Log Query ===\n");
    printf("查询: error\n");
    printf("结果: 50条\n");
    printf("时间: 2026-03-22\n");
    printf("====================\n\n");
}
void mon_log_analysis(void) {
    printf("\n=== Log Analysis ===\n");
    printf("错误分析:\n");
    printf("1. 网络超时: 30%%\n");
    printf("2. 权限不足: 20%%\n");
    printf("3. 数据异常: 10%%\n");
    printf("====================\n\n");
}

// ===== 仪表盘 =====
void mon_dashboard(void) {
    printf("\n");
    printf("╔═══════════════════════════════════════╗\n");
    printf("║         Monitoring Dashboard         ║\n");
    printf("╠═══════════════════════════════════════╣\n");
    printf("║ 系统: CPU 45%% 内存 25%% 磁盘 31%% ║\n");
    printf("║ API:  1000/h 成功率 99.5%%        ║\n");
    printf("║ 用户: 在线 100 活跃 80             ║\n");
    printf("║ AI:   500次/天 响应 1s            ║\n");
    printf("║ 告警: 0个 (正常)                   ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");
}

// ===== 测试 =====
void monitoring_test(void) {
    printf("\n=== Monitoring Test ===\n");
    
    mon_system_init();
    mon_system_cpu();
    mon_system_memory();
    mon_system_disk();
    mon_system_network();
    
    mon_business_init();
    mon_business_api();
    mon_business_users();
    mon_business_ai();
    
    mon_alert_init();
    mon_alert_rules();
    mon_alert_trigger();
    mon_alert_history();
    
    mon_log_init();
    mon_log_query();
    mon_log_analysis();
    
    mon_dashboard();
    
    printf("==================\n\n");
}
