#ifndef PERSONALITY_H
#define PERSONALITY_H

int personality_init(void);
int personality_set(const char *key, const char *value);
const char* personality_get(const char *key);
void personality_show(void);
int personality_generate(const char *input, char *output);

#endif // PERSONALITY_H
