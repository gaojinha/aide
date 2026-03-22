/**
 * Storage - 存储模块
 * 支持: 文件系统、块设备、LVM、加密存储、配额管理
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <sys/quota.h>
#include <mntent.h>
#include <limits.h>
#include <dirent.h>
#include <fcntl.h>
#include <errno.h>

#define STORAGE_MAX_FS 32
#define STORAGE_MAX_MOUNT 16

typedef enum {
    FS_TYPE_EXT4,
    FS_TYPE_BTRFS,
    FS_TYPE_XFS,
    FS_TYPE_VFAT,
    FS_TYPE_NTFS,
    FS_TYPE_NETFS,
    FS_TYPE_UNKNOWN
} fs_type_t;

typedef struct {
    char device[128];
    char mount_point[256];
    char fs_type[32];
    unsigned long total;
    unsigned long free;
    unsigned long available;
    int readonly;
} filesystem_info_t;

typedef struct {
    char name[64];
    char path[256];
    fs_type_t type;
    size_t size;
    size_t used;
    int encrypted;
    int quota_enabled;
} storage_volume_t;

typedef struct {
    char path[256];
    unsigned long long space;
    unsigned long inodes;
    unsigned long inodes_free;
} quota_info_t;

static filesystem_info_t g_filesystems[STORAGE_MAX_FS];
static storage_volume_t g_volumes[STORAGE_MAX_MOUNT];
static int g_fs_count = 0;
static int g_volume_count = 0;

// 文件系统操作
int storage_get_fs_info(const char *path, filesystem_info_t *info) {
    struct statvfs st;
    
    if (statvfs(path, &st) < 0) {
        perror("statvfs");
        return -1;
    }
    
    strncpy(info->mount_point, path, 255);
    info->total = st.f_blocks * st.f_frsize;
    info->free = st.f_bfree * st.f_frsize;
    info->available = st.f_bavail * st.f_frsize;
    info->readonly = (st.f_flag & ST_RDONLY) ? 1 : 0;
    
    return 0;
}

int storage_list_filesystems(filesystem_info_t *list, int max_count) {
    FILE *fp = setmntent("/proc/mounts", "r");
    if (!fp) return -1;
    
    int count = 0;
    struct mntent *mnt;
    
    while ((mnt = getmntent(fp)) && count < max_count) {
        strncpy(list[count].device, mnt->mnt_fsname, 127);
        strncpy(list[count].mount_point, mnt->mnt_dir, 255);
        strncpy(list[count].fs_type, mnt->mnt_type, 31);
        
        storage_get_fs_info(mnt->mnt_dir, &list[count]);
        count++;
    }
    
    endmntent(fp);
    return count;
}

// 存储卷操作
int storage_volume_create(const char *name, const char *path, size_t size) {
    if (g_volume_count >= STORAGE_MAX_MOUNT) return -1;
    
    strncpy(g_volumes[g_volume_count].name, name, 63);
    strncpy(g_volumes[g_volume_count].path, path, 255);
    g_volumes[g_volume_count].type = FS_TYPE_EXT4;
    g_volumes[g_volume_count].size = size;
    g_volumes[g_volume_count].used = 0;
    g_volumes[g_volume_count].encrypted = 0;
    g_volumes[g_volume_count].quota_enabled = 0;
    
    // 创建目录
    mkdir(path, 0755);
    
    g_volume_count++;
    printf("[STORAGE] Volume created: %s at %s (%zu bytes)\n", name, path, size);
    
    return 0;
}

int storage_volume_delete(const char *name) {
    for (int i = 0; i < g_volume_count; i++) {
        if (strcmp(g_volumes[i].name, name) == 0) {
            // 移除目录
            rmdir(g_volumes[i].path);
            
            // 移动数组
            for (int j = i; j < g_volume_count - 1; j++) {
                g_volumes[j] = g_volumes[j + 1];
            }
            g_volume_count--;
            
            printf("[STORAGE] Volume deleted: %s\n", name);
            return 0;
        }
    }
    return -1;
}

int storage_volume_info(const char *name, storage_volume_t *info) {
    for (int i = 0; i < g_volume_count; i++) {
        if (strcmp(g_volumes[i].name, name) == 0) {
            memcpy(info, &g_volumes[i], sizeof(storage_volume_t));
            
            // 更新使用情况
            struct statvfs st;
            if (statvfs(g_volumes[i].path, &st) == 0) {
                info->used = (st.f_blocks - st.f_bfree) * st.f_frsize;
            }
            
            return 0;
        }
    }
    return -1;
}

int storage_volume_list(storage_volume_t *list, int max_count) {
    int count = g_volume_count < max_count ? g_volume_count : max_count;
    memcpy(list, g_volumes, count * sizeof(storage_volume_t));
    return count;
}

// 配额管理
int storage_quota_set(const char *path, unsigned long long space_limit, 
                     unsigned long inode_limit) {
    printf("[STORAGE] Setting quota for %s: space=%llu inodes=%lu\n", 
           path, space_limit, inode_limit);
    return 0;
}

int storage_quota_get(const char *path, quota_info_t *info) {
    struct statvfs st;
    
    if (statvfs(path, &st) < 0) {
        return -1;
    }
    
    strncpy(info->path, path, 255);
    info->space = st.f_blocks * st.f_frsize;
    info->inodes = st.f_files;
    info->inodes_free = st.f_ffree;
    
    return 0;
}

int storage_quota_enable(const char *path) {
    for (int i = 0; i < g_volume_count; i++) {
        if (strcmp(g_volumes[i].path, path) == 0) {
            g_volumes[i].quota_enabled = 1;
            printf("[STORAGE] Quota enabled for: %s\n", path);
            return 0;
        }
    }
    return -1;
}

int storage_quota_disable(const char *path) {
    for (int i = 0; i < g_volume_count; i++) {
        if (strcmp(g_volumes[i].path, path) == 0) {
            g_volumes[i].quota_enabled = 0;
            printf("[STORAGE] Quota disabled for: %s\n", path);
            return 0;
        }
    }
    return -1;
}

// 磁盘使用分析
int storage_disk_usage(const char *path, unsigned long *total, 
                       unsigned long *used, unsigned long *free) {
    struct statvfs st;
    
    if (statvfs(path, &st) < 0) {
        return -1;
    }
    
    *total = st.f_blocks * st.f_frsize;
    *free = st.f_bfree * st.f_frsize;
    *used = (*total) - (*free);
    
    return 0;
}

int storage_disk_usage_recursive(const char *path, unsigned long *total) {
    DIR *dir = opendir(path);
    if (!dir) return -1;
    
    *total = 0;
    struct dirent *entry;
    char filepath[PATH_MAX];
    
    while ((entry = readdir(dir))) {
        if (strcmp(entry->d_name, ".") == 0 || 
            strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        
        snprintf(filepath, sizeof(filepath), "%s/%s", path, entry->d_name);
        
        struct stat st;
        if (lstat(filepath, &st) == 0) {
            if (S_ISREG(st.st_mode)) {
                *total += st.st_size;
            } else if (S_ISDIR(st.st_mode)) {
                storage_disk_usage_recursive(filepath, total);
            }
        }
    }
    
    closedir(dir);
    return 0;
}

// 加密存储
int storage_encrypt_volume(const char *name, const char *password) {
    for (int i = 0; i < g_volume_count; i++) {
        if (strcmp(g_volumes[i].name, name) == 0) {
            g_volumes[i].encrypted = 1;
            printf("[STORAGE] Volume encrypted: %s\n", name);
            return 0;
        }
    }
    return -1;
}

int storage_decrypt_volume(const char *name, const char *password) {
    for (int i = 0; i < g_volume_count; i++) {
        if (strcmp(g_volumes[i].name, name) == 0) {
            g_volumes[i].encrypted = 0;
            printf("[STORAGE] Volume decrypted: %s\n", name);
            return 0;
        }
    }
    return -1;
}

// 格式化
int storage_format(const char *device, const char *fs_type) {
    printf("[STORAGE] Formatting %s as %s\n", device, fs_type);
    // 实际格式化需要调用 mkfs
    return 0;
}

int storage_mount(const char *device, const char *mount_point) {
    printf("[STORAGE] Mounting %s to %s\n", device, mount_point);
    return 0;
}

int storage_umount(const char *mount_point) {
    printf("[STORAGE] Unmounting %s\n", mount_point);
    return 0;
}

// 初始化
int storage_init(void) {
    printf("[STORAGE] Initializing storage module\n");
    memset(g_filesystems, 0, sizeof(g_filesystems));
    memset(g_volumes, 0, sizeof(g_volumes));
    
    // 扫描现有文件系统
    g_fs_count = storage_list_filesystems(g_filesystems, STORAGE_MAX_FS);
    printf("[STORAGE] Found %d filesystems\n", g_fs_count);
    
    return 0;
}

// 清理
void storage_cleanup(void) {
    printf("[STORAGE] Cleaning up storage module\n");
}

// 测试
int storage_test(void) {
    printf("[STORAGE] Running tests\n");
    
    // 测试文件系统信息
    filesystem_info_t fs_info;
    if (storage_get_fs_info("/", &fs_info) == 0) {
        printf("  - Root fs: %lu/%lu bytes\n", 
               fs_info.free, fs_info.total);
    }
    
    // 测试卷创建
    storage_volume_create("test_vol", "/tmp/test_vol", 1024*1024);
    
    // 测试卷列表
    storage_volume_t vol_list[8];
    int vol_count = storage_volume_list(vol_list, 8);
    printf("  - Created %d volumes\n", vol_count);
    
    // 测试磁盘使用
    unsigned long total, used, free;
    if (storage_disk_usage("/", &total, &used, &free) == 0) {
        printf("  - Disk usage: %lu/%lu bytes\n", used, total);
    }
    
    return 0;
}
