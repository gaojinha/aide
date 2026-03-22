/**
 * 存储模块
 */

#include <stdio.h>

int storage_init(void) {
    printf("[Storage] Manager initialized\n");
    return 0;
}

int storage_write(const char *key, const void *data, size_t len) {
    // TODO: 写存储
    return 0;
}

int storage_read(const char *key, void *data, size_t len) {
    // TODO: 读存储
    return 0;
}

int storage_delete(const char *key) {
    // TODO: 删除
    return 0;
}
