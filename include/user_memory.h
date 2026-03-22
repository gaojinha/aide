#ifndef USER_MEMORY_H
#define USER_MEMORY_H

int memory_init(void);
int memory_remember(const char *key, const char *value);
int memory_recall(const char *key, char *value);
int memory_forget(const char *key);
int memory_learn_habit(const char *action, const char *time);
int memory_get_habit(const char *action, char *time);
void memory_list(void);

#endif // USER_MEMORY_H
