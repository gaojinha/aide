#ifndef STORAGE_H
#define STORAGE_H

int storage_init(const char *path);
int storage_write(const char *key, const void *data, size_t len);
int storage_read(const char *key, void *data, size_t max_len);
int storage_delete(const char *key);
int storage_set_string(const char *key, const char *value);
int storage_get_string(const char *key, char *value, size_t max_len);

#endif
