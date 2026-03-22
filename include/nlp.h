#ifndef NLP_H
#define NLP_H

typedef struct {
    int intent;
    char text[256];
    void *entities;
    int entity_count;
    double confidence;
} parse_result_t;

int nlp_init(void);
int nlp_understand(const char *text, void *result);
int nlp_generate(const char *input, const void *ctx, char *response);

#endif
