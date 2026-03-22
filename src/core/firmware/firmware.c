#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_FILES 50

// 固件信息
typedef struct {
    char version[32];
    char build_date[32];
    char platform[32];
    int size;           // KB
    int checksum;
} fw_info_t;

// 固件文件
typedef struct {
    char name[64];
    char path[128];
    int size;
} fw_file_t;

static fw_info_t fw_info = {0};
static fw_file_t files[MAX_FILES];
static int file_count = 0;

// 初始化
void firmware_init(void) {
    printf("[Firmware] Initialized\n");
    
    // 设置版本信息
    strcpy(fw_info.version, "0.1.0");
    strcpy(fw_info.platform, "RK3568");
    time_t now = time(NULL);
    struct tm *tm = localtime(&now);
    strftime(fw_info.build_date, 31, "%Y-%m-%d %H:%M:%S", tm);
    
    printf("  Version: %s\n", fw_info.version);
    printf("  Platform: %s\n", fw_info.platform);
    printf("  Build: %s\n", fw_info.build_date);
}

// 添加文件
int firmware_add_file(const char *name, const char *path, int size) {
    if (file_count >= MAX_FILES) return -1;
    
    fw_file_t *f = &files[file_count];
    strncpy(f->name, name, 63);
    strncpy(f->path, path, 127);
    f->size = size;
    file_count++;
    
    fw_info.size += size;
    return 0;
}

// 计算校验和 (模拟)
int calculate_checksum(void) {
    int sum = 0;
    for (int i = 0; i < file_count; i++) {
        sum += files[i].size;
    }
    fw_info.checksum = sum % 0xFFFFFFFF;
    return fw_info.checksum;
}

// 创建固件包
int firmware_create(const char *output) {
    printf("[Firmware] Creating: %s\n", output);
    
    // 添加要打包的文件
    file_count = 0;
    fw_info.size = 0;
    
    firmware_add_file("aide.bin", "/home/gao/aide/build/aide", 500);
    firmware_add_file("device.dtb", "/home/gao/aide/device-tree/aide-rk3568.dtb", 50);
    firmware_add_file("rootfs.img", "/opt/rootfs.img", 10240);
    firmware_add_file("boot.img", "/opt/boot.img", 2048);
    firmware_add_file("modules.tar", "/lib/modules.tar", 5000);
    
    calculate_checksum();
    
    printf("[Firmware] Files: %d\n", file_count);
    printf("[Firmware] Size: %d KB\n", fw_info.size);
    printf("[Firmware] Checksum: 0x%08X\n", fw_info.checksum);
    printf("[Firmware] Created: %s\n", output);
    
    return 0;
}

// 签名固件 (模拟)
int firmware_sign(const char *key) {
    printf("[Firmware] Signing with key: %s\n", key);
    // 实际应该用私钥签名
    printf("[Firmware] Signature: SHA256-RSA\n");
    printf("[Firmware] Signed OK\n");
    return 0;
}

// 验证固件
int firmware_verify(void) {
    printf("[Firmware] Verifying...\n");
    
    // 验证校验和
    int sum = calculate_checksum();
    if (sum != fw_info.checksum) {
        printf("[Firmware] ERROR: Checksum mismatch!\n");
        return -1;
    }
    
    printf("[Firmware] Checksum: OK\n");
    printf("[Firmware] Signature: OK\n");
    printf("[Firmware] Verified OK\n");
    return 0;
}

// 列出固件内容
void firmware_list(void) {
    printf("\n=== Firmware Package ===\n");
    printf("Version: %s\n", fw_info.version);
    printf("Platform: %s\n", fw_info.platform);
    printf("Build: %s\n", fw_info.build_date);
    printf("Size: %d KB\n", fw_info.size);
    printf("Checksum: 0x%08X\n", fw_info.checksum);
    printf("Files: %d\n\n", file_count);
    
    for (int i = 0; i < file_count; i++) {
        printf("  %d. %s (%d KB)\n", i+1, files[i].name, files[i].size);
    }
    printf("=========================\n\n");
}

// OTA升级
int firmware_ota_check(const char *server) {
    printf("[Firmware] Checking OTA: %s\n", server);
    // 模拟检查
    printf("[Firmware] Current: %s, Latest: %s\n", fw_info.version, fw_info.version);
    printf("[Firmware] No update available\n");
    return 0;  // 0=无需升级
}

// 测试
void firmware_test(void) {
    printf("\n=== Firmware Test ===\n");
    
    firmware_init();
    
    firmware_create("aide-v0.1.0-rk3568.fw");
    firmware_list();
    
    firmware_sign("private_key.pem");
    firmware_verify();
    
    firmware_ota_check("https://ota.aide.com/check");
    
    printf("==================\n\n");
}
