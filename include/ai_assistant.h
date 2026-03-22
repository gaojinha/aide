/**
 * @file ai_assistant.h
 * @brief AI Aide系统头文件
 * 
 * 提供系统初始化、启动、停止等功能
 * 
 * @author AI Assistant Team
 * @version 0.1.0
 * @date 2026-03-22
 * 
 * @example
 * #include "ai_assistant.h"
 * 
 * int main(void) {
 *     ai_system_init();
 *     ai_system_start();
 *     // 运行...
 *     ai_system_stop();
 *     return 0;
 * }
 */

#ifndef AI_ASSISTANT_H
#define AI_ASSISTANT_H

#include <stdint.h>
#include <stdbool.h>

/** 版本信息 */
#define AI_ASSISTANT_VERSION "0.1.0"
#define AI_ASSISTANT_BUILD "20260322"

/** 系统状态 */
typedef enum {
    SYSTEM_STATE_INIT,     /**< 初始化状态 */
    SYSTEM_STATE_READY,   /**< 就绪状态 */
    SYSTEM_STATE_RUNNING, /**< 运行状态 */
    SYSTEM_STATE_SLEEP,   /**< 睡眠状态 */
    SYSTEM_STATE_ERROR    /**< 错误状态 */
} system_state_t;

/**
 * @brief 初始化AI Aide系统
 * @return 0成功，-1失败
 * 
 * @note 调用此函数后，系统进入就绪状态
 */
int ai_system_init(void);

/**
 * @brief 启动AI Aide系统
 * @return 0成功，-1失败
 * 
 * @pre 系统必须已初始化
 */
int ai_system_start(void);

/**
 * @brief 停止AI Aide系统
 * @return 0成功，-1失败
 */
int ai_system_stop(void);

/**
 * @brief 获取当前系统状态
 * @return 系统状态
 */
system_state_t ai_system_get_state(void);

#endif // AI_ASSISTANT_H
