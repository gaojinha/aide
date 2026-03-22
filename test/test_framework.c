#include "test_framework.h"
#include <stdlib.h>

static int test_count = 0;
static int pass_count = 0;

int run_test(const char *name, int (*func)(void)) {
    test_count++;
    printf("\n[Test %d] %s\n", test_count, name);
    int result = func();
    if (result == 0) {
        pass_count++;
        printf("Result: ✅ PASS\n");
    } else {
        printf("Result: ❌ FAIL\n");
    }
    return result;
}

void test_summary(void) {
    printf("\n╔══════════════════════════════╗\n");
    printf("║ Test Summary               ║\n");
    printf("╠══════════════════════════════╣\n");
    printf("║ Total:  %d                 ║\n", test_count);
    printf("║ Pass:   %d                 ║\n", pass_count);
    printf("║ Fail:   %d                 ║\n", test_count - pass_count);
    printf("╚══════════════════════════════╝\n");
}
