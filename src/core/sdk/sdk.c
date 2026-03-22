#include <stdio.h>
#include <string.h>

// ===== SDK列表 =====
void sdk_list(void) {
    printf("\n=== SDKs ===\n");
    printf("1. C SDK (libaide.so)\n");
    printf("2. Python SDK (pip install aide)\n");
    printf("3. JavaScript SDK (npm install aide-sdk)\n");
    printf("4. HTTP REST API\n");
    printf("=====================\n\n");
}

// ===== C SDK =====
void sdk_c_init(void) { printf("[SDK] C SDK initialized\n"); }
void sdk_c_example(void) {
    printf("\n=== C SDK Example ===\n");
    printf("#include <aide/aide.h>\n\n");
    printf("int main() {\n");
    printf("    aide_init();\n");
    printf("    char *reply = aide_chat(\"你好\");\n");
    printf("    printf(\"%%s\\n\", reply);\n");
    printf("    return 0;\n");
    printf("}\n");
    printf("====================\n\n");
}
void sdk_c_compile(void) {
    printf("\n=== Compile ===\n");
    printf("gcc -o demo demo.c -laide\n");
    printf("====================\n\n");
}

// ===== Python SDK =====
void sdk_python_init(void) { printf("[SDK] Python SDK initialized\n"); }
void sdk_python_example(void) {
    printf("\n=== Python SDK Example ===\n");
    printf("import aide\n\n");
    printf("aide.init(api_key=\"xxx\")\n");
    printf("reply = aide.chat(\"你好\")\n");
    printf("print(reply)\n");
    printf("====================\n\n");
}
void sdk_python_install(void) {
    printf("\n=== Install ===\n");
    printf("pip install aide-sdk\n");
    printf("====================\n\n");
}

// ===== JavaScript SDK =====
void sdk_js_init(void) { printf("[SDK] JS SDK initialized\n"); }
void sdk_js_example(void) {
    printf("\n=== JavaScript SDK Example ===\n");
    printf("const aide = require('aide-sdk');\n\n");
    printf("const client = new aide.Client({apiKey: 'xxx'});\n");
    printf("const reply = await client.chat('你好');\n");
    printf("console.log(reply);\n");
    printf("====================\n\n");
}

// ===== REST API =====
void sdk_rest_init(void) { printf("[SDK] REST API initialized\n"); }
void sdk_rest_example(void) {
    printf("\n=== REST API ===\n");
    printf("POST /api/v1/chat\n");
    printf("{\n");
    printf("  \"message\": \"你好\",\n");
    printf("  \"model\": \"abab6.5s-chat\"\n");
    printf("}\n");
    printf("\nResponse:\n");
    printf("{\n");
    printf("  \"reply\": \"你好, 有什么可以帮你的?\"\n");
    printf("}\n");
    printf("================\n\n");
}

// ===== API文档 =====
void sdk_docs(void) {
    printf("\n=== API Docs ===\n");
    printf("1. /api/v1/chat - 对话\n");
    printf("2. /api/v1/tts - 语音合成\n");
    printf("3. /api/v1/stt - 语音识别\n");
    printf("4. /api/v1/vision - 视觉识别\n");
    printf("5. /api/v1/device - 设备控制\n");
    printf("=====================\n\n");
}

// ===== 测试 =====
void sdk_test(void) {
    printf("\n=== SDK Test ===\n");
    
    sdk_list();
    sdk_c_init(); sdk_c_example(); sdk_c_compile();
    sdk_python_init(); sdk_python_example(); sdk_python_install();
    sdk_js_init(); sdk_js_example();
    sdk_rest_init(); sdk_rest_example();
    sdk_docs();
    
    printf("==================\n\n");
}
