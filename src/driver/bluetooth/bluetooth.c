#include <stdio.h>
#include <string.h>

#define MAX_DEVICES 10

// 蓝牙状态
typedef enum {
    BT_OFF,
    BT_SCANNING,
    BT_ON,
    BT_CONNECTED
} bt_status_t;

// 设备类型
typedef enum {
    DEVICE_PHONE,
    DEVICE_HEADSET,
    DEVICE_SPEAKER,
    DEVICE_KEYBOARD,
    DEVICE_MOUSE,
    DEVICE_UNKNOWN
} device_type_t;

// 蓝牙设备
typedef struct {
    char name[32];
    char mac[18];
    device_type_t type;
    int paired;
    int connected;
    int rssi;
} bt_device_t;

static bt_device_t devices[MAX_DEVICES];
static int dev_count = 0;
static bt_status_t bt_status = BT_OFF;

// 初始化
int bluetooth_init(void) {
    printf("[Bluetooth] Initialized\n");
    printf("  Adapter: hci0\n");
    printf("  Address: AA:BB:CC:DD:EE:FF\n");
    return 0;
}

// 启用
int bluetooth_enable(void) {
    printf("[Bluetooth] Enabling...\n");
    bt_status = BT_ON;
    printf("[Bluetooth] Enabled\n");
    return 0;
}

// 禁用
int bluetooth_disable(void) {
    printf("[Bluetooth] Disabling...\n");
    bt_status = BT_OFF;
    printf("[Bluetooth] Disabled\n");
    return 0;
}

// 扫描
int bluetooth_scan(void) {
    printf("[Bluetooth] Scanning...\n");
    bt_status = BT_SCANNING;
    
    dev_count = 0;
    
    bt_device_t *d = &devices[dev_count++];
    strcpy(d->name, "iPhone");
    strcpy(d->mac, "11:22:33:44:55:66");
    d->type = DEVICE_PHONE;
    d->paired = 1;
    d->connected = 0;
    d->rssi = -45;
    
    d = &devices[dev_count++];
    strcpy(d->name, "AirPods Pro");
    strcpy(d->mac, "22:33:44:55:66:77");
    d->type = DEVICE_HEADSET;
    d->paired = 1;
    d->connected = 1;
    d->rssi = -60;
    
    d = &devices[dev_count++];
    strcpy(d->name, "JBL Speaker");
    strcpy(d->mac, "33:44:55:66:77:88");
    d->type = DEVICE_SPEAKER;
    d->paired = 0;
    d->connected = 0;
    d->rssi = -70;
    
    bt_status = BT_ON;
    printf("[Bluetooth] Found %d devices\n", dev_count);
    return dev_count;
}

// 配对
int bluetooth_pair(const char *mac) {
    printf("[Bluetooth] Pairing with %s...\n", mac);
    printf("[Bluetooth] Paired\n");
    return 0;
}

// 连接
int bluetooth_connect(const char *mac) {
    printf("[Bluetooth] Connecting to %s...\n", mac);
    printf("[Bluetooth] Connected\n");
    return 0;
}

// 断开
int bluetooth_disconnect(const char *mac) {
    printf("[Bluetooth] Disconnecting %s...\n", mac);
    printf("[Bluetooth] Disconnected\n");
    return 0;
}

// 发送文件
int bluetooth_send_file(const char *mac, const char *filepath) {
    printf("[Bluetooth] Sending %s to %s...\n", filepath, mac);
    printf("[Bluetooth] Sent\n");
    return 0;
}

// 列出设备
void bluetooth_list(void) {
    printf("\n=== Bluetooth Devices (%d) ===\n", dev_count);
    const char *type_names[] = {"Phone", "Headset", "Speaker", "Keyboard", "Mouse", "Unknown"};
    
    for (int i = 0; i < dev_count; i++) {
        printf("%d. %s (%s) %s %s signal:%d\n",
            i + 1,
            devices[i].name,
            devices[i].mac,
            type_names[devices[i].type],
            devices[i].connected ? "[Connected]" : "[Disconnected]",
            devices[i].rssi);
    }
    printf("===========================\n\n");
}

// 测试
void bluetooth_test(void) {
    printf("\n=== Bluetooth Test ===\n");
    
    bluetooth_enable();
    bluetooth_scan();
    bluetooth_list();
    
    bluetooth_connect("33:44:55:66:77:88");
    bluetooth_disconnect("33:44:55:66:77:88");
    
    printf("==================\n\n");
}
