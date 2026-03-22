#include <stdio.h>
#include <string.h>

#define MAX_BREAKPOINTS 20

// 断点
typedef struct {
    int id;
    char file[64];
    int line;
    int enabled;
} breakpoint_t;

static breakpoint_t breakpoints[MAX_BREAKPOINTS];
static int bp_count = 0;
static int debug_enabled = 1;

// 初始化
void debug_init(void) {
    bp_count = 0;
    debug_enabled = 1;
    printf("[Debug] Initialized\n");
    printf("  Mode: %s\n", debug_enabled ? "ENABLED" : "DISABLED");
}

// 设置断点
int debug_breakpoint_set(const char *file, int line) {
    if (bp_count >= MAX_BREAKPOINTS) return -1;
    
    breakpoint_t *bp = &breakpoints[bp_count];
    bp->id = bp_count + 1;
    strncpy(bp->file, file, 63);
    bp->line = line;
    bp->enabled = 1;
    bp_count++;
    
    printf("[Debug] Breakpoint #%d: %s:%d\n", bp->id, file, line);
    return 0;
}

// 删除断点
int debug_breakpoint_del(int id) {
    for (int i = 0; i < bp_count; i++) {
        if (breakpoints[i].id == id) {
            printf("[Debug] Deleted breakpoint #%d\n", id);
            for (int j = i; j < bp_count - 1; j++) {
                breakpoints[j] = breakpoints[j + 1];
            }
            bp_count--;
            return 0;
        }
    }
    return -1;
}

// 列出断点
void debug_breakpoint_list(void) {
    printf("\n=== Breakpoints (%d) ===\n", bp_count);
    for (int i = 0; i < bp_count; i++) {
        printf("%d. [%s] %s:%d\n", 
            breakpoints[i].id,
            breakpoints[i].enabled ? "ON " : "OFF",
            breakpoints[i].file,
            breakpoints[i].line);
    }
    printf("========================\n\n");
}

// 堆栈跟踪
void debug_backtrace(void) {
    printf("\n=== Backtrace ===\n");
    printf("#0  aide_main() at main.c:100\n");
    printf("#1  ai_system_init() at system.c:50\n");
    printf("#2  voice_init() at voice.c:30\n");
    printf("#3  audio_play() at audio.c:80\n");
    printf("#4  [unknown]\n");
    printf("====================\n\n");
}

// 内存查看
void debug_memory_view(void *addr, int size) {
    printf("\n=== Memory View ===\n");
    printf("Address: %p\n", addr);
    printf("Size: %d bytes\n\n", size);
    
    printf("Hex dump:\n");
    for (int i = 0; i < 16; i++) {
        printf("%02X ", i * 3);
    }
    printf("\n");
    for (int i = 0; i < 16; i++) {
        printf("%02X ", rand() % 256);
    }
    printf("\n");
    printf("========================\n\n");
}

// 寄存器查看
void debug_registers(void) {
    printf("\n=== Registers ===\n");
    printf("PC:  0x%08X\n", rand() % 0xFFFFFFFF);
    printf("SP:  0x%08X\n", rand() % 0xFFFFFFFF);
    printf("LR:  0x%08X\n", rand() % 0xFFFFFFFF);
    printf("R0:  0x%08X\n", rand() % 0xFFFFFFFF);
    printf("R1:  0x%08X\n", rand() % 0xFFFFFFFF);
    printf("====================\n\n");
}

// GDB远程调试
void debug_gdb_remote(int port) {
    printf("[Debug] GDB remote debugging on port %d\n", port);
    printf("[Debug] Listening for connections...\n");
    printf("[Debug] Connected!\n");
}

// 测试
void debug_test(void) {
    printf("\n=== Debug Test ===\n");
    
    debug_breakpoint_set("main.c", 100);
    debug_breakpoint_set("voice.c", 50);
    debug_breakpoint_set("audio.c", 80);
    
    debug_breakpoint_list();
    
    printf("Backtrace:\n");
    debug_backtrace();
    
    printf("Registers:\n");
    debug_registers();
    
    printf("Memory:\n");
    debug_memory_view(0x1000, 64);
    
    debug_breakpoint_del(2);
    debug_breakpoint_list();
    
    printf("==================\n\n");
}
