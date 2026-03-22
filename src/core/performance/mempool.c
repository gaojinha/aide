#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MEMPOOL_BLOCKS 100
#define MEMPOOL_BLOCK_SIZE 256

typedef struct mem_block {
    int id;
    int size;
    int used;
    struct mem_block *next;
} mem_block_t;

static mem_block_t pool[MEMPOOL_BLOCKS];
static mem_block_t *free_list = NULL;
static int total_used = 0;

// 初始化
void mempool_init(void) {
    printf("[MemPool] Initialized: %d blocks x %d bytes\n", 
        MEMPOOL_BLOCKS, MEMPOOL_BLOCK_SIZE);
    
    free_list = &pool[0];
    for (int i = 0; i < MEMPOOL_BLOCKS - 1; i++) {
        pool[i].id = i;
        pool[i].size = MEMPOOL_BLOCK_SIZE;
        pool[i].used = 0;
        pool[i].next = &pool[i + 1];
    }
    pool[MEMPOOL_BLOCKS - 1].next = NULL;
}

// 分配
void* mempool_alloc(int size) {
    if (size > MEMPOOL_BLOCK_SIZE) {
        printf("[MemPool] ERROR: size %d > block_size %d\n", size, MEMPOOL_BLOCK_SIZE);
        return NULL;
    }
    
    if (!free_list) {
        printf("[MemPool] ERROR: out of memory\n");
        return NULL;
    }
    
    mem_block_t *block = free_list;
    free_list = block->next;
    block->used = 1;
    total_used += size;
    
    return block;
}

// 释放
void mempool_free(void *ptr) {
    if (!ptr) return;
    
    mem_block_t *block = (mem_block_t *)ptr;
    block->used = 0;
    block->next = free_list;
    free_list = block;
    total_used -= block->size;
}

// 状态
void mempool_status(void) {
    int used = 0;
    for (int i = 0; i < MEMPOOL_BLOCKS; i++) {
        if (pool[i].used) used++;
    }
    
    printf("\n=== MemPool Status ===\n");
    printf("Total: %d blocks (%d KB)\n", MEMPOOL_BLOCKS, MEMPOOL_BLOCKS * MEMPOOL_BLOCK_SIZE / 1024);
    printf("Used: %d blocks (%.1f%%)\n", used, 100.0 * used / MEMPOOL_BLOCKS);
    printf("Memory: %d bytes\n", total_used);
    printf("=====================\n\n");
}

void mempool_test(void) {
    printf("\n=== MemPool Test ===\n");
    mempool_init();
    mempool_status();
    
    void *p1 = mempool_alloc(100);
    void *p2 = mempool_alloc(200);
    void *p3 = mempool_alloc(50);
    
    mempool_status();
    
    mempool_free(p2);
    mempool_status();
    
    printf("==================\n\n");
}
