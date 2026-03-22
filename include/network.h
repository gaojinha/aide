#ifndef NETWORK_H
#define NETWORK_H

typedef struct {
    char ssid[32];
    int rssi;
    int channel;
    char enc[16];
} wifi_ap_t;

typedef struct {
    int type;
    int status;
    char ip[16];
    char gateway[16];
    char dns[16];
    int rssi;
} network_info_t;

int network_init(void);
int network_wifi_scan(wifi_ap_t *aps, int max);
int network_wifi_connect(const char *ssid, const char *pass);
int network_get_status(network_info_t *info);
int network_wifi_disconnect(void);
int network_4g_connect(void);

#endif
