#include <stdio.h>
#include <string.h>
#include "../src/core/storage.c"

extern int storage_init(const char *path);
extern int storage_write(const char *key, const void *data, size_t len);
extern int storage_read(const char *key, void *data, size_t max_len);
extern int storage_delete(const char *key);

int test_storage_basic(void) {
    storage_init("/tmp/aide_test");
    
    const char *data = "hello world";
    int ret = storage_write("test_key", data, strlen(data) + 1);
    TEST_ASSERT(ret == 0, "storage_write");
    
    char buf[128];
    ret = storage_read("test_key", buf, 128);
    TEST_ASSERT(ret > 0, "storage_read");
    TEST_ASSERT(strcmp(buf, "hello world") == 0, "data match");
    
    ret = storage_delete("test_key");
    TEST_ASSERT(ret == 0, "storage_delete");
    
    TEST_PASS("storage_basic");
    return 0;
}

int test_storage_string(void) {
    storage_init("/tmp/aide_test");
    
    storage_set_string("name", "王二狗");
    
    char buf[64];
    storage_get_string("name", buf, 64);
    TEST_ASSERT(strcmp(buf, "王二狗") == 0, "string match");
    
    TEST_PASS("storage_string");
    return 0;
}
