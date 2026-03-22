/**
 * IPC - 进程间通信模块
 * 支持: 消息队列、共享内存、信号量、管道
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <pthread.h>
#include <errno.h>

#define IPC_MAX_MSG_SIZE 1024
#define IPC_MAX_QUEUE 32
#define IPC_MAX_SHM 16

typedef enum {
    IPC_MSGQ,    // 消息队列
    IPC_SHM,     // 共享内存
    IPC_SEM,     // 信号量
    IPC_SOCKET,  // Unix Socket
    IPC_PIPE     // 管道
} ipc_type_t;

typedef struct {
    int id;
    ipc_type_t type;
    key_t key;
    int fd;
    void *addr;
    size_t size;
} ipc_handle_t;

typedef struct {
    long mtype;
    char mtext[IPC_MAX_MSG_SIZE];
} ipc_msg_t;

static ipc_handle_t g_msgqs[IPC_MAX_QUEUE];
static ipc_handle_t g_shms[IPC_MAX_SHM];
static int g_msgq_count = 0;
static int g_shm_count = 0;

// 消息队列操作
int ipc_msgq_create(key_t key, int mode) {
    int msgid = msgget(key, IPC_CREAT | mode);
    if (msgid < 0) {
        perror("msgget");
        return -1;
    }
    
    if (g_msgq_count < IPC_MAX_QUEUE) {
        g_msgqs[g_msgq_count].id = msgid;
        g_msgqs[g_msgq_count].type = IPC_MSGQ;
        g_msgqs[g_msgq_count].key = key;
        g_msgq_count++;
    }
    
    return msgid;
}

int ipc_msgq_send(int msgid, long type, const void *data, size_t len) {
    ipc_msg_t msg;
    msg.mtype = type;
    memcpy(msg.mtext, data, len < IPC_MAX_MSG_SIZE ? len : IPC_MAX_MSG_SIZE);
    
    return msgsnd(msgid, &msg, len, 0);
}

int ipc_msgq_recv(int msgid, long *type, void *buf, size_t bufsize) {
    ipc_msg_t msg;
    int ret = msgrcv(msgid, &msg, IPC_MAX_MSG_SIZE, *type, 0);
    
    if (ret > 0) {
        memcpy(buf, msg.mtext, ret < bufsize ? ret : bufsize);
    }
    return ret;
}

int ipc_msgq_destroy(int msgid) {
    return msgctl(msgid, IPC_RMID, NULL);
}

// 共享内存操作
int ipc_shm_create(key_t key, size_t size) {
    int shmid = shmget(key, size, IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        return -1;
    }
    
    void *addr = shmat(shmid, NULL, 0);
    if (addr == (void *)-1) {
        perror("shmat");
        return -1;
    }
    
    if (g_shm_count < IPC_MAX_SHM) {
        g_shms[g_shm_count].id = shmid;
        g_shms[g_shm_count].type = IPC_SHM;
        g_shms[g_shm_count].key = key;
        g_shms[g_shm_count].addr = addr;
        g_shms[g_shm_count].size = size;
        g_shm_count++;
    }
    
    return shmid;
}

void *ipc_shm_attach(int shmid) {
    return shmat(shmid, NULL, SHM_RDONLY);
}

int ipc_shm_detach(void *addr) {
    return shmdt(addr);
}

int ipc_shm_destroy(int shmid) {
    return shmctl(shmid, IPC_RMID, NULL);
}

// 信号量操作
int ipc_sem_create(key_t key, int init_val) {
    int semid = semget(key, 1, IPC_CREAT | 0666);
    if (semid < 0) {
        perror("semget");
        return -1;
    }
    
    union semun arg;
    arg.val = init_val;
    semctl(semid, 0, SETVAL, arg);
    
    return semid;
}

int ipc_sem_wait(int semid) {
    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_op = -1;
    sb.sem_flg = 0;
    return semop(semid, &sb, 1);
}

int ipc_sem_signal(int semid) {
    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_op = 1;
    sb.sem_flg = 0;
    return semop(semid, &sb, 1);
}

int ipc_sem_destroy(int semid) {
    return semctl(semid, 0, IPC_RMID);
}

// Unix Socket 操作
int ipc_socket_create(const char *path) {
    int sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        return -1;
    }
    
    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, path, sizeof(addr.sun_path) - 1);
    
    unlink(path);
    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        close(sockfd);
        return -1;
    }
    
    return sockfd;
}

int ipc_socket_send(int sockfd, const char *path, const void *data, size_t len) {
    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, path, sizeof(addr.sun_path) - 1);
    
    return sendto(sockfd, data, len, 0, (struct sockaddr *)&addr, sizeof(addr));
}

int ipc_socket_recv(int sockfd, void *buf, size_t bufsize) {
    struct sockaddr_un addr;
    socklen_t len = sizeof(addr);
    return recvfrom(sockfd, buf, bufsize, 0, (struct sockaddr *)&addr, &len);
}

// 初始化
int ipc_init(void) {
    printf("[IPC] Initializing IPC module\n");
    memset(g_msgqs, 0, sizeof(g_msgqs));
    memset(g_shms, 0, sizeof(g_shms));
    return 0;
}

// 清理
void ipc_cleanup(void) {
    printf("[IPC] Cleaning up IPC\n");
    
    // 分离共享内存
    for (int i = 0; i < g_shm_count; i++) {
        if (g_shms[i].addr) {
            shmdt(g_shms[i].addr);
        }
    }
}

// 测试
int ipc_test(void) {
    printf("[IPC] Running tests\n");
    
    // 测试消息队列
    key_t key = ftok("/tmp", 'A');
    int msgid = ipc_msgq_create(key, 0666);
    if (msgid >= 0) {
        printf("  - Message queue created: %d\n", msgid);
        ipc_msgq_send(msgid, 1, "Hello", 5);
        
        char buf[128];
        long type = 1;
        int ret = ipc_msgq_recv(msgid, &type, buf, sizeof(buf));
        if (ret > 0) {
            buf[ret] = 0;
            printf("  - Received: %s\n", buf);
        }
        ipc_msgq_destroy(msgid);
    }
    
    // 测试共享内存
    int shmid = ipc_shm_create(key + 1, 4096);
    if (shmid >= 0) {
        printf("  - Shared memory created: %d\n", shmid);
        ipc_shm_destroy(shmid);
    }
    
    // 测试信号量
    int semid = ipc_sem_create(key + 2, 1);
    if (semid >= 0) {
        printf("  - Semaphore created: %d\n", semid);
        ipc_sem_signal(semid);
        ipc_sem_destroy(semid);
    }
    
    return 0;
}
