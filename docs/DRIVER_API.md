# aide 驱动API

## GPIO

```c
int gpio_init(void);
int gpio_set_mode(int pin, int mode);  // INPUT/OUTPUT
int gpio_write(int pin, int value);
int gpio_read(int pin);
```

## 传感器

```c
int sensor_init(void);
int sensor_read(sensor_type_t type, float *value);
int sensor_calibrate(sensor_type_t type);
```

### 传感器类型
- SENSOR_ACCEL: 加速度
- SENSOR_GYRO: 陀螺仪
- SENSOR_MAG: 磁场
- SENSOR_TEMP: 温度
- SENSOR_HUMIDITY: 湿度
- SENSOR_PRESSURE: 气压
- SENSOR_GPS: GPS
- SENSOR_LIGHT: 光照
- SENSOR_PROXIMITY: 距离

## WiFi

```c
int wifi_init(void);
int wifi_enable(void);
int wifi_disable(void);
int wifi_scan(void);
int wifi_connect(const char *ssid, const char *password);
int wifi_disconnect(void);
```

## 蓝牙

```c
int bluetooth_init(void);
int bluetooth_enable(void);
int bluetooth_disable(void);
int bluetooth_scan(void);
int bluetooth_pair(const char *mac);
int bluetooth_connect(const char *mac);
int bluetooth_disconnect(const char *mac);
```

## 音频

```c
int audio_init(void);
int audio_set_volume(int vol);
int audio_play(int track_id);
int audio_pause(void);
int audio_stop(void);
int audio_record(const char *file, int seconds);
```

## 视频

```c
int video_init(void);
int video_play(int video_id);
int video_pause(void);
int video_stop(void);
int video_seek(int seconds);
int video_fullscreen(int enable);
```

## 电源

```c
int power_init(void);
int power_get_percentage(void);
int power_start_charging(void);
int power_stop_charging(void);
int power_suspend(void);
int power_shutdown(void);
int power_reboot(void);
```

## 红外

```c
int ir_init(void);
int ir_decode(unsigned int raw_code);
int ir_send(ir_key_t key);
```

## 文件管理

```c
int file_manager_init(void);
int file_list(const char *path);
int file_copy(const char *src, const char *dst);
int file_move(const char *src, const char *dst);
int file_delete(const char *path);
int file_mkdir(const char *path);
```
