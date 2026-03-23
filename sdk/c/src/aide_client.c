/**
 * AIDE SDK - C Implementation
 */

#include <aide/aide.h>
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct aide_client {
    char base_url[256];
    char api_key[128];
    int timeout;
    CURL *curl;
};

struct aide_result {
    char *data;
    size_t size;
    long http_code;
};

static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    aide_result_t *result = (aide_result_t *)userp;
    
    char *ptr = realloc(result->data, result->size + realsize + 1);
    if (!ptr) return 0;
    
    result->data = ptr;
    memcpy(&(result->data[result->size]), contents, realsize);
    result->size += realsize;
    result->data[result->size] = 0;
    
    return realsize;
}

static int http_request(aide_client_t *client, const char *method, const char *path, 
                       const char *body, aide_result_t *result) {
    CURL *curl = client->curl;
    char url[512];
    struct curl_slist *headers = NULL;
    
    snprintf(url, sizeof(url), "%s%s", client->base_url, path);
    
    curl_easy_reset(curl);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, client->timeout);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, result);
    
    if (client->api_key[0]) {
        char auth_header[256];
        snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", client->api_key);
        headers = curl_slist_append(headers, auth_header);
    }
    
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    
    if (strcmp(method, "POST") == 0) {
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        if (body) curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);
    } else if (strcmp(method, "PUT") == 0) {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
        if (body) curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);
    } else if (strcmp(method, "DELETE") == 0) {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
    }
    
    CURLcode res = curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &result->http_code);
    curl_slist_free_all(headers);
    
    if (res != CURLE_OK) {
        return AIDE_ERROR_NETWORK;
    }
    
    return AIDE_OK;
}

/* ========== 客户端 ========== */
aide_client_t* aide_client_new(const char *base_url, const char *api_key) {
    aide_client_t *client = calloc(1, sizeof(aide_client_t));
    if (!client) return NULL;
    
    strncpy(client->base_url, base_url ? base_url : "http://localhost:8080", 255);
    strncpy(client->api_key, api_key ? api_key : "", 127);
    client->timeout = 30000;
    
    client->curl = curl_easy_init();
    if (!client->curl) {
        free(client);
        return NULL;
    }
    
    return client;
}

void aide_client_free(aide_client_t *client) {
    if (client) {
        if (client->curl) curl_easy_cleanup(client->curl);
        free(client);
    }
}

int aide_client_set_timeout(aide_client_t *client, int timeout_ms) {
    if (!client) return AIDE_ERROR_PARAM;
    client->timeout = timeout_ms;
    return AIDE_OK;
}

/* ========== 系统状态 ========== */
int aide_get_status(aide_client_t *client, char *buf, size_t len) {
    aide_result_t result = {0};
    int ret = http_request(client, "GET", "/api/v1/status", NULL, &result);
    
    if (ret == AIDE_OK && buf && len > 0) {
        size_t copy_len = result.size < len - 1 ? result.size : len - 1;
        memcpy(buf, result.data, copy_len);
        buf[copy_len] = 0;
    }
    
    free(result.data);
    return ret == AIDE_OK ? (int)result.http_code : ret;
}

/* ========== 语音 ========== */
int aide_tts(aide_client_t *client, const char *text, const char *voice) {
    char body[2048];
    snprintf(body, sizeof(body), "{\"text\":\"%s\",\"voice\":\"%s\"}", text, voice ? voice : "zh-CN-XiaoxiaoNeural");
    
    aide_result_t result = {0};
    int ret = http_request(client, "POST", "/api/v1/tts", body, &result);
    free(result.data);
    return ret == AIDE_OK ? (int)result.http_code : ret;
}

int aide_stt(aide_client_t *client, const char *audio_path, char *buf, size_t len) {
    // 简化实现
    (void)client; (void)audio_path; (void)buf; (void)len;
    return AIDE_OK;
}

int aide_voice_push(aide_client_t *client, const char *device, const char *text) {
    char body[1024];
    snprintf(body, sizeof(body), "{\"device\":\"%s\",\"text\":\"%s\"}", device, text);
    
    aide_result_t result = {0};
    int ret = http_request(client, "POST", "/api/v1/voice", body, &result);
    free(result.data);
    return ret == AIDE_OK ? (int)result.http_code : ret;
}

/* ========== 对话 ========== */
int aide_chat(aide_client_t *client, const char *message, char *buf, size_t len) {
    char body[4096];
    snprintf(body, sizeof(body), "{\"message\":\"%s\"}", message);
    
    aide_result_t result = {0};
    int ret = http_request(client, "POST", "/api/v1/chat", body, &result);
    
    if (ret == AIDE_OK && buf && len > 0) {
        size_t copy_len = result.size < len - 1 ? result.size : len - 1;
        memcpy(buf, result.data, copy_len);
        buf[copy_len] = 0;
    }
    
    free(result.data);
    return ret == AIDE_OK ? (int)result.http_code : ret;
}

int aide_chat_stream(aide_client_t *client, const char *message, aide_callback_t callback, void *user_data) {
    // 流式响应 - 简化实现
    char buf[4096];
    int ret = aide_chat(client, message, buf, sizeof(buf));
    if (ret == 200 && callback) {
        callback(buf, user_data);
    }
    return ret;
}

/* ========== 通知 ========== */
int aide_notify(aide_client_t *client, const char *device, const char *title, const char *body) {
    char json[1024];
    snprintf(json, sizeof(json), "{\"device\":\"%s\",\"title\":\"%s\",\"body\":\"%s\"}", device, title, body);
    
    aide_result_t result = {0};
    int ret = http_request(client, "POST", "/api/v1/notification", json, &result);
    free(result.data);
    return ret == AIDE_OK ? (int)result.http_code : ret;
}

/* ========== 远程控制 ========== */
int aide_control(aide_client_t *client, const char *device, const char *action) {
    char json[512];
    snprintf(json, sizeof(json), "{\"device\":\"%s\",\"action\":\"%s\"}", device, action);
    
    aide_result_t result = {0};
    int ret = http_request(client, "POST", "/api/v1/control", json, &result);
    free(result.data);
    return ret == AIDE_OK ? (int)result.http_code : ret;
}

/* ========== 传感器 ========== */
int aide_get_sensors(aide_client_t *client, char *buf, size_t len) {
    aide_result_t result = {0};
    int ret = http_request(client, "GET", "/api/v1/sensors", NULL, &result);
    
    if (ret == AIDE_OK && buf && len > 0) {
        size_t copy_len = result.size < len - 1 ? result.size : len - 1;
        memcpy(buf, result.data, copy_len);
        buf[copy_len] = 0;
    }
    
    free(result.data);
    return ret == AIDE_OK ? (int)result.http_code : ret;
}

/* ========== 摄像头 ========== */
int aide_camera_snap(aide_client_t *client, const char *device, char *buf, size_t len) {
    char json[256];
    snprintf(json, sizeof(json), "{\"device\":\"%s\"}", device ? device : "default");
    
    aide_result_t result = {0};
    int ret = http_request(client, "POST", "/api/v1/camera/snap", json, &result);
    
    if (ret == AIDE_OK && buf && len > 0) {
        size_t copy_len = result.size < len - 1 ? result.size : len - 1;
        memcpy(buf, result.data, copy_len);
        buf[copy_len] = 0;
    }
    
    free(result.data);
    return ret == AIDE_OK ? (int)result.http_code : ret;
}

/* ========== 文件操作 ========== */
int aide_list_files(aide_client_t *client, const char *path, char *buf, size_t len) {
    char url[512];
    snprintf(url, sizeof(url), "/api/v1/files?path=%s", path ? path : "/");
    
    aide_result_t result = {0};
    int ret = http_request(client, "GET", url, NULL, &result);
    
    if (ret == AIDE_OK && buf && len > 0) {
        size_t copy_len = result.size < len - 1 ? result.size : len - 1;
        memcpy(buf, result.data, copy_len);
        buf[copy_len] = 0;
    }
    
    free(result.data);
    return ret == AIDE_OK ? (int)result.http_code : ret;
}

int aide_upload_file(aide_client_t *client, const char *local_path, const char *remote_path) {
    (void)client; (void)local_path; (void)remote_path;
    return AIDE_OK;  // 简化实现
}

int aide_download_file(aide_client_t *client, const char *remote_path, const char *local_path) {
    (void)client; (void)remote_path; (void)local_path;
    return AIDE_OK;  // 简化实现
}

/* ========== 设置 ========== */
int aide_get_settings(aide_client_t *client, char *buf, size_t len) {
    aide_result_t result = {0};
    int ret = http_request(client, "GET", "/api/v1/settings", NULL, &result);
    
    if (ret == AIDE_OK && buf && len > 0) {
        size_t copy_len = result.size < len - 1 ? result.size : len - 1;
        memcpy(buf, result.data, copy_len);
        buf[copy_len] = 0;
    }
    
    free(result.data);
    return ret == AIDE_OK ? (int)result.http_code : ret;
}

int aide_set_setting(aide_client_t *client, const char *key, const char *value) {
    char json[512];
    snprintf(json, sizeof(json), "{\"%s\":\"%s\"}", key, value);
    
    aide_result_t result = {0};
    int ret = http_request(client, "PUT", "/api/v1/settings", json, &result);
    free(result.data);
    return ret == AIDE_OK ? (int)result.http_code : ret;
}

/* ========== 技能 ========== */
int aide_list_skills(aide_client_t *client, char *buf, size_t len) {
    aide_result_t result = {0};
    int ret = http_request(client, "GET", "/api/v1/skills", NULL, &result);
    
    if (ret == AIDE_OK && buf && len > 0) {
        size_t copy_len = result.size < len - 1 ? result.size : len - 1;
        memcpy(buf, result.data, copy_len);
        buf[copy_len] = 0;
    }
    
    free(result.data);
    return ret == AIDE_OK ? (int)result.http_code : ret;
}

int aide_call_skill(aide_client_t *client, const char *skill_name, const char *params, char *buf, size_t len) {
    char path[256];
    char body[2048];
    
    snprintf(path, sizeof(path), "/api/v1/skills/%s", skill_name);
    snprintf(body, sizeof(body), "%s", params ? params : "{}");
    
    aide_result_t result = {0};
    int ret = http_request(client, "POST", path, body, &result);
    
    if (ret == AIDE_OK && buf && len > 0) {
        size_t copy_len = result.size < len - 1 ? result.size : len - 1;
        memcpy(buf, result.data, copy_len);
        buf[copy_len] = 0;
    }
    
    free(result.data);
    return ret == AIDE_OK ? (int)result.http_code : ret;
}

/* ========== 场景 ========== */
int aide_list_scenes(aide_client_t *client, char *buf, size_t len) {
    aide_result_t result = {0};
    int ret = http_request(client, "GET", "/api/v1/scenes", NULL, &result);
    
    if (ret == AIDE_OK && buf && len > 0) {
        size_t copy_len = result.size < len - 1 ? result.size : len - 1;
        memcpy(buf, result.data, copy_len);
        buf[copy_len] = 0;
    }
    
    free(result.data);
    return ret == AIDE_OK ? (int)result.http_code : ret;
}

int aide_switch_scene(aide_client_t *client, const char *scene_name) {
    char json[256];
    snprintf(json, sizeof(json), "{\"scene\":\"%s\"}", scene_name);
    
    aide_result_t result = {0};
    int ret = http_request(client, "POST", "/api/v1/scenes/switch", json, &result);
    free(result.data);
    return ret == AIDE_OK ? (int)result.http_code : ret;
}

/* ========== 设备 ========== */
int aide_list_devices(aide_client_t *client, char *buf, size_t len) {
    aide_result_t result = {0};
    int ret = http_request(client, "GET", "/api/v1/devices", NULL, &result);
    
    if (ret == AIDE_OK && buf && len > 0) {
        size_t copy_len = result.size < len - 1 ? result.size : len - 1;
        memcpy(buf, result.data, copy_len);
        buf[copy_len] = 0;
    }
    
    free(result.data);
    return ret == AIDE_OK ? (int)result.http_code : ret;
}

int aide_find_device(aide_client_t *client, const char *device_id) {
    char path[256];
    snprintf(path, sizeof(path), "/api/v1/devices/%s/find", device_id);
    
    aide_result_t result = {0};
    int ret = http_request(client, "POST", path, "{}", &result);
    free(result.data);
    return ret == AIDE_OK ? (int)result.http_code : ret;
}

/* ========== 健康 ========== */
int aide_get_health(aide_client_t *client, char *buf, size_t len) {
    aide_result_t result = {0};
    int ret = http_request(client, "GET", "/api/v1/health", NULL, &result);
    
    if (ret == AIDE_OK && buf && len > 0) {
        size_t copy_len = result.size < len - 1 ? result.size : len - 1;
        memcpy(buf, result.data, copy_len);
        buf[copy_len] = 0;
    }
    
    free(result.data);
    return ret == AIDE_OK ? (int)result.http_code : ret;
}
