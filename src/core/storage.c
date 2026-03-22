/**
 * 存储模块实现
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_PATH 256
#define MAX_FILES 100

typedef struct {
    char key[64];
    char value[256];
    time_t modified;
} storage_item_t;

static storage_item_t storage[MAX_FILES];
static int storage_count = 0;
static char storage_path[MAX_PATH] = "/tmp/aide_storage";

// 确保目录存在
static int ensure_dir(const char *path) {
    struct stat st;
    if (stat(path, &st) == -1) {
        printf("[Storage] Creating directory: %s\n", path);
        return mkdir(path, 0755);
    }
    return 0;
}

// 初始化存储
int storage_init(const char *path) {
    if (path) {
        strncpy(storage_path, path, MAX_PATH - 1);
    }
    printf("[Storage] Initialized at: %s\n", storage_path);
    ensure_dir(storage_path);
    return 0;
}

// 写入数据
int storage_write(const char *key, const void *data, size_t len) {
    char filepath[MAX_PATH];
    snprintf(filepath, MAX_PATH, "%s/%s.dat", storage_path, key);
    
    FILE *f = fopen(filepath, "wb");
    if (!f) {
        printf("[Storage] Write failed: %s\n", key);
        return -1;
    }
    
    fwrite(data, 1, len, f);
    fclose(f);
    
    printf("[Storage] Written: %s (%zu bytes)\n", key, len);
    return 0;
}

// 读取数据
int storage_read(const char *key, void *data, size_t max_len) {
    char filepath[MAX_PATH];
    snprintf(filepath, MAX_PATH, "%s/%s.dat", storage_path, key);
    
    FILE *f = fopen(filepath, "rb");
    if (!f) {
        printf("[Storage] Read failed: %s\n", key);
        return -1;
    }
    
    size_t len = fread(data, 1, max_len, f);
    fclose(f);
    
    printf("[Storage] Read: %s (%zu bytes)\n", key, len);
    return len;
}

// 删除数据
int storage_delete(const char *key) {
    char filepath[MAX_PATH];
    snprintf(filepath, MAX_PATH, "%s/%s.dat", storage_path, key);
    
    if (unlink(filepath) == 0) {
        printf("[Storage] Deleted: %s\n", key);
        return 0;
    }
    return -1;
}

// 检查key是否存在
int storage_exists(const char *key) {
    char filepath[MAX_PATH];
    snprintf(filepath, MAX_PATH, "%s/%s.dat", storage_path, key);
    
    struct stat st;
    return (stat(filepath, &st) == 0) ? 1 : 0;
}

// 列出所有key
int storage_list(char keys[][64], int max_keys) {
    printf("[Storage] Listing files in: %s\n", storage_path);
    // TODO: 实际遍历目录
    return 0;
}

// 保存字符串
int storage_set_string(const char *key, const char *value) {
    return storage_write(key, value, strlen(value) + 1);
}

// 读取字符串
int storage_get_string(const char *key, char *value, size_t max_len) {
    return storage_read(key, value, max_len);
}

// 保存JSON
int storage_set_json(const char *key, const char *json) {
    char filepath[MAX_PATH];
    snprintf(filepath, MAX_PATH, "%s/%s.json", storage_path, key);
    
    FILE *f = fopen(filepath, "w");
    if (!f) return -1;
    
    fprintf(f, "%s", json);
    fclose(f);
    printf("[Storage] JSON saved: %s\n", key);
    return 0;
}

// 获取存储大小
int storage_size(const char *key) {
    char filepath[MAX_PATH];
    snprintf(filepath, MAX_PATH, "%s/%s.dat", storage_path, key);
    
    struct stat st;
    if (stat(filepath, &st) == 0) {
        return st.st_size;
    }
    return -1;
}

// 清除所有数据
int storage_clear(void) {
    printf("[Storage] Clearing all data...\n");
    // TODO: 遍历删除
    storage_count = 0;
    return 0;
}
