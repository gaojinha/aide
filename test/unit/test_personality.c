/**
 * 人格化测试
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../../include/personality.h"

void test_init(void) {
    printf("  [Test] Init...");
    assert(personality_init() == 0);
    printf(" OK\n");
}

void test_set_get(void) {
    printf("  [Test] Set/Get...");
    personality_set("name", "测试");
    assert(strcmp(personality_get("name"), "测试") == 0);
    personality_set("age", "30");
    printf(" OK\n");
}

void test_show(void) {
    printf("  [Test] Show...");
    personality_show();
    printf(" OK\n");
}

void test_generate(void) {
    printf("  [Test] Generate...");
    char response[128];
    personality_generate("你好", response);
    printf(" OK (response: %s)\n", response);
}

int main(void) {
    printf("=== Running Personality Tests ===\n");
    test_init();
    test_set_get();
    test_show();
    test_generate();
    printf("=== All Tests Passed ===\n");
    return 0;
}
