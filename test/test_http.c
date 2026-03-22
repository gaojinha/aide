#include <stdio.h>
#include "../src/core/protocol/http.c"

int test_http_get(void) {
    http_response_t resp;
    int ret = http_get("http://test.com", &resp);
    TEST_ASSERT(ret == 0, "http_get");
    TEST_ASSERT(resp.status_code == 200, "status 200");
    
    TEST_PASS("http_get");
    return 0;
}

int test_http_post(void) {
    http_response_t resp;
    int ret = http_post("http://test.com", "{\"test\":1}", &resp);
    TEST_ASSERT(ret == 0, "http_post");
    TEST_ASSERT(resp.status_code == 201, "status 201");
    
    TEST_PASS("http_post");
    return 0;
}
