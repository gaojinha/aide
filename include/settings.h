#ifndef SETTINGS_H
#define SETTINGS_H

int settings_init(void);
int settings_set_string(const char *key, const char *value);
int settings_set_int(const char *key, int value);
int settings_set_bool(const char *key, int value);
const char* settings_get_string(const char *key);
int settings_get_int(const char *key);
int settings_get_bool(const char *key);
int settings_delete(const char *key);
int settings_reset(void);
void settings_list(void);
int settings_save(const char *filename);
int settings_load(const char *filename);

#endif
