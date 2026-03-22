/**
 * 电话应用
 */

#include <stdio.h>

int phone_init(void) {
    printf("[App/Phone] Initialized\n");
    return 0;
}

int phone_call(const char *number) {
    printf("[App/Phone] Calling: %s\n", number);
    return 0;
}

int phone_answer(void) {
    return 0;
}

int phone_hangup(void) {
    return 0;
}
