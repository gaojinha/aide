#include <stdio.h>
#include <string.h>

typedef enum {
    ERR_OK = 0,
    ERR_INVALID_PARAM = 1,
    ERR_NULL_POINTER = 2,
    ERR_OUT_OF_MEMORY = 3,
    ERR_TIMEOUT = 4,
    ERR_NOT_SUPPORTED = 5,
    ERR_NOT_FOUND = 6,
    ERR_ALREADY_EXISTS = 7,
    ERR_PERMISSION_DENIED = 8,
    ERR_NET_DISCONNECTED = 100,
    ERR_NET_TIMEOUT = 101,
    ERR_NET_UNREACHABLE = 102,
    ERR_HTTP_ERROR = 103,
    ERR_WEBSOCKET_ERROR = 104,
    ERR_STORAGE_FULL = 200,
    ERR_STORAGE_READ = 201,
    ERR_STORAGE_WRITE = 202,
    ERR_STORAGE_CORRUPT = 203,
    ERR_AUTH_FAILED = 300,
    ERR_AUTH_TOKEN_EXPIRED = 301,
    ERR_AUTH_LOCKED = 302,
    ERR_HW_NOT_FOUND = 400,
    ERR_HW_INIT_FAILED = 401,
    ERR_HW_NOT_READY = 402,
    ERR_HW_BUSY = 403,
    ERR_MODULE_NOT_INIT = 500,
    ERR_MODULE_BUSY = 501,
    ERR_SYSTEM = 900,
    ERR_UNKNOWN = 999
} error_code_t;

static const char* error_strings[1000] = {0};

void error_strings_init(void) {
    error_strings[0] = "OK";
    error_strings[1] = "Invalid parameter";
    error_strings[2] = "Null pointer";
    error_strings[3] = "Out of memory";
    error_strings[4] = "Timeout";
    error_strings[5] = "Not supported";
    error_strings[6] = "Not found";
    error_strings[7] = "Already exists";
    error_strings[8] = "Permission denied";
    error_strings[100] = "Network disconnected";
    error_strings[101] = "Network timeout";
    error_strings[102] = "Network unreachable";
    error_strings[103] = "HTTP error";
    error_strings[104] = "WebSocket error";
    error_strings[200] = "Storage full";
    error_strings[201] = "Storage read error";
    error_strings[202] = "Storage write error";
    error_strings[203] = "Storage corrupted";
    error_strings[300] = "Authentication failed";
    error_strings[301] = "Token expired";
    error_strings[302] = "Account locked";
    error_strings[400] = "Hardware not found";
    error_strings[401] = "Hardware init failed";
    error_strings[402] = "Hardware not ready";
    error_strings[403] = "Hardware busy";
    error_strings[500] = "Module not initialized";
    error_strings[501] = "Module busy";
    error_strings[900] = "System error";
    error_strings[999] = "Unknown error";
}

const char* error_string(error_code_t err) {
    if (error_strings[0] == NULL) error_strings_init();
    if (err >= 0 && err < 1000 && error_strings[err])
        return error_strings[err];
    return "Unknown error";
}

void error_print(const char *module, error_code_t err, const char *extra) {
    printf("[ERROR] %s: %s (%d)", module, error_string(err), err);
    if (extra) printf(" - %s", extra);
    printf("\n");
}

int error_is_ok(error_code_t err) { return err == ERR_OK; }

void error_test(void) {
    printf("\n=== Error Test ===\n");
    error_print("WiFi", ERR_NET_DISCONNECTED, NULL);
    error_print("Storage", ERR_STORAGE_FULL, "No space");
    error_print("Auth", ERR_AUTH_FAILED, "Wrong password");
    error_print("Hardware", ERR_HW_INIT_FAILED, NULL);
    printf("\nERR_TIMEOUT: %s\n", error_string(ERR_TIMEOUT));
    printf("Is ERR_OK? %s\n\n", error_is_ok(ERR_OK) ? "YES" : "NO");
}
