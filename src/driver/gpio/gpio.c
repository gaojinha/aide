/**
 * GPIO模块
 */

#include <stdio.h>
#include <string.h>

int gpio_init(void) {
    printf("[GPIO] Initialized\n");
    printf("  LED_STATUS(17), LED_POWER(27), BTN_RESET(22), BTN_WAKE(23)\n");
    return 0;
}

void gpio_led_on(const char *name) {
    printf("[GPIO] LED ON: %s\n", name);
}

void gpio_led_off(const char *name) {
    printf("[GPIO] LED OFF: %s\n", name);
}

void gpio_test(void) {
    printf("\n=== GPIO Test ===\n");
    gpio_led_on("LED_STATUS");
    gpio_led_off("LED_STATUS");
    printf("==================\n\n");
}
