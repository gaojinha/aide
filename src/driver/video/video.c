#include <stdio.h>
#include <string.h>

#define MAX_VIDEOS 30

// 播放状态
typedef enum {
    VIDEO_STOP,
    VIDEO_PLAY,
    VIDEO_PAUSE,
    VIDEO_BUFFERING
} video_status_t;

// 视频格式
typedef enum {
    FMT_MP4,
    FMT_MKV,
    FMT_AVI,
    FMT_FLV,
    FMT_WEBM
} video_format_t;

// 视频信息
typedef struct {
    char title[64];
    char path[128];
    int duration;      // 秒
    int width;
    int height;
    video_format_t format;
    int size;          // MB
} video_t;

static video_t videos[MAX_VIDEOS];
static int video_count = 0;
static int current_video = -1;
static video_status_t video_status = VIDEO_STOP;
static int position = 0;  // 秒

// 初始化
int video_init(void) {
    printf("[Video] Initialized\n");
    printf("  Decoder: FFmpeg\n");
    printf("  Output: HDMI\n");
    return 0;
}

// 添加视频
int video_add(const char *title, const char *path, int duration, int w, int h, int size_mb) {
    if (video_count >= MAX_VIDEOS) return -1;
    
    video_t *v = &videos[video_count];
    strncpy(v->title, title, 63);
    strncpy(v->path, path, 127);
    v->duration = duration;
    v->width = w;
    v->height = h;
    v->size = size_mb;
    video_count++;
    
    return 0;
}

// 播放
int video_play(int video_id) {
    if (video_id < 0 || video_id >= video_count) return -1;
    
    current_video = video_id;
    video_status = VIDEO_PLAY;
    position = 0;
    
    printf("[Video] Playing: %s\n", videos[video_id].title);
    return 0;
}

// 暂停
int video_pause(void) {
    video_status = VIDEO_PAUSE;
    printf("[Video] Paused at %d:%02d\n", position/60, position%60);
    return 0;
}

// 继续
int video_resume(void) {
    video_status = VIDEO_PLAY;
    printf("[Video] Resumed\n");
    return 0;
}

// 停止
int video_stop(void) {
    video_status = VIDEO_STOP;
    position = 0;
    printf("[Video] Stopped\n");
    return 0;
}

// 跳转
int video_seek(int seconds) {
    if (current_video < 0) return -1;
    if (seconds < 0) seconds = 0;
    if (seconds > videos[current_video].duration) seconds = videos[current_video].duration;
    
    position = seconds;
    printf("[Video] Seek to %d:%02d\n", position/60, position%60);
    return 0;
}

// 快进/快退
int video_forward(int seconds) {
    return video_seek(position + seconds);
}

int video_rewind(int seconds) {
    return video_seek(position - seconds);
}

// 设置音量
int video_set_volume(int vol) {
    printf("[Video] Volume: %d%%\n", vol);
    return 0;
}

// 全屏
int video_fullscreen(int enable) {
    printf("[Video] Fullscreen: %s\n", enable ? "ON" : "OFF");
    return 0;
}

// 列出视频
void video_list(void) {
    printf("\n=== Videos (%d) ===\n", video_count);
    printf("Status: %s\n", video_status == VIDEO_PLAY ? "Playing" : 
                         video_status == VIDEO_PAUSE ? "Paused" : "Stopped");
    
    for (int i = 0; i < video_count; i++) {
        printf("%d. %s (%dx%d, %dMB) %d:%02d%s\n",
            i + 1,
            videos[i].title,
            videos[i].width,
            videos[i].height,
            videos[i].size,
            videos[i].duration / 60,
            videos[i].duration % 60,
            i == current_video ? " ◄──" : "");
    }
    printf("====================\n\n");
}

// 测试
void video_test(void) {
    printf("\n=== Video Test ===\n");
    
    // 添加测试视频
    video_add("流浪地球", "/movies/wandering.mp4", 7200, 1920, 1080, 2500);
    video_add("满江红", "/movies/manjianghong.mp4", 9000, 1920, 1080, 3200);
    video_add("狂飙01", "/tv/kuanbiao_01.mp4", 2700, 1920, 1080, 800);
    
    video_list();
    
    video_play(0);
    video_pause();
    video_resume();
    video_forward(30);
    video_rewind(10);
    video_seek(1200);
    video_stop();
    
    video_fullscreen(1);
    video_fullscreen(0);
    
    printf("==================\n\n");
}
