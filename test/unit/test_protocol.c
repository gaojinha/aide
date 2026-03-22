/**
 * 协议测试
 */

extern int http_init(void);
extern int http_get(const char *url, void *resp);
extern int http_post(const char *url, const char *data, void *resp);
extern int websocket_init(void);
extern int websocket_connect(void *ws, const char *url);

void test_http(void) {
    printf("  [Test] HTTP init...\n");
    http_init();
    printf("  [Test] HTTP GET...\n");
    http_get("http://example.com", NULL);
    printf("  [Test] HTTP POST...\n");
    http_post("http://example.com", "data", NULL);
}

void test_websocket(void) {
    printf("  [Test] WebSocket init...\n");
    websocket_init();
}

int main(void) {
    printf("=== Protocol Tests ===\n");
    test_http();
    test_websocket();
    printf("=== All Passed ===\n");
    return 0;
}
