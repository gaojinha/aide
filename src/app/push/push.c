#include <stdio.h>
#include <time.h>
#include <string.h>

// 推送类型
typedef enum {
    PUSH_NOTIFICATION,  // 系统通知
    PUSH_EMAIL,         // 邮件
    PUSH_SMS,          // 短信
    PUSH_CALL           // 电话
} push_type_t;

// 推送状态
typedef struct {
    int id;
    push_type_t type;
    char title[64];
    char body[256];
    char sender[64];
    int read;
    time_t time;
} push_message_t;

#define MAX_PUSH 50
static push_message_t pushes[MAX_PUSH];
static int push_count = 0;

// 初始化
int push_init(void) {
    printf("[Push] Initialized\n");
    return 0;
}

// 发送通知
int push_notify(const char *title, const char *body) {
    printf("[Push] Notification: %s - %s\n", title, body);
    // TODO: 实际发送
    return 0;
}

// 发送邮件
int push_email(const char *to, const char *subject, const char *body) {
    printf("[Push] Email to: %s\n  Subject: %s\n", to, subject);
    // TODO: 实际发送
    return 0;
}

// 接收推送(模拟)
int push_receive(push_type_t type, const char *title, const char *body, const char *from) {
    if (push_count >= MAX_PUSH) return -1;
    
    push_message_t *p = &pushes[push_count];
    p->id = push_count + 1;
    p->type = type;
    strncpy(p->title, title, 63);
    strncpy(p->body, body, 255);
    strncpy(p->sender, from, 63);
    p->read = 0;
    p->time = time(NULL);
    push_count++;
    
    printf("[Push] Received: [%s] %s\n", from, title);
    return push_count;
}

// 标记已读
int push_mark_read(int id) {
    for (int i = 0; i < push_count; i++) {
        if (pushes[i].id == id) {
            pushes[i].read = 1;
            return 0;
        }
    }
    return -1;
}

// 获取未读数
int push_get_unread(void) {
    int count = 0;
    for (int i = 0; i < push_count; i++) {
        if (!pushes[i].read) count++;
    }
    return count;
}

// 列出消息
void push_list(void) {
    printf("\n=== Push Messages (%d) ===\n", push_count);
    for (int i = 0; i < push_count; i++) {
        printf("%d. [%s] %s %s\n",
            pushes[i].id,
            pushes[i].read ? "read" : "unread",
            pushes[i].sender,
            pushes[i].title);
    }
    printf("Unread: %d\n", push_get_unread());
    printf("========================\n\n");
}

// 测试
void push_test(void) {
    printf("\n=== Push Test ===\n");
    
    push_notify("测试通知", "这是一条测试消息");
    
    push_receive(PUSH_NOTIFICATION, "新消息", "有人给你发消息", "微信");
    push_receive(PUSH_EMAIL, "邮件提醒", "你有新邮件", "boss@company.com");
    push_receive(PUSH_CALL, "未接来电", "1234567890", "老婆");
    
    push_list();
    
    push_mark_read(1);
    printf("After mark read:\n");
    push_list();
    
    printf("==================\n\n");
}
