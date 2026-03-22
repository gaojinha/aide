#include <stdio.h>

extern int http_get(const char *url, void *resp);
extern int http_post(const char *url, const char *data, void *resp);

int main() {
    printf("Testing HTTP...\n");
    http_get("http://example.com", NULL);
    http_post("http://example.com", "test", NULL);
    printf("Done\n");
    return 0;
}
