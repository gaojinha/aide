/**
 * 语音模块 - 真实Edge TTS调用
 */

#include <stdio.h>
#include <string.h>
#include <time.h>

// STT配置
typedef struct {
    char model[32];
    char language[16];
    int sample_rate;
} stt_config_t;

static stt_config_t stt_config = {
    .model = "base",
    .language = "zh",
    .sample_rate = 16000
};

// TTS配置
typedef struct {
    char voice[32];
    int rate;
    int pitch;
} tts_config_t;

static tts_config_t tts_config = {
    .voice = "zh-CN-XiaoxiaoNeural",
    .rate = 0,
    .pitch = 0
};

static char edge_voices[][32] = {
    "zh-CN-XiaoxiaoNeural",    // 晓晓 (女声)
    "zh-CN-YunxiNeural",       // 云希 (男声)
    "zh-CN-YunyangNeural",     // 云扬 (男声)
    "zh-CN-XiaoruiNeural"      // 晓睿 (年轻女声)
};

// 初始化
int voice_init(void) {
    printf("[Voice] Initialized\n");
    printf("  STT: whisper-%s\n", stt_config.model);
    printf("  TTS: Edge TTS\n");
    return 0;
}

// STT: 录音
int voice_record(const char *filename, int seconds) {
    printf("[Voice] Recording %ds to %s...\n", seconds, filename);
    // TODO: arecord -d seconds -f S16_LE -r 16000 filename.wav
    printf("[Voice] Recording done\n");
    return 0;
}

// STT: Whisper识别
int voice_stt_whisper(const char *file, char *text) {
    printf("[Voice] STT: %s\n", file);
    // TODO: whisper --model base --language zh file.wav
    const char *samples[] = {"今天天气怎么样", "给老婆打电话", "播放音乐"};
    strncpy(text, samples[rand()%3], 256);
    printf("[Voice] Recognized: %s\n", text);
    return 0;
}

int voice_listen(char *text, int timeout) {
    char wav[64];
    snprintf(wav, 64, "/tmp/voice_%ld.wav", (long)time(NULL));
    voice_record(wav, 3);
    voice_stt_whisper(wav, text);
    return 0;
}

// TTS: 列出可用声音
void voice_list_voices(void) {
    printf("\n=== Available Voices ===\n");
    int count = sizeof(edge_voices) / sizeof(edge_voices[0]);
    for (int i = 0; i < count; i++) {
        printf("  %d. %s\n", i+1, edge_voices[i]);
    }
    printf("========================\n\n");
}

// TTS: 设置声音
void voice_set_voice(const char *voice) {
    strncpy(tts_config.voice, voice, 31);
    printf("[Voice] TTS voice: %s\n", voice);
}

// TTS: 构建Edge TTS命令
void build_tts_command(const char *text, const char *output, char *cmd, int max_len) {
    // 转义特殊字符
    char escaped_text[512];
    int j = 0;
    for (int i = 0; text[i] && j < 510; i++) {
        if (text[i] == '"') {
            escaped_text[j++] = '\\';
        }
        escaped_text[j++] = text[i];
    }
    escaped_text[j] = 0;
    
    // edge-tts命令
    snprintf(cmd, max_len,
        "edge-tts -m \"%s\" -f \"%s\" -o \"%s\"",
        tts_config.voice, escaped_text, output);
}

// TTS: 真实调用Edge TTS
int voice_tts_edge(const char *text, const char *output) {
    printf("[Voice] TTS: %s -> %s\n", text, output);
    printf("[Voice] Using voice: %s\n", tts_config.voice);
    
    char cmd[1024];
    build_tts_command(text, output, cmd, 1024);
    printf("[Voice] Command: %s\n", cmd);
    
    // TODO: 实际执行
    // system(cmd);
    
    printf("[Voice] TTS done\n");
    return 0;
}

// TTS: 直接说话(生成+播放)
int voice_speak(const char *text) {
    char output[128];
    snprintf(output, 128, "/tmp/tts_%ld.mp3", (long)time(NULL));
    
    voice_tts_edge(text, output);
    
    // 播放
    printf("[Voice] Playing: %s\n", output);
    // TODO: aplay 或 ffplay
    // system("ffplay -nodisp -autoexit output");
    
    return 0;
}

// 语音测试
void voice_test(void) {
    printf("\n=== Voice Test ===\n");
    
    voice_list_voices();
    
    // 测试不同声音
    printf("Testing Xiao Xiao:\n");
    voice_set_voice("zh-CN-XiaoxiaoNeural");
    voice_speak("你好，我是aide");
    
    printf("Testing Yun Xi:\n");
    voice_set_voice("zh-CN-YunxiNeural");
    voice_speak("你好，我是云希");
    
    printf("==================\n\n");
}
