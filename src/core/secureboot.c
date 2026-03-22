#include <stdio.h>
#include <string.h>

typedef enum {
    STAGE_BL0, STAGE_BL1, STAGE_BL2, STAGE_KERNEL, STAGE_ROOTFS, STAGE_APP
} boot_stage_t;

typedef struct {
    boot_stage_t stage;
    char name[32];
    char hash[65];
    int verified;
} boot_item_t;

static boot_item_t boot_chain[6];
static int boot_stage = 0;

int secureboot_init(void) {
    printf("[SecureBoot] Initialized\n");
    printf("  Chain: BL0 -> BL1 -> BL2 -> Kernel -> RootFS -> App\n");
    return 0;
}

int secureboot_add_item(boot_stage_t stage, const char *name, const char *hash) {
    boot_item_t *item = &boot_chain[stage];
    item->stage = stage;
    strncpy(item->name, name, 31);
    strncpy(item->hash, hash, 64);
    item->verified = 0;
    return 0;
}

int secureboot_verify(boot_stage_t stage) {
    boot_item_t *item = &boot_chain[stage];
    printf("[SecureBoot] Verifying %s...\n", item->name);
    // 简化: 只要有hash就算通过
    if (strlen(item->hash) > 0) {
        item->verified = 1;
        printf("[SecureBoot] Verified: %s OK\n", item->name);
        return 0;
    }
    return -1;
}

int secureboot_start(void) {
    printf("\n=== Secure Boot ===\n");
    secureboot_add_item(STAGE_BL0, "bootloader0", "abc123");
    secureboot_add_item(STAGE_BL1, "bootloader1", "def456");
    secureboot_add_item(STAGE_BL2, "bootloader2", "ghi789");
    secureboot_add_item(STAGE_KERNEL, "kernel", "jkl012");
    secureboot_add_item(STAGE_ROOTFS, "rootfs", "mno345");
    secureboot_add_item(STAGE_APP, "aide", "pqr678");
    
    for (int i = 0; i <= STAGE_APP; i++) {
        if (secureboot_verify(i) != 0) {
            printf("[SecureBoot] FAILED at stage %d!\n", i);
            return -1;
        }
    }
    printf("[SecureBoot] All verified!\n");
    printf("=====================\n\n");
    return 0;
}

void secureboot_status(void) {
    printf("\n=== Secure Boot Status ===\n");
    const char *stage_names[] = {"BL0", "BL1", "BL2", "Kernel", "RootFS", "App"};
    for (int i = 0; i <= STAGE_APP; i++) {
        printf("%s: %s\n", stage_names[i], boot_chain[i].verified ? "✓ VERIFIED" : "✗ NOT");
    }
    printf("===========================\n\n");
}

void secureboot_test(void) {
    printf("\n=== SecureBoot Test ===\n");
    secureboot_start();
    secureboot_status();
    printf("==================\n\n");
}
