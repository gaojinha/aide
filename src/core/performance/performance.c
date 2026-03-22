#include <stdio.h>
#include <time.h>

// 内存池
extern void mempool_test(void);
extern void mempool_init(void);
extern void mempool_status(void);

// 线程池
extern void threadpool_test(void);
extern void threadpool_init(int threads);

// 缓存
extern void cache_test(void);
extern void cache_init(void);

// 主测试
void performance_test(void) {
    printf("\n");
    printf("╔══════════════════════════════════╗\n");
    printf("║     Performance Test Suite       ║\n");
    printf("╚══════════════════════════════════╝\n\n");
    
    // 内存池测试
    mempool_test();
    
    // 线程池测试
    threadpool_test();
    
    // 缓存测试
    cache_test();
    
    printf("╔══════════════════════════════════╗\n");
    printf("║     All Tests Completed!         ║\n");
    printf("╚══════════════════════════════════╝\n\n");
}
