/**
 * UI框架 - 简单控制台UI
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 颜色定义
#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BLUE    "\033[34m"

// UI组件类型
typedef enum {
    UI_BUTTON,
    UI_TEXT,
    UI_IMAGE,
    UI_INPUT
} ui_type_t;

// 简单的UI组件
typedef struct {
    ui_type_t type;
    char *id;
    char *label;
    void *data;
} ui_component_t;

// 屏幕
typedef struct {
    char *name;
    ui_component_t **components;
    int component_count;
} ui_screen_t;

// 初始化UI
int ui_init(void) {
    printf("[UI] Framework initialized\n");
    return 0;
}

// 创建屏幕
ui_screen_t* ui_screen_create(const char *name) {
    ui_screen_t *screen = malloc(sizeof(ui_screen_t));
    screen->name = strdup(name);
    screen->components = NULL;
    screen->component_count = 0;
    return screen;
}

// 添加组件
int ui_screen_add(ui_screen_t *screen, ui_component_t *comp) {
    screen->component_count++;
    screen->components = realloc(screen->components, 
        screen->component_count * sizeof(void*));
    screen->components[screen->component_count - 1] = comp;
    return 0;
}

// 显示屏幕
int ui_screen_show(ui_screen_t *screen) {
    printf("\n=== %s ===\n", screen->name);
    for (int i = 0; i < screen->component_count; i++) {
        ui_component_t *c = screen->components[i];
        printf("  [%d] %s\n", i+1, c->label);
    }
    printf("=============\n");
    return 0;
}

// 显示主菜单
int ui_main_menu(void) {
    printf("\n");
    printf(COLOR_BLUE "╔═══════════════════════════════╗\n" COLOR_RESET);
    printf(COLOR_BLUE "║     AI助理 v0.1.0            ║\n" COLOR_RESET);
    printf(COLOR_BLUE "╠═══════════════════════════════╣\n" COLOR_RESET);
    printf(COLOR_BLUE "║  1. 对话                     ║\n" COLOR_RESET);
    printf(COLOR_BLUE "║  2. 电话                     ║\n" COLOR_RESET);
    printf(COLOR_BLUE "║  3. 消息                     ║\n" COLOR_RESET);
    printf(COLOR_BLUE "║  4. 设置                     ║\n" COLOR_RESET);
    printf(COLOR_BLUE "║  5. 退出                     ║\n" COLOR_RESET);
    printf(COLOR_BLUE "╚═══════════════════════════════╝\n" COLOR_RESET);
    printf("请选择: ");
    return 0;
}
