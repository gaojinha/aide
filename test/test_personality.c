#include <stdio.h>
#include <string.h>
#include "../src/ai/personality.c"

int test_personality_name(void) {
    personality_init();
    
    const char *name = personality_get_name();
    TEST_ASSERT(strcmp(name, "王二狗") == 0, "default name");
    
    personality_set_name("小爱");
    name = personality_get_name();
    TEST_ASSERT(strcmp(name, "小爱") == 0, "set name");
    
    TEST_PASS("personality_name");
    return 0;
}

int test_personality_greeting(void) {
    const char *greet = personality_get_greeting();
    TEST_ASSERT(strlen(greet) > 0, "greeting not empty");
    
    TEST_PASS("personality_greeting");
    return 0;
}
