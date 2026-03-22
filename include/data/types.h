/**
 * @file types.h
 * @brief 数据类型定义
 * 
 * 项目中使用的数据结构定义
 */

#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include <stdint.h>
#include <stdbool.h>

/* 用户信息 */
typedef struct {
    uint32_t id;
    char name[64];
    char phone[32];
    char email[128];
    uint8_t auth_level;
} user_info_t;

/* 消息结构 */
typedef struct {
    uint64_t msg_id;
    uint32_t from_id;
    uint32_t to_id;
    char content[1024];
    uint32_t timestamp;
    uint8_t type; // 0:text 1:image 2:voice
} message_t;

/* AI对话 */
typedef struct {
    char role[16]; // user/assistant/system
    char content[4096];
    uint32_t timestamp;
} chat_message_t;

/* 传感器数据 */
typedef struct {
    float accel[3];    // 加速度
    float gyro[3];     // 陀螺仪
    float temperature; // 温度
    float humidity;    // 湿度
    float light;       // 光照
    uint32_t timestamp;
} sensor_data_t;

/* 语音数据 */
typedef struct {
    uint8_t *audio_data;
    uint32_t data_size;
    uint32_t sample_rate;
    uint16_t channels;
    uint16_t bits_per_sample;
} audio_data_t;

/* 配置项 */
typedef struct {
    char key[64];
    char value[256];
    char type[16]; // string/int/float/bool
} config_item_t;

#endif // DATA_TYPES_H
