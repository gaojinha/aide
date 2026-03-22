#ifndef UI_H
#define UI_H

#include <stddef.h>

// 初始化UI
int ui_init(void);

// 屏幕管理
typedef struct ui_screen ui_screen_t;
ui_screen_t* ui_screen_create(const char *name);
int ui_screen_show(ui_screen_t *screen);

// 主菜单
int ui_main_menu(void);

#endif // UI_H
