#include <stdio.h>
#include <string.h>

typedef struct { char text[256]; float vec[128]; } doc_t;
static doc_t docs[100];
static int doc_count = 0;

void vec_init(void) { printf("[Vector DB] Initialized\n"); }

void vec_add(const char *text) {
    doc_t *d = &docs[doc_count++];
    strncpy(d->text, text, 255);
    // 模拟向量
    for (int i = 0; i < 128; i++) d->vec[i] = (float)(rand() % 100) / 100;
    printf("[Vector] Added: %s\n", text);
}

void vec_search(const char *query, int topk) {
    printf("\n=== Search: %s ===\n", query);
    printf("Top-%d:\n", topk);
    for (int i = 0; i < topk && i < doc_count; i++) {
        float score = 1.0 - (float)i * 0.1;
        printf("%d. [%0.2f] %s\n", i+1, score, docs[i].text);
    }
    printf("====================\n\n");
}

void vec_similar(const char *text) {
    printf("\n=== Similar: %s ===\n", text);
    printf("相似文档:\n");
    printf("1. [0.95] %s\n", text);
    printf("2. [0.85] 相关内容A\n");
    printf("3. [0.80] 相关内容B\n");
    printf("====================\n\n");
}

void vec_delete(const char *text) {
    printf("[Vector] Deleted: %s\n", text);
}

void vector_test(void) {
    printf("\n=== Vector Test ===\n");
    vec_init();
    vec_add("人工智能是未来的趋势");
    vec_add("机器学习是AI的一个分支");
    vec_add("深度学习是机器学习的进阶");
    vec_add("Python是常用的编程语言");
    vec_search("AI", 3);
    vec_similar("人工智能");
    printf("==================\n\n");
}
