#include <stdio.h>
#include <string.h>

#define MAX_TRACKS 50

// 播放状态
typedef enum {
    PLAY_STOP,
    PLAY_PLAY,
    PLAY_PAUSE
} play_status_t;

// 音频格式
typedef enum {
    FMT_MP3,
    FMT_WAV,
    FMT_FLAC,
    FMT_AAC,
    FMT_OGG
} audio_format_t;

// 曲目
typedef struct {
    char title[64];
    char artist[32];
    char album[32];
    int duration;     // 秒
    audio_format_t format;
} track_t;

static track_t tracks[MAX_TRACKS];
static int track_count = 0;
static int current_track = -1;
static play_status_t play_status = PLAY_STOP;
static int volume = 70;

// 初始化
int audio_init(void) {
    printf("[Audio] Initialized\n");
    printf("  Codec: ALSA\n");
    printf("  Output: Speaker/Headphone\n");
    return 0;
}

// 设置音量
int audio_set_volume(int vol) {
    if (vol < 0) vol = 0;
    if (vol > 100) vol = 100;
    volume = vol;
    printf("[Audio] Volume: %d%%\n", volume);
    return 0;
}

// 获取音量
int audio_get_volume(void) {
    return volume;
}

// 添加曲目
int audio_add_track(const char *title, const char *artist, int duration) {
    if (track_count >= MAX_TRACKS) return -1;
    
    track_t *t = &tracks[track_count];
    strncpy(t->title, title, 63);
    strncpy(t->artist, artist, 31);
    t->duration = duration;
    t->format = FMT_MP3;
    track_count++;
    
    return 0;
}

// 播放
int audio_play(int track_id) {
    if (track_id < 0 || track_id >= track_count) return -1;
    
    current_track = track_id;
    play_status = PLAY_PLAY;
    printf("[Audio] Playing: %s - %s\n", 
        tracks[track_id].artist, tracks[track_id].title);
    return 0;
}

// 暂停
int audio_pause(void) {
    play_status = PLAY_PAUSE;
    printf("[Audio] Paused\n");
    return 0;
}

// 继续
int audio_resume(void) {
    play_status = PLAY_PLAY;
    printf("[Audio] Resumed\n");
    return 0;
}

// 停止
int audio_stop(void) {
    play_status = PLAY_STOP;
    current_track = -1;
    printf("[Audio] Stopped\n");
    return 0;
}

// 上一首
int audio_prev(void) {
    if (current_track > 0) {
        current_track--;
        audio_play(current_track);
    }
    return current_track;
}

// 下一首
int audio_next(void) {
    if (current_track < track_count - 1) {
        current_track++;
        audio_play(current_track);
    }
    return current_track;
}

// 录音
int audio_record(const char *file, int seconds) {
    printf("[Audio] Recording to %s (%ds)...\n", file, seconds);
    printf("[Audio] Recording done\n");
    return 0;
}

// 列出曲目
void audio_list(void) {
    printf("\n=== Audio Tracks (%d) ===\n", track_count);
    printf("Volume: %d%%\n", volume);
    printf("Status: %s\n", play_status == PLAY_PLAY ? "Playing" : 
                             play_status == PLAY_PAUSE ? "Paused" : "Stopped");
    
    for (int i = 0; i < track_count; i++) {
        printf("%d. %s - %s (%d:%02d)%s\n",
            i + 1,
            tracks[i].artist,
            tracks[i].title,
            tracks[i].duration / 60,
            tracks[i].duration % 60,
            i == current_track ? " ◄──" : "");
    }
    printf("=========================\n\n");
}

// 测试
void audio_test(void) {
    printf("\n=== Audio Test ===\n");
    
    // 添加测试曲目
    audio_add_track("演员", "薛之谦", 245);
    audio_add_track("成都", "赵雷", 330);
    audio_add_track("追光者", "岑宁儿", 210);
    audio_add_track("空空如也", "任然", 248);
    
    audio_list();
    
    audio_set_volume(80);
    audio_play(0);
    audio_pause();
    audio_resume();
    audio_next();
    audio_prev();
    audio_stop();
    
    printf("==================\n\n");
}
