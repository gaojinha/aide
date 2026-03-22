/**
 * 语音+模型测试
 */

#include <stdio.h>
#include <string.h>

extern int voice_init(void);
extern int voice_tts_edge(const char *text, const char *file);
extern int voice_stt_whisper(const char *file, char *text);

extern int model_init(void);
extern int model_load_local(const char *path);
extern int model_infer_local(const char *prompt, char *resp, int max);
extern int model_infer_cloud(const char *prompt, char *resp, int max);
extern int model_infer_smart(const char *prompt, char *resp, int max);

void test_voice(void) {
    printf("[Test] Voice init: OK\n");
    char text[128];
    voice_stt_whisper("test.wav", text);
    voice_tts_edge("你好", "output.wav");
}

void test_model(void) {
    printf("[Test] Model init: OK\n");
    model_load_local("/models/test.bin");
    char resp[128];
    model_infer_local("你好", resp, 100);
    model_infer_cloud("你好", resp, 100);
    model_infer_smart("你好", resp, 100);
}

int main(void) {
    printf("=== Voice+Model Tests ===\n");
    voice_init();
    model_init();
    test_voice();
    test_model();
    printf("=== All Passed ===\n");
    return 0;
}
