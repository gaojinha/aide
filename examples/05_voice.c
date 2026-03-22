/**
 * 示例5: 语音使用
 */

#include <stdio.h>
#include "voice.h"

int main(void) {
    // 初始化语音
    voice_init();
    
    // 语音识别
    char text[256];
    voice_stt_whisper("recording.wav", text);
    printf("识别结果: %s\n", text);
    
    // 语音合成
    voice_tts_edge("你好，我是AI助理", "hello.mp3");
    printf("语音合成完成\n");
    
    return 0;
}
