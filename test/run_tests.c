#include <stdio.h>
#include "test_framework.c"

// 测试函数声明
extern int test_storage_basic(void);
extern int test_storage_string(void);
extern int test_personality_name(void);
extern int test_personality_greeting(void);
extern int test_http_get(void);
extern int test_http_post(void);
extern int test_settings_basic(void);

int main() {
    printf("╔══════════════════════════════╗\n");
    printf("║     aide Unit Tests        ║\n");
    printf("╚══════════════════════════════╝\n");
    
    // 运行所有测试
    run_test("Storage Basic", test_storage_basic);
    run_test("Storage String", test_storage_string);
    run_test("Personality Name", test_personality_name);
    run_test("Personality Greeting", test_personality_greeting);
    run_test("HTTP GET", test_http_get);
    run_test("HTTP POST", test_http_post);
    run_test("Settings Basic", test_settings_basic);
    
    test_summary();
    return 0;
}
