/**
 * 传感器模块 - 全部手机传感器
 */

#include <stdio.h>
#include <string.h>
#include <time.h>

// ==================== 运动传感器 ====================

// 加速度计
typedef struct {
    float x, y, z;      // m/s²
} accel_t;

// 陀螺仪
typedef struct {
    float x, y, z;      // rad/s
} gyro_t;

// 磁场
typedef struct {
    float x, y, z;      // μT
} mag_t;

// 重力
typedef struct {
    float x, y, z;
} gravity_t;

// 线性加速度
typedef struct {
    float x, y, z;
} linear_accel_t;

// 旋转矢量
typedef struct {
    float x, y, z, w;
} rotation_vector_t;

// ==================== 位置传感器 ====================

// GPS
typedef struct {
    double lat, lon;     // 度
    float altitude;       // 米
    float accuracy;       // 米
    float speed;         // m/s
} gps_t;

// 接近传感器
typedef struct {
    int distance;        // cm
    int near;           // 0/1
} proximity_t;

// 环境光
typedef struct {
    int lux;            // 勒克斯
} als_t;

// ==================== 环境传感器 ====================

// 气压/海拔
typedef struct {
    float pressure;      // hPa
    float altitude;      // 米
} barometer_t;

// 温度
typedef struct {
    float celsius;      // 摄氏度
} temperature_t;

// 湿度
typedef struct {
    float relative;     // %
} humidity_t;

// ==================== 生物传感器 ====================

// 心率
typedef struct {
    int bpm;            // 每分钟心跳
} heart_rate_t;

// 血氧
typedef struct {
    int spo2;           // %
} spo2_t;

// 步数
typedef struct {
    int steps;
    float distance;     // 米
} pedometer_t;

// 全局状态
static int sensor_initialized = 0;

// 初始化所有传感器
int sensor_init(void) {
    printf("[Sensors] Initialized\n");
    printf("  Motion: Accel/Gyro/MAG/Gravity\n");
    printf("  Position: GPS/Proximity/ALS\n");
    printf("  Environment: Barometer/Temp/Humidity\n");
    printf("  Bio: HeartRate/SPO2/Pedometer\n");
    sensor_initialized = 1;
    return 0;
}

// ==================== 运动传感器 ====================

// 加速度计
int sensor_read_accel(accel_t *data) {
    // 模拟数据
    data->x = 0.1;
    data->y = 0.2;
    data->z = 9.8;
    return 0;
}

// 陀螺仪
int sensor_read_gyro(gyro_t *data) {
    data->x = 0.01;
    data->y = -0.02;
    data->z = 0.0;
    return 0;
}

// 磁场
int sensor_read_mag(mag_t *data) {
    data->x = 25.0;
    data->y = 10.0;
    data->z = 45.0;
    return 0;
}

// ==================== 位置传感器 ====================

// GPS
int sensor_read_gps(gps_t *data) {
    // 模拟：西安坐标
    data->lat = 34.3416;
    data->lon = 108.9398;
    data->altitude = 400.0;
    data->accuracy = 5.0;
    data->speed = 0.0;
    return 0;
}

// 接近传感器
int sensor_read_proximity(proximity_t *data) {
    data->distance = 5;
    data->near = 1;  // 靠近耳朵
    return 0;
}

// 环境光
int sensor_read_als(als_t *data) {
    data->lux = 500;  // 室内
    return 0;
}

// ==================== 环境传感器 ====================

// 气压
int sensor_read_barometer(barometer_t *data) {
    data->pressure = 1013.25;  // 标准大气压
    data->altitude = 0.0;
    return 0;
}

// 温度
int sensor_read_temperature(temperature_t *data) {
    data->celsius = 25.0;
    return 0;
}

// 湿度
int sensor_read_humidity(humidity_t *data) {
    data->relative = 45.0;
    return 0;
}

// ==================== 生物传感器 ====================

// 心率
int sensor_read_heart_rate(heart_rate_t *data) {
    data->bpm = 75;
    return 0;
}

// 血氧
int sensor_read_spo2(spo2_t *data) {
    data->spo2 = 98;
    return 0;
}

// 步数
int sensor_read_pedometer(pedometer_t *data) {
    data->steps = 5200;
    data->distance = 3600.0;
    return 0;
}

// ==================== 综合测试 ====================

void sensor_test(void) {
    printf("\n=== Sensors Test ===\n");
    
    // 运动
    accel_t accel;
    sensor_read_accel(&accel);
    printf("Accel: %.2f %.2f %.2f m/s²\n", accel.x, accel.y, accel.z);
    
    gyro_t gyro;
    sensor_read_gyro(&gyro);
    printf("Gyro: %.2f %.2f %.2f rad/s\n", gyro.x, gyro.y, gyro.z);
    
    // 位置
    gps_t gps;
    sensor_read_gps(&gps);
    printf("GPS: %.4f, %.4f (alt: %.1fm)\n", gps.lat, gps.lon, gps.altitude);
    
    als_t als;
    sensor_read_als(&als);
    printf("ALS: %d lux\n", als.lux);
    
    // 环境
    barometer_t baro;
    sensor_read_barometer(&baro);
    printf("Barometer: %.1f hPa\n", baro.pressure);
    
    temperature_t temp;
    sensor_read_temperature(&temp);
    printf("Temp: %.1f °C\n", temp.celsius);
    
    humidity_t hum;
    sensor_read_humidity(&hum);
    printf("Humidity: %.1f %%\n", hum.relative);
    
    // 生物
    heart_rate_t hr;
    sensor_read_heart_rate(&hr);
    printf("Heart Rate: %d bpm\n", hr.bpm);
    
    pedometer_t pedo;
    sensor_read_pedometer(&pedo);
    printf("Pedometer: %d steps (%.1fm)\n", pedo.steps, pedo.distance);
    
    printf("=====================\n\n");
}
