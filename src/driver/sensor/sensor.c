/**
 * 传感器驱动
 */

#include <stdio.h>

int sensor_init(void) {
    printf("[Driver/Sensor] Initialized\n");
    return 0;
}

float sensor_read_accel(void) {
    // TODO: 读取加速度
    return 0.0f;
}

float sensor_read_gyro(void) {
    // TODO: 读取陀螺仪
    return 0.0f;
}

float sensor_read_light(void) {
    // TODO: 读取光感
    return 0.0f;
}
