/**
 * @file protocol.h
 * @brief 通信协议格式定义
 */

#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>

/* 协议头 */
typedef struct {
    uint16_t magic;      // 0xAA55
    uint8_t version;    // 协议版本
    uint8_t type;       // 消息类型
    uint16_t length;    // 数据长度
    uint32_t seq;       // 序列号
    uint16_t checksum;  // 校验和
} protocol_header_t;

/* 消息类型 */
#define MSG_TYPE_TEXT      0x01
#define MSG_TYPE_VOICE     0x02
#define MSG_TYPE_IMAGE      0x03
#define MSG_TYPE_CMD       0x10
#define MSG_TYPE_RESPONSE   0x11
#define MSG_TYPE_HEARTBEAT 0xFF

/* API响应 */
typedef struct {
    int32_t code;       // 0:成功
    char message[256];
    void *data;
} api_response_t;

#endif // PROTOCOL_H
