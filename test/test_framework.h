#ifndef TEST_H
#define TEST_H

#include <stdio.h>

#define TEST_ASSERT(cond, msg) do { \
    if (!(cond)) { \
        printf("  ❌ FAIL: %s\n", msg); \
        return 1; \
    } \
} while(0)

#define TEST_PASS(msg) printf("  ✅ PASS: %s\n", msg)

int run_test(const char *name, int (*func)(void));

#endif
