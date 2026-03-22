/**
 * @file driver.h
 * @brief 驱动框架头文件
 * 
 * 统一驱动接口定义
 */

#ifndef DRIVER_H
#define DRIVER_H

#include <stdint.h>
#include <stdbool.h>

/** 驱动类型 */
typedef enum {
    DRIVER_CAMERA,
    DRIVER_SENSOR,
    DRIVER_DISPLAY,
    DRIVER_NETWORK,
    DRIVER_AUDIO,
    DRIVER_STORAGE
} driver_type_t;

/** 驱动状态 */
typedef enum {
    DRIVER_STATE_UNINIT,
    DRIVER_STATE_READY,
    DRIVER_STATE_RUNNING,
    DRIVER_STATE_ERROR
} driver_state_t;

/** 驱动操作 */
typedef struct driver_ops {
    int (*init)(void);
    int (*start)(void);
    int (*stop)(void);
    int (*read)(void *buf, size_t len);
    int (*write)(const void *buf, size_t len);
    int (*control)(int cmd, void *arg);
} driver_ops_t;

/** 驱动描述符 */
typedef struct driver {
    driver_type_t type;
    driver_state_t state;
    char name[64];
    const driver_ops_t *ops;
} driver_t;

/* 驱动注册 */
int driver_register(driver_t *drv);
int driver_unregister(driver_t *drv);
int driver_find(const char *name, driver_t **drv);

/* 驱动操作 */
int driver_init_all(void);
int driver_start_all(void);
int driver_stop_all(void);

#endif // DRIVER_H
