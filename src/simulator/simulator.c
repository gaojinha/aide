/**
 * 模拟器 - 开发板未到时模拟测试
 */

#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct {
    int camera_ready;
    int sensor_ready;
    int network_ready;
    int battery;
} simulator_hw_t;

static simulator_hw_t hw = {.battery = 100};

int sim_init(void) {
    printf("[Simulator] Initializing...\n");
    hw.camera_ready = hw.sensor_ready = hw.network_ready = 1;
    hw.battery = 100;
    printf("[Simulator] Ready\n");
    return 0;
}

int sim_camera_capture(char *data) {
    sprintf(data, "simulated_image_%ld.jpg", time(NULL));
    printf("[Sim] Camera: %s\n", data);
    return 0;
}

float sim_sensor_read(const char *type) {
    printf("[Sim] Sensor %s: ", type);
    if (strcmp(type, "temp") == 0) return 25.5f;
    return 0.0f;
}

int sim_network_send(const char *data) {
    printf("[Sim] Network: %s\n", data);
    return 0;
}
