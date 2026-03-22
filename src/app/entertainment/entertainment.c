#include <stdio.h>
#include <string.h>

#define MAX_MUSICS 30
#define MAX_VIDEOS 20

typedef struct { char title[64]; char artist[64]; int duration; } music_t;
typedef struct { char title[64]; char type[32]; } video_t;

static music_t musics[MAX_MUSICS];
static int music_count = 0;
static video_t videos[MAX_VIDEOS];
static int video_count = 0;

void ent_music_init(void) {
    printf("[Entertainment] Music initialized\n");
    music_t *m = &musics[music_count++];
    strcpy(m->title, "演员"); strcpy(m->artist, "薛之谦"); m->duration = 240;
    m = &musics[music_count++];
    strcpy(m->title, "晴天"); strcpy(m->artist, "周杰伦"); m->duration = 280;
    printf("  Musics: %d\n", music_count);
}
void ent_music_list(void) {
    printf("\n=== Music Playlist (%d) ===\n", music_count);
    for (int i = 0; i < music_count; i++) {
        printf("%d. %s - %s (%d秒)\n", i+1, musics[i].title, musics[i].artist, musics[i].duration);
    }
    printf("===========================\n\n");
}

void ent_video_init(void) {
    printf("[Entertainment] Video initialized\n");
    video_t *v = &videos[video_count++];
    strcpy(v->title, "流浪地球2"); strcpy(v->type, "电影");
    v = &videos[video_count++];
    strcpy(v->title, "狂飙"); strcpy(v->type, "电视剧");
    printf("  Videos: %d\n", video_count);
}
void ent_video_list(void) {
    printf("\n=== Videos (%d) ===\n", video_count);
    for (int i = 0; i < video_count; i++) {
        printf("%d. %s (%s)\n", i+1, videos[i].title, videos[i].type);
    }
    printf("=====================\n\n");
}

void ent_game_init(void) { printf("[Entertainment] Games\n"); printf("  最近玩: 王者荣耀\n"); }
void ent_social_init(void) { printf("[Entertainment] Social\n"); printf("  朋友圈: 3条新动态\n"); }
void ent_travel_init(void) {
    printf("[Entertainment] Travel\n");
    printf("  推荐: 永济-西安3日游\n");
}

void ent_dashboard(void) {
    printf("\n");
    printf("╔═══════════════════════════════════════╗\n");
    printf("║      Entertainment Dashboard          ║\n");
    printf("╠═══════════════════════════════════════╣\n");
    printf("║ 🎵 音乐: 播放中 - 演员              ║\n");
    printf("║ 📺 视频: 流浪地球2                  ║\n");
    printf("║ 🎮 游戏: 王者荣耀                   ║\n");
    printf("║ 📱 社交: 3条新动态                  ║\n");
    printf("║ ✈️ 旅行: 永济-西安                  ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");
}

void ent_test(void) {
    printf("\n=== Entertainment Test ===\n");
    ent_music_init(); ent_music_list();
    ent_video_init(); ent_video_list();
    ent_game_init(); ent_social_init(); ent_travel_init();
    ent_dashboard();
    printf("=====================\n\n");
}
