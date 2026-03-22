#include <stdio.h>
#include <time.h>
#include <string.h>

#define CACHE_SIZE 100

typedef struct cache_entry {
    char key[64];
    char value[256];
    int hits;
    int ttl;  // 秒
    time_t last_access;
} cache_entry_t;

static cache_entry_t cache[CACHE_SIZE];
static int cache_count = 0;

// 初始化
void cache_init(void) {
    memset(cache, 0, sizeof(cache));
    cache_count = 0;
    printf("[Cache] Initialized: %d entries\n", CACHE_SIZE);
}

// 设置
int cache_set(const char *key, const char *value, int ttl) {
    // 查找已存在
    for (int i = 0; i < CACHE_SIZE; i++) {
        if (cache[i].key[0] && strcmp(cache[i].key, key) == 0) {
            strncpy(cache[i].value, value, 255);
            cache[i].last_access = time(NULL);
            return 0;
        }
    }
    
    // 找空位
    for (int i = 0; i < CACHE_SIZE; i++) {
        if (!cache[i].key[0]) {
            strncpy(cache[i].key, key, 63);
            strncpy(cache[i].value, value, 255);
            cache[i].hits = 0;
            cache[i].ttl = ttl;
            cache[i].last_access = time(NULL);
            cache_count++;
            return 0;
        }
    }
    
    // LRU淘汰
    int lru = 0;
    time_t oldest = cache[0].last_access;
    for (int i = 1; i < CACHE_SIZE; i++) {
        if (cache[i].last_access < oldest) {
            oldest = cache[i].last_access;
            lru = i;
        }
    }
    
    strncpy(cache[lru].key, key, 63);
    strncpy(cache[lru].value, value, 255);
    cache[lru].hits = 0;
    cache[lru].ttl = ttl;
    cache[lru].last_access = time(NULL);
    
    return 0;
}

// 获取
const char* cache_get(const char *key) {
    for (int i = 0; i < CACHE_SIZE; i++) {
        if (cache[i].key[0] && strcmp(cache[i].key, key) == 0) {
            cache[i].hits++;
            cache[i].last_access = time(NULL);
            return cache[i].value;
        }
    }
    return NULL;
}

// 状态
void cache_status(void) {
    int total_hits = 0;
    for (int i = 0; i < CACHE_SIZE; i++) {
        total_hits += cache[i].hits;
    }
    
    printf("\n=== Cache Status ===\n");
    printf("Entries: %d/%d\n", cache_count, CACHE_SIZE);
    printf("Total hits: %d\n", total_hits);
    printf("====================\n\n");
}

void cache_test(void) {
    printf("\n=== Cache Test ===\n");
    cache_init();
    
    cache_set("name", "aide", 60);
    cache_set("version", "0.1.0", 60);
    cache_set("model", "MiniMax", 60);
    
    printf("Get name: %s\n", cache_get("name"));
    printf("Get version: %s\n", cache_get("version"));
    printf("Get model: %s\n", cache_get("model"));
    printf("Get missing: %s\n", cache_get("none") ? "found" : "NULL");
    
    cache_get("name");  // 再次访问增加hits
    cache_get("name");
    
    cache_status();
    printf("==================\n\n");
}
