#include <stdio.h>
#include <string.h>

// ===== 日常起居 =====
void life_morning_init(void) {
    printf("[Life] Morning routines initialized\n");
}
void life_morning_report(void) {
    printf("\n=== Morning Report ===\n");
    printf("🌅 起床时间: 07:00\n");
    printf("🌤️  天气: 晴 20-28°C\n");
    printf("👕 穿衣建议: 长袖+外套\n");
    printf("🌫️  空气质量: 良 (52)\n");
    printf("☀️  紫外线: 中等\n");
    printf("====================\n\n");
}

// ===== 出行 =====
void life_transport_init(void) {
    printf("[Life] Transport initialized\n");
}
void life_transport_taxi(void) { printf("[Life] 叫车中...\n"); }
void life_transport_nav(void) {
    printf("\n=== Navigation ===\n");
    printf("目的地: 西安市政府\n");
    printf("距离: 45公里\n");
    printf("预计: 50分钟\n");
    printf("路线: 高速\n");
    printf("==================\n\n");
}
void life_transport_bus(void) {
    printf("\n=== Bus ===\n");
    printf("下一班: 12路\n");
    printf("到站: 3分钟\n");
    printf("================\n\n");
}
void life_transport_parking(void) {
    printf("\n=== Parking ===\n");
    printf("附近停车场: 3个\n");
    printf("最近: 距离200米\n");
    printf("价格: 5元/小时\n");
    printf("================\n\n");
}
void life_transport_charge(void) {
    printf("\n=== Charging Station ===\n");
    printf("附近充电桩: 2个\n");
    printf("快充: 1个 (距离500米)\n");
    printf("================\n\n");
}

// ===== 餐饮 =====
void life_food_init(void) {
    printf("[Life] Food initialized\n");
}
void life_food_order(void) { printf("[Life] 外卖下单中...\n"); }
void life_food_restaurant(void) {
    printf("\n=== Restaurant Search ===\n");
    printf("1. 兰州拉面 (4.5星, 2km)\n");
    printf("2. 川菜馆 (4.3星, 3km)\n");
    printf("3. 麦当劳 (4.2星, 1km)\n");
    printf("=======================\n\n");
}
void life_food_booking(void) { printf("[Life] 订位成功\n"); }
void life_food_shopping(void) {
    printf("\n=== Grocery Shopping ===\n");
    printf("今日推荐: 青菜、肉类、水果\n");
    printf("附近超市: 永济超市 (500米)\n");
    printf("================\n\n");
}
void life_food_cooking(void) {
    printf("\n=== Cooking Lesson ===\n");
    printf("今日菜谱: 西红柿炒鸡蛋\n");
    printf("步骤:\n");
    printf("1. 鸡蛋打散\n");
    printf("2. 西红柿切块\n");
    printf("3. 炒鸡蛋盛出\n");
    printf("4. 炒西红柿加糖\n");
    printf("5. 放入鸡蛋翻炒\n");
    printf("================\n\n");
}

// ===== 购物 =====
void life_shopping_init(void) {
    printf("[Life] Shopping initialized\n");
}
void life_shopping_search(void) {
    printf("\n=== Shopping Search ===\n");
    printf("商品: 无线耳机\n");
    printf("京东: ¥299 (有货)\n");
    printf("淘宝: ¥259 (3天)\n");
    printf("拼多多: ¥199 (5天)\n");
    printf("======================\n\n");
}
void life_shopping_order(void) { printf("[Life] 订单已下单\n"); }
void life_shopping_track(void) {
    printf("\n=== Logistics ===\n");
    printf("订单: TB123456789\n");
    printf("状态: 运输中\n");
    printf("预计: 明天送达\n");
    printf("================\n\n");
}

// ===== 家居 =====
void life_home_init(void) {
    printf("[Life] Home initialized\n");
}
void life_home_light(int on) {
    printf("[Life] Light %s\n", on ? "ON" : "OFF");
}
void life_home_ac(int temp) {
    printf("[Life] AC set to %d°C\n", temp);
}
void life_home_lock(int locked) {
    printf("[Life] Door %s\n", locked ? "LOCKED" : "UNLOCKED");
}
void life_home_camera(void) {
    printf("\n=== Home Camera ===\n");
    printf("客厅: 正常\n");
    printf("门口: 有人经过\n");
    printf("厨房: 正常\n");
    printf("================\n\n");
}
void life_home_robot(void) {
    printf("\n=== Robot Vacuum ===\n");
    printf("状态: 工作中\n");
    printf("电量: 80%%\n");
    printf("区域: 客厅+卧室\n");
    printf("================\n\n");
}

// ===== 生活仪表盘 =====
void life_dashboard(void) {
    printf("\n");
    printf("╔═══════════════════════════════════════╗\n");
    printf("║         Life Dashboard             ║\n");
    printf("╠═══════════════════════════════════════╣\n");
    printf("║ 🌤️  天气: 晴 20-28°C             ║\n");
    printf("║ 🚗  出行: 驾车                     ║\n");
    printf("║ 🍜  餐饮: 已推荐餐厅                ║\n");
    printf("║ 🛒  物流: 1个快递                  ║\n");
    printf("║ 🏠  家居: 灯(开) 门(锁) 空调(24°C) ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");
}

// ===== 测试 =====
void life_test(void) {
    printf("\n=== Life Test ===\n");
    
    printf("--- Morning ---\n");
    life_morning_init();
    life_morning_report();
    
    printf("--- Transport ---\n");
    life_transport_init();
    life_transport_nav();
    life_transport_bus();
    life_transport_parking();
    life_transport_charge();
    
    printf("--- Food ---\n");
    life_food_init();
    life_food_restaurant();
    life_food_cooking();
    
    printf("--- Shopping ---\n");
    life_shopping_init();
    life_shopping_search();
    life_shopping_track();
    
    printf("--- Home ---\n");
    life_home_init();
    life_home_light(1);
    life_home_ac(24);
    life_home_lock(1);
    life_home_camera();
    life_home_robot();
    
    life_dashboard();
    
    printf("==================\n\n");
}
