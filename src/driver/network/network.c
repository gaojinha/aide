/**
 * 网络驱动
 */

#include <stdio.h>

int network_init(void) {
    printf("[Driver/Network] Initialized\n");
    return 0;
}

int network_connect(const char *ssid, const char *pass) {
    printf("[Driver/Network] Connecting: %s\n", ssid);
    return 0;
}

int network_disconnect(void) {
    return 0;
}

int network_send(const void *data, size_t len) {
    return 0;
}

int network_recv(void *data, size_t len) {
    return 0;
}
