#include <stdio.h>
#include <string.h>

#define MAX_CODES 30

// 遥控按键
typedef enum {
    KEY_POWER,
    KEY_VOL_UP,
    KEY_VOL_DOWN,
    KEY_CH_UP,
    KEY_CH_DOWN,
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_OK,
    KEY_0, KEY_1, KEY_2, KEY_3, KEY_4,
    KEY_5, KEY_6, KEY_7, KEY_8, KEY_9,
    KEY_MUTE,
    KEY_MENU,
    KEY_BACK,
    KEY_HOME
} ir_key_t;

// 红外码
typedef struct {
    ir_key_t key;
    char name[16];
    unsigned int code;
} ir_code_t;

static ir_code_t codes[MAX_CODES];
static int code_count = 0;

// 初始化
int ir_init(void) {
    printf("[IR] Initialized\n");
    printf("  Receiver: GPIO\n");
    
    // 添加遥控码
    ir_add_code(KEY_POWER, "POWER", 0x00FF00FF);
    ir_add_code(KEY_VOL_UP, "VOL+", 0x00FFE01F);
    ir_add_code(KEY_VOL_DOWN, "VOL-", 0x00FFD02F);
    ir_add_code(KEY_CH_UP, "CH+", 0x00FC03F);
    ir_add_code(KEY_CH_DOWN, "CH-", 0x00FB04F);
    ir_add_code(KEY_UP, "UP", 0x00F708F);
    ir_add_code(KEY_DOWN, "DOWN", 0x00F00F);
    ir_add_code(KEY_LEFT, "LEFT", 0x00EF10EF);
    ir_add_code(KEY_RIGHT, "RIGHT", 0x00EE11EF);
    ir_add_code(KEY_OK, "OK", 0x00ED12ED);
    ir_add_code(KEY_1, "1", 0x00EE11E);
    ir_add_code(KEY_2, "2", 0x00EE11E);
    
    printf("  Codes: %d\n", code_count);
    return 0;
}

// 添加码
int ir_add_code(ir_key_t key, const char *name, unsigned int code) {
    if (code_count >= MAX_CODES) return -1;
    
    codes[code_count].key = key;
    strncpy(codes[code_count].name, name, 15);
    codes[code_count].code = code;
    code_count++;
    
    return 0;
}

// 解码
int ir_decode(unsigned int raw_code) {
    for (int i = 0; i < code_count; i++) {
        if (codes[i].code == raw_code) {
            printf("[IR] Key: %s (0x%08X)\n", codes[i].name, raw_code);
            return codes[i].key;
        }
    }
    printf("[IR] Unknown: 0x%08X\n", raw_code);
    return -1;
}

// 发送
int ir_send(ir_key_t key) {
    for (int i = 0; i < code_count; i++) {
        if (codes[i].key == key) {
            printf("[IR] Sending: %s (0x%08X)\n", codes[i].name, codes[i].code);
            return 0;
        }
    }
    return -1;
}

// 列出码
void ir_list(void) {
    printf("\n=== IR Codes (%d) ===\n", code_count);
    for (int i = 0; i < code_count; i++) {
        printf("%d. %s: 0x%08X\n", i+1, codes[i].name, codes[i].code);
    }
    printf("=====================\n\n");
}

// 测试
void ir_test(void) {
    printf("\n=== IR Test ===\n");
    
    ir_list();
    
    printf("Decoding test:\n");
    ir_decode(0x00FF00FF);  // POWER
    ir_decode(0x00FFE01F);  // VOL+
    ir_decode(0x00ED12ED);  // OK
    
    printf("\nSending test:\n");
    ir_send(KEY_POWER);
    ir_send(KEY_VOL_UP);
    ir_send(KEY_OK);
    
    printf("==================\n\n");
}
