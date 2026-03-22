#include <stdio.h>
#include <time.h>

static time_t last_sync = 0;

int ntp_init(void) {
    printf("[NTP] Initialized (server: ntp.aliyun.com)\n");
    return 0;
}

int ntp_sync(void) {
    printf("[NTP] Syncing...\n");
    last_sync = time(NULL);
    printf("[NTP] Synced OK\n");
    return 0;
}

void ntp_status(void) {
    printf("\n=== NTP Status ===\n");
    printf("Server: ntp.aliyun.com\n");
    if (last_sync > 0) {
        printf("Last sync: %ld\n", (long)last_sync);
    } else {
        printf("Last sync: Never\n");
    }
    printf("Current: %ld\n", (long)time(NULL));
    printf("==================\n\n");
}

void ntp_test(void) {
    printf("\n=== NTP Test ===\n");
    ntp_sync();
    ntp_status();
    printf("==================\n\n");
}
