#include <stdio.h>
#include <stdlib.h>

#define MAX_THREADS 8
#define MAX_TASKS 50

typedef void (*task_func_t)(void *);

typedef struct task {
    task_func_t func;
    void *arg;
    int priority;
} task_t;

typedef struct thread_pool {
    int thread_count;
    int active_threads;
    int pending_tasks;
    task_t tasks[MAX_TASKS];
    int task_head;
    int task_tail;
} thread_pool_t;

static thread_pool_t tp = {0};

// 初始化
void threadpool_init(int threads) {
    if (threads > MAX_THREADS) threads = MAX_THREADS;
    tp.thread_count = threads;
    tp.active_threads = 0;
    tp.pending_tasks = 0;
    tp.task_head = 0;
    tp.task_tail = 0;
    
    printf("[ThreadPool] Initialized: %d threads, %d max tasks\n", 
        threads, MAX_TASKS);
}

// 添加任务
int threadpool_add(task_func_t func, void *arg, int priority) {
    if (tp.pending_tasks >= MAX_TASKS) {
        printf("[ThreadPool] ERROR: task queue full\n");
        return -1;
    }
    
    task_t *task = &tp.tasks[tp.task_tail];
    task->func = func;
    task->arg = arg;
    task->priority = priority;
    
    tp.task_tail = (tp.task_tail + 1) % MAX_TASKS;
    tp.pending_tasks++;
    
    return 0;
}

// 执行任务
void threadpool_execute(void) {
    if (tp.pending_tasks == 0) return;
    
    task_t *task = &tp.tasks[tp.task_head];
    tp.task_head = (tp.task_head + 1) % MAX_TASKS;
    tp.pending_tasks--;
    tp.active_threads++;
    
    // 执行
    if (task->func) {
        task->func(task->arg);
    }
    
    tp.active_threads--;
}

// 状态
void threadpool_status(void) {
    printf("\n=== ThreadPool Status ===\n");
    printf("Threads: %d\n", tp.thread_count);
    printf("Active: %d\n", tp.active_threads);
    printf("Pending: %d\n", tp.pending_tasks);
    printf("=========================\n\n");
}

void demo_task(void *arg) {
    printf("[Task] Running: %s\n", (char*)arg);
}

void threadpool_test(void) {
    printf("\n=== ThreadPool Test ===\n");
    threadpool_init(4);
    threadpool_status();
    
    threadpool_add(demo_task, "Task 1", 0);
    threadpool_add(demo_task, "Task 2", 0);
    threadpool_add(demo_task, "Task 3", 0);
    
    printf("Adding 3 tasks...\n");
    threadpool_status();
    
    while (tp.pending_tasks > 0) {
        threadpool_execute();
    }
    
    threadpool_status();
    printf("==================\n\n");
}
