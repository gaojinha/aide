#include <stdio.h>
#include <time.h>
#include <string.h>

#define MAX_FILES 100

// 文件类型
typedef enum {
    TYPE_FILE,
    TYPE_DIR,
    TYPE_LINK
} file_type_t;

// 文件信息
typedef struct {
    char name[64];
    char path[128];
    file_type_t type;
    int size;       // KB
    time_t mtime;
} file_info_t;

static file_info_t files[MAX_FILES];
static int file_count = 0;

// 初始化
int file_manager_init(void) {
    printf("[FileManager] Initialized\n");
    return 0;
}

// 列出目录
int file_list(const char *path) {
    printf("[FileManager] Listing: %s\n", path);
    
    file_count = 0;
    
    // 模拟文件
    file_info_t *f = &files[file_count++];
    strcpy(f->name, "Documents");
    strcpy(f->path, "/sdcard/Documents");
    f->type = TYPE_DIR;
    f->size = 0;
    
    f = &files[file_count++];
    strcpy(f->name, "Pictures");
    strcpy(f->path, "/sdcard/Pictures");
    f->type = TYPE_DIR;
    f->size = 0;
    
    f = &files[file_count++];
    strcpy(f->name, "music.mp3");
    strcpy(f->path, "/sdcard/music.mp3");
    f->type = TYPE_FILE;
    f->size = 5120;
    
    f = &files[file_count++];
    strcpy(f->name, "video.mp4");
    strcpy(f->path, "/sdcard/video.mp4");
    f->type = TYPE_FILE;
    f->size = 204800;
    
    printf("[FileManager] Found %d items\n", file_count);
    return file_count;
}

// 复制
int file_copy(const char *src, const char *dst) {
    printf("[FileManager] Copying: %s -> %s\n", src, dst);
    return 0;
}

// 移动
int file_move(const char *src, const char *dst) {
    printf("[FileManager] Moving: %s -> %s\n", src, dst);
    return 0;
}

// 删除
int file_delete(const char *path) {
    printf("[FileManager] Deleting: %s\n", path);
    return 0;
}

// 创建目录
int file_mkdir(const char *path) {
    printf("[FileManager] mkdir: %s\n", path);
    return 0;
}

// 重命名
int file_rename(const char *old, const char *new) {
    printf("[FileManager] Renaming: %s -> %s\n", old, new);
    return 0;
}

// 获取空间
void file_get_space(const char *path, long *total, long *used) {
    *total = 32L * 1024 * 1024;  // 32GB
    *used = 12L * 1024 * 1024;   // 12GB
    printf("[FileManager] Space: %ld/%ld KB\n", *used, *total);
}

// 列出文件
void file_list_show(void) {
    printf("\n=== Files (%d) ===\n", file_count);
    for (int i = 0; i < file_count; i++) {
        printf("%d. %s %s %dKB\n",
            i+1,
            files[i].type == TYPE_DIR ? "[DIR]" : "[FILE]",
            files[i].name,
            files[i].size);
    }
    
    long total, used;
    file_get_space("/sdcard", &total, &used);
    printf("Space: %ld/%ld KB (%.1f%% used)\n", used, total, 100.0*used/total);
    printf("=====================\n\n");
}

// 测试
void file_manager_test(void) {
    printf("\n=== FileManager Test ===\n");
    
    file_list("/sdcard");
    file_list_show();
    
    file_copy("/sdcard/test.txt", "/sdcard/Documents/test.txt");
    file_move("/sdcard/old.txt", "/sdcard/new.txt");
    file_delete("/sdcard/temp.txt");
    file_mkdir("/sdcard/NewFolder");
    
    printf("==================\n\n");
}
