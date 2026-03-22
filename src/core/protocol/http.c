/**
 * HTTP客户端实现
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_HEADER 64
#define MAX_BODY 4096

typedef struct {
    char method[16];
    char url[256];
    char headers[MAX_HEADER][128];
    int header_count;
    char body[MAX_BODY];
} http_request_t;

typedef struct {
    int status_code;
    char status_msg[64];
    char headers[MAX_HEADER][128];
    int header_count;
    char body[MAX_BODY];
} http_response_t;

// 添加响应头
static void add_response_header(http_response_t *resp, const char *key, const char *value) {
    if (resp->header_count < MAX_HEADER) {
        snprintf(resp->headers[resp->header_count], 128, "%s: %s", key, value);
        resp->header_count++;
    }
}

// HTTP GET
int http_get(const char *url, void *resp_ptr) {
    http_response_t *resp = (http_response_t *)resp_ptr;
    printf("[HTTP] GET %s\n", url);
    
    // 模拟响应
    if (resp) {
        resp->status_code = 200;
        strcpy(resp->status_msg, "OK");
        strcpy(resp->body, "{\"status\":\"ok\"}");
        add_response_header(resp, "Content-Type", "application/json");
    }
    
    printf("[HTTP] Response: 200 OK\n");
    return 0;
}

// HTTP POST
int http_post(const char *url, const char *data, void *resp_ptr) {
    http_response_t *resp = (http_response_t *)resp_ptr;
    printf("[HTTP] POST %s\n", url);
    printf("[HTTP] Body: %s\n", data);
    
    if (resp) {
        resp->status_code = 201;
        strcpy(resp->status_msg, "Created");
        strcpy(resp->body, "{\"id\":\"12345\"}");
    }
    
    printf("[HTTP] Response: 201 Created\n");
    return 0;
}
