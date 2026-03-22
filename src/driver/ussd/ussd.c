#include <stdio.h>
#include <string.h>

void ussd_init(void) { printf("[USSD] Initialized\n"); }

void ussd_send(const char *code) {
    printf("\n=== USSD: %s ===\n", code);
    if (strcmp(code, "*100#") == 0) {
        printf("运营商: 中国移动\n");
        printf("余额: 58.50元\n");
        printf("流量: 3.5GB\n");
        printf("通话: 120分钟\n");
    } else if (strcmp(code, "*101#") == 0) {
        printf("当前状态: 正常\n");
    }
    printf("====================\n\n");
}

void ussd_balance(void) {
    printf("\n=== Balance ===\n");
    printf("话费: 58.50元\n");
    printf("流量: 3.5GB\n");
    printf("====================\n\n");
}

void ussd_package(void) {
    printf("\n=== Packages ===\n");
    printf("1. 5GB流量包 - 30元\n");
    printf("2. 100分钟通话 - 20元\n");
    printf("3. 短信包 - 10元\n");
    printf("=====================\n\n");
}

void ussd_test(void) {
    printf("\n=== USSD Test ===\n");
    ussd_init();
    ussd_send("*100#");
    ussd_balance();
    ussd_package();
    printf("==================\n\n");
}
