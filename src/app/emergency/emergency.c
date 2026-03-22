#include <stdio.h>
#include <string.h>

// ===== 紧急求助 =====
void emergency_sos_init(void) {
    printf("[Emergency] SOS initialized\n");
}
void emergency_call_120(void) {
    printf("\n=== Calling 120 ===\n");
    printf("正在拨打急救电话: 120\n");
    printf("定位: 山西省永济市xxx\n");
    printf("已通知家人: 是\n");
    printf("预计到达: 15分钟\n");
    printf("==================\n\n");
}
void emergency_call_110(void) {
    printf("\n=== Calling 110 ===\n");
    printf("正在拨打报警电话: 110\n");
    printf("定位: 已发送\n");
    printf("已通知家人: 是\n");
    printf("==================\n\n");
}
void emergency_notify_family(void) {
    printf("\n=== Notify Family ===\n");
    printf("通知: 老婆\n");
    printf("内容: 我遇到紧急情况, 需要帮助\n");
    printf("位置: 山西省永济市xxx\n");
    printf("电话: 13800138001\n");
    printf("状态: 已发送\n");
    printf("==================\n\n");
}
void emergency_send_location(void) {
    printf("\n=== Send Location ===\n");
    printf("纬度: 34.8685\n");
    printf("经度: 110.9975\n");
    printf("精度: 10米\n");
    printf("已发送给: 家人 + 紧急联系人\n");
    printf("==================\n\n");
}

// ===== 健康意外 =====
void emergency_health_fall(void) {
    printf("\n=== Fall Detection ===\n");
    printf("⚠️ 检测到摔倒!\n");
    printf("时间: 2026-03-22 20:25\n");
    printf("位置: 家中\n");
    printf("\n自动操作:\n");
    printf("[ ] 拨打120\n");
    printf("[x] 通知家人\n");
    printf("[x] 发送位置\n");
    printf("确认无事后, 点击解除警报\n");
    printf("======================\n\n");
}
void emergency_health_heart(void) {
    printf("\n=== Heart Rate Alert ===\n");
    printf("⚠️ 心率异常!\n");
    printf("当前: 150 BPM (过高)\n");
    printf("静息: 68 BPM\n");
    printf("\n建议:\n");
    printf("1. 立即休息\n");
    printf("2. 深呼吸\n");
    printf("3. 如持续请联系医生\n");
    printf("4. 严重时拨打120\n");
    printf("======================\n\n");
}
void emergency_health_blood_pressure(void) {
    printf("\n=== Blood Pressure Alert ===\n");
    printf("⚠️ 血压异常!\n");
    printf("当前: 160/100 (偏高)\n");
    printf("正常: 120/80\n");
    printf("\n建议:\n");
    printf("1. 休息10分钟重测\n");
    printf("2. 减少盐摄入\n");
    printf("3. 按时服用降压药\n");
    printf("4. 持续偏高就医\n");
    printf("========================\n\n");
}
void emergency_health_spo2(void) {
    printf("\n=== Blood Oxygen Alert ===\n");
    printf("⚠️ 血氧过低!\n");
    printf("当前: 88%% (过低)\n");
    printf("正常: 95%%-100%%\n");
    printf("\n建议:\n");
    printf("1. 立即深呼吸\n");
    printf("2. 打开窗户通风\n");
    printf("3. 如持续就就医\n");
    printf("4. 严重拨打120\n");
    printf("======================\n\n");
}
void emergency_health_temperature(void) {
    printf("\n=== Temperature Alert ===\n");
    printf("⚠️ 体温异常!\n");
    printf("当前: 39.2°C (发烧)\n");
    printf("正常: 36.5°C\n");
    printf("\n建议:\n");
    printf("1. 服用退烧药\n");
    printf("2. 多喝水\n");
    printf("3. 物理降温\n");
    printf("4. 持续高温就医\n");
    printf("======================\n\n");
}
void emergency_health_low_sugar(void) {
    printf("\n=== Low Blood Sugar ===\n");
    printf("⚠️ 低血糖风险!\n");
    printf("当前血糖: 3.5 mmol/L\n");
    printf("正常: 4.4-6.1 mmol/L\n");
    printf("\n建议:\n");
    printf("1. 立即吃糖/饼干\n");
    printf("2. 喝糖水\n");
    printf("3. 坐下休息\n");
    printf("4. 如昏迷立即就医\n");
    printf("======================\n\n");
}

// ===== 异常处理 =====
void emergency_device_lost(void) {
    printf("\n=== Device Lost ===\n");
    printf("操作:\n");
    printf("1. 远程锁定设备\n");
    printf("2. 播放声音\n");
    printf("3. 清除数据\n");
    printf("4. 定位设备\n");
    printf("\n定位: 永济市xxx\n");
    printf("最后在线: 10分钟前\n");
    printf("====================\n\n");
}
void emergency_device_error(void) {
    printf("\n=== Device Error ===\n");
    printf("错误: 系统崩溃\n");
    printf("操作:\n");
    printf("1. 重启设备\n");
    printf("2. 进入恢复模式\n");
    printf("3. 刷机\n");
    printf("4. 联系售后\n");
    printf("==================\n\n");
}
void emergency_scam_detect(void) {
    printf("\n=== Scam Detection ===\n");
    printf("⚠️ 可疑电话/短信检测\n");
    printf("\n内容: 您的账户涉嫌洗钱...\n");
    printf("判定: 诈骗短信 (98%%)\n");
    printf("\n建议:\n");
    printf("1. 不要点击链接\n");
    printf("2. 不要转账\n");
    printf("3. 不要提供验证码\n");
    printf("4. 标记为垃圾信息\n");
    printf("======================\n\n");
}

// ===== 一键求助 =====
void emergency_onekey_help(void) {
    printf("\n");
    printf("╔═══════════════════════════════════════╗\n");
    printf("║        🚨 一键紧急求助 🚨           ║\n");
    printf("╠═══════════════════════════════════════╣\n");
    printf("║ [1] 急救电话 120                     ║\n");
    printf("║ [2] 报警电话 110                     ║\n");
    printf("║ [3] 通知家人                         ║\n");
    printf("║ [4] 发送位置                         ║\n");
    printf("║ [5] 取消                             ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");
}

// ===== 测试 =====
void emergency_test(void) {
    printf("\n=== Emergency Test ===\n");
    
    emergency_sos_init();
    
    printf("--- Emergency Call ---\n");
    emergency_call_120();
    
    printf("--- Health Alerts ---\n");
    emergency_health_fall();
    emergency_health_heart();
    emergency_health_blood_pressure();
    emergency_health_spo2();
    emergency_health_temperature();
    emergency_health_low_sugar();
    
    printf("--- Device Issues ---\n");
    emergency_device_lost();
    emergency_device_error();
    emergency_scam_detect();
    
    emergency_onekey_help();
    
    printf("==================\n\n");
}
