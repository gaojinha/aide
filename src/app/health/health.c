#include <stdio.h>
#include <string.h>

// ===== 运动 =====
void health_exercise_init(void) {
    printf("[Health] Exercise initialized\n");
}
void health_exercise_steps(void) {
    printf("\n=== Steps Today ===\n");
    printf("步数: 8,500\n");
    printf("目标: 10,000\n");
    printf("进度: ████████░░ 85%%\n");
    printf("距离: 6.5公里\n");
    printf("消耗: 350卡\n");
    printf("================\n\n");
}
void health_exercise_record(void) {
    printf("\n=== Exercise Records ===\n");
    printf("1. 跑步 30分钟 (昨天)\n");
    printf("2. 瑜伽 45分钟 (前天)\n");
    printf("3. 游泳 1小时 (3天前)\n");
    printf("======================\n\n");
}
void health_exercise_course(void) {
    printf("\n=== Recommended Courses ===\n");
    printf("1. 晨间拉伸 (10分钟)\n");
    printf("2.  HIIT燃脂 (20分钟)\n");
    printf("3. 晚间瑜伽 (30分钟)\n");
    printf("========================\n\n");
}

// ===== 睡眠 =====
void health_sleep_init(void) { printf("[Health] Sleep tracking\n"); }
void health_sleep_monitor(void) {
    printf("\n=== Sleep Monitor ===\n");
    printf("入睡: 22:30\n");
    printf("起床: 06:30\n");
    printf("时长: 8小时\n");
    printf("深度: 3小时\n");
    printf("浅度: 4小时\n");
    printf("REM:  1小时\n");
    printf("质量: 92%%\n");
    printf("==================\n\n");
}
void health_sleep_alarm(void) {
    printf("\n=== Sleep Alarm ===\n");
    printf("唤醒: 07:00\n");
    printf("模式: 渐响\n");
    printf("工作日: 已开启\n");
    printf("周末: 已关闭\n");
    printf("================\n\n");
}
void health_sleep_aid(void) {
    printf("\n=== Sleep Aid ===\n");
    printf("白噪音: 雨声\n");
    printf("时长: 30分钟\n");
    printf("助眠音乐: 已开启\n");
    printf("================\n\n");
}

// ===== 饮食 =====
void health_diet_init(void) { printf("[Health] Diet tracking\n"); }
void health_diet_record(void) {
    printf("\n=== Diet Record ===\n");
    printf("早餐: 豆浆+油条 (400卡)\n");
    printf("午餐: 米饭+红烧肉 (650卡)\n");
    printf("晚餐: 粥+小菜 (300卡)\n");
    printf("零食: 苹果 (80卡)\n");
    printf("------------------------\n");
    printf("总计: 1,430卡\n");
    printf("目标: 1,800卡\n");
    printf("===================\n\n");
}
void health_diet_calculator(void) {
    printf("\n=== Calories Calculator ===\n");
    printf("食物: 100克米饭\n");
    printf("热量: 130卡\n");
    printf("蛋白质: 2.6g\n");
    printf("碳水: 28g\n");
    printf("脂肪: 0.3g\n");
    printf("================\n\n");
}
void health_diet_advice(void) {
    printf("\n=== Diet Advice ===\n");
    printf("今日:\n");
    printf("- 蛋白质摄入不足, 建议加个鸡蛋\n");
    printf("- 维生素C摄入不足, 建议吃个橙子\n");
    printf("- 饮水不足, 再喝200ml水\n");
    printf("================\n\n");
}
void health_diet_recipe(void) {
    printf("\n=== Recipe Recommendation ===\n");
    printf("早餐: 豆浆+鸡蛋+全麦面包\n");
    printf("午餐: 鸡胸肉+蔬菜+米饭\n");
    printf("晚餐: 鱼+蔬菜+粗粮\n");
    printf("================\n\n");
}

// ===== 身体 =====
void health_body_init(void) { printf("[Health] Body tracking\n"); }
void health_body_symptom(void) {
    printf("\n=== Symptom Query ===\n");
    printf("头痛可能原因:\n");
    printf("1. 睡眠不足\n");
    printf("2. 压力大\n");
    printf("3. 视力疲劳\n");
    printf("建议: 多休息, 适当放松\n");
    printf("====================\n\n");
}
void health_body_water(void) {
    printf("\n=== Water Reminder ===\n");
    printf("当前: 1,500ml\n");
    printf("目标: 2,000ml\n");
    printf("进度: ████████░░ 75%%\n");
    printf("下次提醒: 30分钟后\n");
    printf("==================\n\n");
}
void health_body_posture(void) {
    printf("\n=== Posture Reminder ===\n");
    printf("当前姿势: 坐着\n");
    printf("已保持: 1小时\n");
    printf("提醒: 该站起来了!\n");
    printf("建议: 活动5分钟\n");
    printf("==================\n\n");
}
void health_body_eye(void) {
    printf("\n=== Eye Exercise ===\n");
    printf("屏幕时间: 4小时\n");
    printf("提醒: 做眼保健操\n");
    printf("\n1. 闭眼30秒\n");
    printf("2. 转动眼球\n");
    printf("3. 远近交替\n");
    printf("4. 按摩眼周\n");
    printf("==============\n\n");
}

// ===== 心理 =====
void health_mind_init(void) { printf("[Health] Mind tracking\n"); }
void health_mind_chat(void) {
    printf("\n=== AI Chat ===\n");
    printf("你: 最近压力大\n");
    printf("aide: 深呼吸, 一切都会好起来的~ 需要我帮你做冥想吗?\n");
    printf("================\n\n");
}
void health_mind_stress(void) {
    printf("\n=== Stress Test ===\n");
    printf("得分: 65/100 (中等)\n");
    printf("建议:\n");
    printf("- 听音乐放松\n");
    printf("- 做深呼吸\n");
    printf("- 找朋友倾诉\n");
    printf("===============\n\n");
}
void health_mind_meditate(void) {
    printf("\n=== Meditation ===\n");
    printf("正在播放: 静心冥想\n");
    printf("时长: 10分钟\n");
    printf("进度: ██████░░░░ 60%%\n");
    printf("================\n\n");
}
void health_mind_encourage(void) {
    printf("\n=== Daily Encouragement ===\n");
    printf("每一天都是新的开始!\n");
    printf("相信自己, 你可以的!\n");
    printf("加油! 💪\n");
    printf("======================\n\n");
}

// ===== 日常健康监测 =====
void health_monitor_daily(void) {
    printf("\n=== Daily Health Monitor ===\n");
    printf("❤️ 心率: 72 BPM (正常)\n");
    printf("🌡️  体温: 36.5°C (正常)\n");
    printf("🩸 血压: 120/80 (正常)\n");
    printf("🩺 血氧: 98%% (正常)\n");
    printf("👟 步数: 8,500\n");
    printf("💤 睡眠: 8小时\n");
    printf("💧 饮水: 1,500ml\n");
    printf("🍽️  摄入: 1,430卡\n");
    printf("==========================\n\n");
}

// ===== 健康仪表盘 =====
void health_dashboard(void) {
    printf("\n");
    printf("╔═══════════════════════════════════════╗\n");
    printf("║         Health Dashboard             ║\n");
    printf("╠═══════════════════════════════════════╣\n");
    printf("║ ❤️ 心率: 72 BPM   🩸 120/80      ║\n");
    printf("║ 👟 步数: 8,500    💧 1,500ml     ║\n");
    printf("║ 😴 睡眠: 8小时     🍽️ 1,430卡    ║\n");
    printf("║ 😊 心情: 良好      🧘 冥想10分钟 ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");
}

// ===== 测试 =====
void health_test(void) {
    printf("\n=== Health Test ===\n");
    
    health_exercise_init();
    health_exercise_steps();
    health_exercise_record();
    health_exercise_course();
    
    health_sleep_init();
    health_sleep_monitor();
    health_sleep_alarm();
    health_sleep_aid();
    
    health_diet_init();
    health_diet_record();
    health_diet_calculator();
    health_diet_advice();
    health_diet_recipe();
    
    health_body_init();
    health_body_symptom();
    health_body_water();
    health_body_posture();
    health_body_eye();
    
    health_mind_init();
    health_mind_chat();
    health_mind_stress();
    health_mind_meditate();
    health_mind_encourage();
    
    health_monitor_daily();
    health_dashboard();
    
    printf("==================\n\n");
}
