#ifndef AI_ASSISTANT_H
#define AI_ASSISTANT_H

#include <stdint.h>
#include <stdbool.h>

// 版本信息
#define AI_ASSISTANT_VERSION "0.1.0"
#define AI_ASSISTANT_BUILD "20260322"

// 系统状态
typedef enum {
    SYSTEM_STATE_INIT,
    SYSTEM_STATE_READY,
    SYSTEM_STATE_RUNNING,
    SYSTEM_STATE_SLEEP,
    SYSTEM_STATE_ERROR
} system_state_t;

// 初始化系统
int ai_system_init(void);

// 启动系统
int ai_system_start(void);

// 停止系统
int ai_system_stop(void);

// 获取系统状态
system_state_t ai_system_get_state(void);

#endif // AI_ASSISTANT_H
