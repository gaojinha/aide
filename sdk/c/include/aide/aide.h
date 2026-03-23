/**
 * AIDE SDK - C Language SDK
 * AI Phone Assistant C Library
 */

#ifndef AIDE_SDK_H
#define AIDE_SDK_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========== 版本信息 ========== */
#define AIDE_SDK_VERSION "0.1.0"
#define AIDE_SDK_VER_MAJOR 0
#define AIDE_SDK_VER_MINOR 1
#define AIDE_SDK_VER_PATCH 0

/* ========== 错误码 ========== */
#define AIDE_OK              0
#define AIDE_ERROR          -1
#define AIDE_ERROR_PARAM    -2
#define AIDE_ERROR_NETWORK  -3
#define AIDE_ERROR_TIMEOUT  -4
#define AIDE_ERROR_AUTH     -5
#define AIDE_ERROR_NOMEM    -6

/* ========== 类型定义 ========== */
typedef struct aide_client aide_client_t;
typedef struct aide_result aide_result_t;

typedef void (*aide_callback_t)(const char *data, void *user_data);

/* ========== 客户端 ========== */
aide_client_t* aide_client_new(const char *base_url, const char *api_key);
void aide_client_free(aide_client_t *client);
int aide_client_set_timeout(aide_client_t *client, int timeout_ms);

/* ========== 系统状态 ========== */
int aide_get_status(aide_client_t *client, char *buf, size_t len);

/* ========== 语音 ========== */
int aide_tts(aide_client_t *client, const char *text, const char *voice);
int aide_stt(aide_client_t *client, const char *audio_path, char *buf, size_t len);
int aide_voice_push(aide_client_t *client, const char *device, const char *text);

/* ========== 对话 ========== */
int aide_chat(aide_client_t *client, const char *message, char *buf, size_t len);
int aide_chat_stream(aide_client_t *client, const char *message, aide_callback_t callback, void *user_data);

/* ========== 通知 ========== */
int aide_notify(aide_client_t *client, const char *device, const char *title, const char *body);

/* ========== 远程控制 ========== */
int aide_control(aide_client_t *client, const char *device, const char *action);

/* ========== 传感器 ========== */
int aide_get_sensors(aide_client_t *client, char *buf, size_t len);

/* ========== 摄像头 ========== */
int aide_camera_snap(aide_client_t *client, const char *device, char *buf, size_t len);

/* ========== 文件操作 ========== */
int aide_list_files(aide_client_t *client, const char *path, char *buf, size_t len);
int aide_upload_file(aide_client_t *client, const char *local_path, const char *remote_path);
int aide_download_file(aide_client_t *client, const char *remote_path, const char *local_path);

/* ========== 设置 ========== */
int aide_get_settings(aide_client_t *client, char *buf, size_t len);
int aide_set_setting(aide_client_t *client, const char *key, const char *value);

/* ========== 技能 ========== */
int aide_list_skills(aide_client_t *client, char *buf, size_t len);
int aide_call_skill(aide_client_t *client, const char *skill_name, const char *params, char *buf, size_t len);

/* ========== 场景 ========== */
int aide_list_scenes(aide_client_t *client, char *buf, size_t len);
int aide_switch_scene(aide_client_t *client, const char *scene_name);

/* ========== 设备 ========== */
int aide_list_devices(aide_client_t *client, char *buf, size_t len);
int aide_find_device(aide_client_t *client, const char *device_id);

/* ========== 健康 ========== */
int aide_get_health(aide_client_t *client, char *buf, size_t len);

#ifdef __cplusplus
}
#endif

#endif /* AIDE_SDK_H */
