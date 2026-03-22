#include <stdio.h>
#include <string.h>

typedef struct { char entity[64]; char rel[32]; char target[64]; } triple_t;
static triple_t triples[100];
static int triple_count = 0;

void kg_init(void) { 
    printf("[Knowledge Graph] Initialized\n"); 
    // 添加示例
    triple_t *t = &triples[triple_count++];
    strcpy(t->entity, "马斯克"); strcpy(t->rel, "创立"); strcpy(t->target, "特斯拉");
    t = &triples[triple_count++];
    strcpy(t->entity, "马斯克"); strcpy(t->rel, "创立"); strcpy(t->target, "SpaceX");
    t = &triples[triple_count++];
    strcpy(t->entity, "特斯拉"); strcpy(t->rel, "总部在"); strcpy(t->target, "美国");
    printf("  Triples: %d\n", triple_count);
}

void kg_add(const char *e, const char *r, const char *t) {
    triple_t *tr = &triples[triple_count++];
    strncpy(tr->entity, e, 63);
    strncpy(tr->rel, r, 31);
    strncpy(tr->target, t, 63);
    printf("[KG] Added: %s -[%s]-> %s\n", e, r, t);
}

void kg_query(const char *entity) {
    printf("\n=== Query: %s ===\n", entity);
    for (int i = 0; i < triple_count; i++) {
        if (strcmp(triples[i].entity, entity) == 0) {
            printf("%s -[%s]-> %s\n", triples[i].entity, triples[i].rel, triples[i].target);
        }
    }
    printf("====================\n\n");
}

void kg_path(const char *e1, const char *e2) {
    printf("\n=== Path: %s -> %s ===\n", e1, e2);
    printf("%s\n", e1);
    printf("  |\n  v\n%s\n", e2);
    printf("====================\n\n");
}

void kg_recommend(const char *entity) {
    printf("\n=== Recommend ===\n");
    printf("因为您关注: %s\n", entity);
    printf("推荐:\n");
    printf("1. 相关实体A\n");
    printf("2. 相关实体B\n");
    printf("3. 相关实体C\n");
    printf("====================\n\n");
}

void knowledge_test(void) {
    printf("\n=== Knowledge Test ===\n");
    kg_init();
    kg_add("中国", "首都在", "北京");
    kg_query("马斯克");
    kg_path("马斯克", "美国");
    kg_recommend("人工智能");
    printf("==================\n\n");
}
