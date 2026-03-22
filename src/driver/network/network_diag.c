#include <stdio.h>
#include <string.h>

#define MAX_HOSTS 10

// 网络接口
typedef struct {
    char name[16];
    char ip[16];
    char mac[18];
    int up;
    int speed;  // Mbps
} net_interface_t;

// 诊断结果
typedef struct {
    char host[64];
    int success;
    int time_ms;
    int packet_loss;
} ping_result_t;

static net_interface_t ifaces[5];
static int iface_count = 0;

// 初始化
void net_diag_init(void) {
    printf("[NetDiag] Initialized\n");
    
    // 模拟网卡
    strcpy(ifaces[0].name, "eth0");
    strcpy(ifaces[0].ip, "192.168.1.100");
    strcpy(ifaces[0].mac, "AA:BB:CC:DD:EE:FF");
    ifaces[0].up = 1;
    ifaces[0].speed = 1000;
    iface_count++;
    
    strcpy(ifaces[1].name, "wlan0");
    strcpy(ifaces[1].ip, "192.168.1.101");
    strcpy(ifaces[1].mac, "11:22:33:44:55:66");
    ifaces[1].up = 1;
    ifaces[1].speed = 300;
    iface_count++;
    
    printf("  Interfaces: %d\n", iface_count);
}

// Ping
int net_ping(const char *host, int count) {
    printf("[NetDiag] Pinging %s (%d times)...\n", host, count);
    
    int success = 0;
    int total_time = 0;
    
    for (int i = 0; i < count; i++) {
        // 模拟ping
        int time_ms = 10 + rand() % 50;
        total_time += time_ms;
        
        if (rand() % 10 > 1) {  // 90%成功率
            success++;
            printf("  Reply from %s: time=%dms\n", host, time_ms);
        } else {
            printf("  Request timeout\n");
        }
    }
    
    int loss = (count - success) * 100 / count;
    printf("\n--- Ping statistics ---\n");
    printf("%s: packets: %d sent, %d received, %d%% loss\n", 
        host, count, success, loss);
    printf("rtt min/avg/max = %d/%d/%d ms\n", 
        10, total_time / count, 60);
    
    return success > 0 ? 0 : -1;
}

// Traceroute
int net_traceroute(const char *host) {
    printf("[NetDiag] Traceroute to %s...\n", host);
    
    const char *hops[] = {
        "192.168.1.1",
        "10.0.0.1",
        "172.16.0.1",
        "61.135.169.125"  // 百度
    };
    
    for (int i = 0; i < 4; i++) {
        printf("  %d  %s  %d ms\n", i+1, hops[i], (i+1)*5);
    }
    printf("  %s (destination)\n", host);
    
    return 0;
}

// DNS查询
int net_dns(const char *domain) {
    printf("[NetDiag] DNS lookup: %s\n", domain);
    
    if (strcmp(domain, "baidu.com") == 0) {
        printf("  -> 220.181.38.149\n");
        printf("  -> 220.181.38.148\n");
    } else if (strcmp(domain, "google.com") == 0) {
        printf("  -> 142.250.185.78\n");
    } else {
        printf("  -> 8.8.8.8 (resolved)\n");
    }
    
    return 0;
}

// 网速测试
void net_speedtest(void) {
    printf("[NetDiag] Speed test...\n");
    printf("  Download: %d Mbps\n", 50 + rand() % 100);
    printf("  Upload: %d Mbps\n", 20 + rand() % 50);
    printf("  Ping: %d ms\n", 10 + rand() % 30);
}

// 网络接口状态
void net_iface_status(void) {
    printf("\n=== Network Interfaces ===\n");
    
    for (int i = 0; i < iface_count; i++) {
        printf("%d. %s\n", i+1, ifaces[i].name);
        printf("   IP: %s\n", ifaces[i].ip);
        printf("   MAC: %s\n", ifaces[i].mac);
        printf("   Status: %s\n", ifaces[i].up ? "UP" : "DOWN");
        printf("   Speed: %d Mbps\n", ifaces[i].speed);
        printf("\n");
    }
    printf("=========================\n\n");
}

// Netstat
void net_netstat(void) {
    printf("\n=== Netstat ===\n");
    printf("Proto Recv-Q Send-Q Local Address    Foreign Address   State\n");
    printf("tcp   0      0      0.0.0.0:22       0.0.0.0:*        LISTEN\n");
    printf("tcp   0      0      0.0.0.0:80       0.0.0.0:*        LISTEN\n");
    printf("tcp   0      0      192.168.1.100:80  192.168.1.10:5432 ESTABLISHED\n");
    printf("tcp   0      0      192.168.1.100:443 192.168.1.10:5433 ESTABLISHED\n");
    printf("udp   0      0      0.0.0.0:53       0.0.0.0:*\n");
    printf("======================\n\n");
}

// 测试
void net_diag_test(void) {
    printf("\n=== NetDiag Test ===\n");
    
    net_iface_status();
    
    printf("Ping test:\n");
    net_ping("baidu.com", 4);
    
    printf("\nTraceroute:\n");
    net_traceroute("google.com");
    
    printf("\nDNS lookup:\n");
    net_dns("baidu.com");
    
    printf("\nSpeed test:\n");
    net_speedtest();
    
    printf("\nNetstat:\n");
    net_netstat();
    
    printf("==================\n\n");
}
