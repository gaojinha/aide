#include <stdio.h>
#include <time.h>
#include <string.h>

#define MAX_EMAILS 50
#define MAX_TASKS 50
#define MAX_MEETINGS 20
#define MAX_CLIENTS 30

// 邮件
typedef struct {
    char from[64];
    char to[64];
    char subject[128];
    char body[512];
    int read;
    int starred;
    time_t time;
} email_t;

// 任务
typedef struct {
    char title[128];
    char desc[256];
    int priority;  // 1-5
    int status;    // 0:todo 1:doing 2:done
    time_t due;
} task_t;

// 会议
typedef struct {
    char title[128];
    time_t start;
    time_t end;
    char attendees[256];
    char notes[512];
} meeting_t;

// 客户
typedef struct {
    char name[64];
    char company[64];
    char phone[32];
    char email[64];
    char notes[256];
    time_t last_contact;
} client_t;

static email_t emails[MAX_EMAILS];
static int email_count = 0;
static task_t tasks[MAX_TASKS];
static int task_count = 0;
static meeting_t meetings[MAX_MEETINGS];
static int meeting_count = 0;
static client_t clients[MAX_CLIENTS];
static int client_count = 0;

// 邮件模块
void workflow_mail_init(void) {
    printf("[Workflow] Mail initialized\n");
    
    // 模拟邮件
    email_t *e = &emails[email_count++];
    strcpy(e->from, "boss@company.com");
    strcpy(e->to, "me@company.com");
    strcpy(e->subject, "项目进度汇报");
    strcpy(e->body, "请今天下班前提交周报");
    e->read = 0;
    e->starred = 1;
    
    e = &emails[email_count++];
    strcpy(e->from, "hr@company.com");
    strcpy(e->to, "me@company.com");
    strcpy(e->subject, "下周一会议通知");
    strcpy(e->body, "请准时参加部门例会");
    e->read = 1;
    e->starred = 0;
    
    printf("  Emails: %d\n", email_count);
}

// 读邮件
void workflow_mail_list(void) {
    printf("\n=== Emails (%d) ===\n", email_count);
    for (int i = 0; i < email_count; i++) {
        printf("%d. [%c%c] %s\n", i+1, 
            emails[i].starred ? '*' : ' ',
            emails[i].read ? ' ' : 'N',
            emails[i].subject);
        printf("   From: %s\n", emails[i].from);
    }
    printf("====================\n\n");
}

// 写邮件
void workflow_mail_send(const char *to, const char *subject, const char *body) {
    printf("[Workflow] Sending email to: %s\n", to);
    printf("  Subject: %s\n", subject);
    printf("  Body: %s\n", body);
    printf("[Workflow] Email sent!\n");
}

// 日程/任务模块
void workflow_task_init(void) {
    printf("[Workflow] Tasks initialized\n");
    
    task_t *t = &tasks[task_count++];
    strcpy(t->title, "完成项目报告");
    strcpy(t->desc, "整理本周工作内容");
    t->priority = 3;
    t->status = 0;
    
    t = &tasks[task_count++];
    strcpy(t->title, "客户拜访");
    strcpy(t->desc, "拜访XX公司");
    t->priority = 5;
    t->status = 1;
    
    printf("  Tasks: %d\n", task_count);
}

// 任务列表
void workflow_task_list(void) {
    const char *status_name[] = {"TODO", "DOING", "DONE"};
    const char *priority_name[] = {"", "低", "中", "高", "紧急", "重要"};
    
    printf("\n=== Tasks (%d) ===\n", task_count);
    for (int i = 0; i < task_count; i++) {
        printf("%d. [%s] %s\n", i+1, status_name[tasks[i].status], tasks[i].title);
        printf("   Priority: %s\n", priority_name[tasks[i].priority]);
    }
    printf("====================\n\n");
}

// 添加任务
void workflow_task_add(const char *title, int priority) {
    task_t *t = &tasks[task_count++];
    strncpy(t->title, title, 127);
    t->priority = priority;
    t->status = 0;
    printf("[Workflow] Task added: %s\n", title);
}

// 会议模块
void workflow_meeting_init(void) {
    printf("[Workflow] Meetings initialized\n");
    
    meeting_t *m = &meetings[meeting_count++];
    strcpy(m->title, "周例会");
    strcpy(m->attendees, "team@company.com");
    strcpy(m->notes, "讨论项目进度");
    
    m = &meetings[meeting_count++];
    strcpy(m->title, "项目评审");
    strcpy(m->attendees, "pm@company.com, dev@company.com");
    strcpy(m->notes, "评审本周工作");
    
    printf("  Meetings: %d\n", meeting_count);
}

// 会议列表
void workflow_meeting_list(void) {
    printf("\n=== Meetings (%d) ===\n", meeting_count);
    for (int i = 0; i < meeting_count; i++) {
        printf("%d. %s\n", i+1, meetings[i].title);
        printf("   Attendees: %s\n", meetings[i].attendees);
    }
    printf("=======================\n\n");
}

// 客户模块
void workflow_client_init(void) {
    printf("[Workflow] Clients initialized\n");
    
    client_t *c = &clients[client_count++];
    strcpy(c->name, "张总");
    strcpy(c->company, "XX科技");
    strcpy(c->phone, "13800138000");
    strcpy(c->email, "zhang@xx.com");
    strcpy(c->notes, "重要客户");
    
    c = &clients[client_count++];
    strcpy(c->name, "李经理");
    strcpy(c->company, "YY集团");
    strcpy(c->phone, "13900139000");
    strcpy(c->email, "li@yy.com");
    strcpy(c->notes, "潜在客户");
    
    printf("  Clients: %d\n", client_count);
}

// 客户列表
void workflow_client_list(void) {
    printf("\n=== Clients (%d) ===\n", client_count);
    for (int i = 0; i < client_count; i++) {
        printf("%d. %s - %s\n", i+1, clients[i].name, clients[i].company);
        printf("   Phone: %s\n", clients[i].phone);
    }
    printf("======================\n\n");
}

// 报销模块
void workflow_expense_init(void) {
    printf("[Workflow] Expenses initialized\n");
    printf("  Recent: 3 records\n");
    printf("  Total this month: ¥2500\n");
}

void workflow_expense_list(void) {
    printf("\n=== Expenses ===\n");
    printf("Date       Category   Amount\n");
    printf("2026-03-20 交通       ¥150\n");
    printf("2026-03-18 餐饮       ¥280\n");
    printf("2026-03-15 办公       ¥450\n");
    printf("----------------------------\n");
    printf("Total: ¥880\n");
    printf("========================\n\n");
}

// 工作台概览
void workflow_dashboard(void) {
    printf("\n");
    printf("╔═══════════════════════════════════════╗\n");
    printf("║           Work Dashboard             ║\n");
    printf("╠═══════════════════════════════════════╣\n");
    printf("║ 📧 Emails:  %d (unread: %d, star: %d)   ║\n", 
        email_count, 1, 1);
    printf("║ ✓ Tasks:   %d (todo: %d, done: %d)     ║\n", 
        task_count, 1, 1);
    printf("║ 📅 Meetings: %d (today: %d)            ║\n", 
        meeting_count, 1);
    printf("║ 👥 Clients: %d                          ║\n", client_count);
    printf("║ 💰 Expenses: ¥2500/month              ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");
}

// 测试
void workflow_test(void) {
    printf("\n=== Workflow Test ===\n");
    
    // Mail
    workflow_mail_init();
    workflow_mail_list();
    
    // Tasks
    workflow_task_init();
    workflow_task_list();
    
    // Meetings
    workflow_meeting_init();
    workflow_meeting_list();
    
    // Clients
    workflow_client_init();
    workflow_client_list();
    
    // Expenses
    workflow_expense_init();
    workflow_expense_list();
    
    // Dashboard
    workflow_dashboard();
    
    printf("==================\n\n");
}
