/**
 * 消息应用
 */

#include <stdio.h>

int messaging_init(void) {
    printf("[App/Messaging] Initialized\n");
    return 0;
}

int messaging_send(const char *to, const char *msg) {
    printf("[App/Messaging] Sending to %s: %s\n", to, msg);
    return 0;
}

int messaging_recv(void) {
    // TODO: 接收消息
    return 0;
}
