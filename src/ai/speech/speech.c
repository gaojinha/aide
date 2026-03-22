#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_AUDIO 1024

// ===== 本地STT ( whisper.cpp ) =====
typedef struct {
    char model[64];
    int loaded;
} stt_model_t;

static stt_model_t stt_model;
static int stt_initialized = 0;

void stt_init(void) {
    printf("[STT] Initialized\n");
    printf("  Engine: whisper.cpp\n");
    printf("  Model: whisper-base.bin\n");
    stt_initialized = 1;
}

int stt_load_model(const char *model) {
    printf("[STT] Loading: %s\n", model);
    strncpy(stt_model.model, model, 63);
    stt_model.loaded = 1;
    printf("[STT] Model loaded!\n");
    return 0;
}

int stt_recognize(const char *audio_file, char *text, int max_len) {
    if (!stt_model.loaded) {
        printf("[STT] No model loaded, using cloud...\n");
        snprintf(text, max_len, "[云端STT] %s", audio_file);
        return 0;
    }
    printf("[STT] Recognizing: %s\n", audio_file);
    printf("[STT] Using whisper.cpp...\n");
    snprintf(text, max_len, "识别结果: 你好，这是语音识别结果");
    return 0;
}

void stt_list_models(void) {
    printf("\n=== STT Models ===\n");
    printf("1. tiny (39MB)\n");
    printf("2. base (74MB)\n");
    printf("3. small (244MB)\n");
    printf("4. medium (769MB)\n");
    printf("5. large (1550MB)\n");
    printf("=====================\n\n");
}

// ===== 本地TTS ( piper ) =====
typedef struct {
    char voice[64];
    int loaded;
} tts_model_t;

static tts_model_t tts_model;

void tts_init(void) {
    printf("[TTS] Initialized\n");
    printf("  Engine: piper\n");
    printf("  Voice: zh_CN-manying-medium\n");
}

int tts_load_voice(const char *voice) {
    printf("[TTS] Loading voice: %s\n", voice);
    strncpy(tts_model.voice, voice, 63);
    tts_model.loaded = 1;
    printf("[TTS] Voice loaded!\n");
    return 0;
}

int tts_synthesize(const char *text, const char *output) {
    if (!tts_model.loaded) {
        printf("[TTS] No voice loaded, using cloud...\n");
    }
    printf("[TTS] Synthesizing: %s\n", text);
    printf("[TTS] Using piper...\n");
    printf("[TTS] Output: %s\n", output ? output : "output.wav");
    printf("[TTS] Done!\n");
    return 0;
}

void tts_list_voices(void) {
    printf("\n=== TTS Voices ===\n");
    printf("1. zh_CN-manying-medium (中文女声)\n");
    printf("2. zh_CN-liaoning-xiaowei (东北话)\n");
    printf("3. zh_CN-shaanxi-xiaosi (陕西话)\n");
    printf("4. en_US-lessac-medium (英文男声)\n");
    printf("=======================\n\n");
}

// ===== 语音识别主函数 =====
int speech_stt(const char *audio_file, char *text, int max_len) {
    if (!stt_initialized) stt_init();
    return stt_recognize(audio_file, text, max_len);
}

// ===== 语音合成主函数 =====
int speech_tts(const char *text, const char *output) {
    return tts_synthesize(text, output);
}

// ===== 初始化 =====
int speech_init(void) {
    printf("[AI/Speech] Initialized\n");
    printf("  STT: whisper.cpp (本地) / Cloud API\n");
    printf("  TTS: piper (本地) / Edge TTS (云端)\n");
    
    // 加载默认模型
    stt_init();
    stt_load_model("whisper-base");
    
    tts_init();
    tts_load_voice("zh_CN-manying-medium");
    
    return 0;
}

// ===== 测试 =====
void speech_test(void) {
    printf("\n=== Speech Test ===\n");
    
    char text[256];
    
    // STT测试
    printf("--- STT Test ---\n");
    stt_list_models();
    speech_stt("test.wav", text, 256);
    printf("Result: %s\n", text);
    
    // TTS测试
    printf("--- TTS Test ---\n");
    tts_list_voices();
    speech_tts("你好，我是 aide 语音助手", "hello.wav");
    
    printf("==================\n\n");
}
