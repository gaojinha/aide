/**
 * 语音模块
 */

#include <stdio.h>

int speech_init(void) {
    printf("[AI/Speech] Initialized\n");
    return 0;
}

int speech_stt(const void *audio, char *text) {
    // TODO: 语音转文字
    return 0;
}

int speech_tts(const char *text, void *audio) {
    // TODO: 文字转语音
    return 0;
}
