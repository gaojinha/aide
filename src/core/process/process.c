/**
 * Process - 进程管理模块
 * 支持: 进程创建、销毁、监控、优先级、调度
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sched.h>
#include <pthread.h>
#include <errno.h>
#include <signal.h>

#define MAX_PROCESSES 256
#define MAX_THREADS 64

typedef enum {
    PROC_RUNNING,
    PROC_ZOMBIE,
    PROC_STOPPED,
    PROC_DEAD
} process_state_t;

typedef struct {
    pid_t pid;
    pid_t ppid;
    char name[64];
    process_state_t state;
    int priority;
    int nice;
    size_t memory;
    time_t start_time;
    time_t cpu_time;
} process_info_t;

typedef struct {
    pthread_t tid;
    char name[64];
    void *(*start_routine)(void *);
    void *arg;
    int running;
} thread_info_t;

static process_info_t g_processes[MAX_PROCESSES];
static thread_info_t g_threads[MAX_THREADS];
static int g_process_count = 0;
static int g_thread_count = 0;
static pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;

// 进程创建
pid_t process_create(const char *name, void (*entry)(void), char *const argv[]) {
    pid_t pid = fork();
    
    if (pid == 0) {
        // 子进程
        if (entry) {
            entry();
        } else if (argv) {
            execvp(argv[0], argv);
        }
        exit(0);
    } else if (pid > 0) {
        // 父进程
        pthread_mutex_lock(&g_lock);
        if (g_process_count < MAX_PROCESSES) {
            g_processes[g_process_count].pid = pid;
            g_processes[g_process_count].ppid = getpid();
            strncpy(g_processes[g_process_count].name, name, 63);
            g_processes[g_process_count].state = PROC_RUNNING;
            g_processes[g_process_count].start_time = time(NULL);
            g_process_count++;
        }
        pthread_mutex_unlock(&g_lock);
    }
    
    return pid;
}

// 进程终止
int process_kill(pid_t pid, int sig) {
    return kill(pid, sig);
}

// 等待进程
pid_t process_wait(pid_t pid, int *status) {
    return waitpid(pid, status, 0);
}

// 获取进程信息
int process_info(pid_t pid, process_info_t *info) {
    char path[64];
    snprintf(path, sizeof(path), "/proc/%d/status", pid);
    
    FILE *fp = fopen(path, "r");
    if (!fp) return -1;
    
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "Name:", 5) == 0) {
            sscanf(line + 5, "%s", info->name);
        } else if (strncmp(line, "State:", 6) == 0) {
            char state;
            sscanf(line + 6, "%c", &state);
            switch (state) {
                case 'R': info->state = PROC_RUNNING; break;
                case 'Z': info->state = PROC_ZOMBIE; break;
                case 'S': info->state = PROC_STOPPED; break;
                default: info->state = PROC_DEAD; break;
            }
        } else if (strncmp(line, "Threads:", 8) == 0) {
            // ignore
        } else if (strncmp(line, "VmRSS:", 6) == 0) {
            sscanf(line + 6, "%zu", &info->memory);
        }
    }
    fclose(fp);
    
    info->pid = pid;
    info->ppid = getppid();
    
    return 0;
}

// 列出所有进程
int process_list(process_info_t *list, int max_count) {
    DIR *dir = opendir("/proc");
    if (!dir) return -1;
    
    int count = 0;
    struct dirent *entry;
    
    while ((entry = readdir(dir)) && count < max_count) {
        if (entry->d_name[0] >= '0' && entry->d_name[0] <= '9') {
            pid_t pid = atoi(entry->d_name);
            if (process_info(pid, &list[count]) == 0) {
                count++;
            }
        }
    }
    
    closedir(dir);
    return count;
}

// 设置进程优先级
int process_set_priority(pid_t pid, int priority) {
    return setpriority(PRIO_PROCESS, pid, priority);
}

int process_get_priority(pid_t pid) {
    return getpriority(PRIO_PROCESS, pid);
}

// 设置 Nice 值
int process_set_nice(pid_t pid, int nice) {
    return setpriority(PRIO_PROCESS, pid, nice);
}

// 线程创建
pthread_t thread_create(const char *name, void *(*start_routine)(void *), void *arg) {
    pthread_t tid;
    pthread_attr_t attr;
    
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    
    if (pthread_create(&tid, &attr, start_routine, arg) == 0) {
        pthread_mutex_lock(&g_lock);
        if (g_thread_count < MAX_THREADS) {
            g_threads[g_thread_count].tid = tid;
            strncpy(g_threads[g_thread_count].name, name, 63);
            g_threads[g_thread_count].running = 1;
            g_thread_count++;
        }
        pthread_mutex_unlock(&g_lock);
    }
    
    pthread_attr_destroy(&attr);
    return tid;
}

// 线程终止
void thread_exit(void *retval) {
    pthread_exit(retval);
}

// 线程等待
int thread_join(pthread_t thread, void **retval) {
    return pthread_join(thread, retval);
}

// 获取当前线程 ID
pthread_t thread_self(void) {
    return pthread_self();
}

// 线程列表
int thread_list(thread_info_t *list, int max_count) {
    pthread_mutex_lock(&g_lock);
    int count = g_thread_count < max_count ? g_thread_count : max_count;
    memcpy(list, g_threads, count * sizeof(thread_info_t));
    pthread_mutex_unlock(&g_lock);
    return count;
}

// 调度控制
int process_sched_yield(void) {
    return sched_yield();
}

int process_sched_set_affinity(pid_t pid, cpu_set_t *mask) {
    return sched_setaffinity(0, sizeof(cpu_set_t), mask);
}

int process_sched_get_affinity(pid_t pid, cpu_set_t *mask) {
    return sched_getaffinity(0, sizeof(cpu_set_t), mask);
}

// 资源限制
int process_set_rlimit(int resource, struct rlimit *rlim) {
    return setrlimit(resource, rlim);
}

int process_get_rlimit(int resource, struct rlimit *rlim) {
    return getrlimit(resource, rlim);
}

// 初始化
int process_init(void) {
    printf("[PROCESS] Initializing process module\n");
    memset(g_processes, 0, sizeof(g_processes));
    memset(g_threads, 0, sizeof(g_threads));
    return 0;
}

// 清理
void process_cleanup(void) {
    printf("[PROCESS] Cleaning up process module\n");
}

// 测试
int process_test(void) {
    printf("[PROCESS] Running tests\n");
    
    // 测试进程创建
    pid_t pid = process_create("test_proc", NULL, (char*[]){"ls", "-la", NULL});
    if (pid > 0) {
        printf("  - Process created: %d\n", pid);
        int status;
        process_wait(pid, &status);
        printf("  - Process exited with status: %d\n", WEXITSTATUS(status));
    }
    
    // 测试线程创建
    void *test_thread(void *arg) {
        printf("  - Thread running\n");
        sleep(1);
        return NULL;
    }
    
    pthread_t tid = thread_create("test_thread", test_thread, NULL);
    if (tid) {
        thread_join(tid, NULL);
        printf("  - Thread joined\n");
    }
    
    // 列出进程
    process_info_t list[10];
    int count = process_list(list, 10);
    printf("  - Found %d processes\n", count);
    
    return 0;
}
