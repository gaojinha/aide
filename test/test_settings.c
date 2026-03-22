#include <stdio.h>
#include <string.h>
#include "../src/app/settings/settings.c"

int test_settings_basic(void) {
    settings_init();
    
    settings_set_string("test_key", "test_value");
    const char *val = settings_get_string("test_key");
    TEST_ASSERT(strcmp(val, "test_value") == 0, "set/get string");
    
    settings_set_int("test_int", 42);
    int ival = settings_get_int("test_int");
    TEST_ASSERT(ival == 42, "set/get int");
    
    settings_set_bool("test_bool", 1);
    int bval = settings_get_bool("test_bool");
    TEST_ASSERT(bval == 1, "set/get bool");
    
    TEST_PASS("settings_basic");
    return 0;
}
