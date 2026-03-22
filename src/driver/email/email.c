#include <stdio.h>
#include <string.h>

void email_init(void) { printf("[Email] Initialized\n"); }

void email_smtp_send(const char *to, const char *subject, const char *body) {
    printf("\n=== SMTP Send ===\n");
    printf("SMTP: smtp.163.com:587\n");
    printf("From: gaojinha@163.com\n");
    printf("To: %s\n", to);
    printf("Subject: %s\n", subject);
    printf("Body: %s\n", body);
    printf("Sending...\n");
    printf("Sent OK!\n");
    printf("====================\n\n");
}

void email_imap_list(void) {
    printf("\n=== IMAP List ===\n");
    printf("Folder: INBOX (50)\n");
    printf("1. [UNREAD] 项目进度汇报\n");
    printf("2. [READ] 会议通知\n");
    printf("3. [UNREAD] 快递通知\n");
    printf("======================\n\n");
}

void email_imap_fetch(const char *id) {
    printf("\n=== IMAP Fetch: %s ===\n", id);
    printf("From: boss@company.com\n");
    printf("To: me@163.com\n");
    printf("Subject: 项目进度汇报\n");
    printf("Date: 2026-03-22 10:00\n");
    printf("\n内容:\n请提交本周周报, 谢谢!\n");
    printf("======================\n\n");
}

void email_attachment(const char *file) {
    printf("\n=== Attachment ===\n");
    printf("File: %s\n", file);
    printf("Size: 1.2MB\n");
    printf("Downloading...\n");
    printf("Saved!\n");
    printf("====================\n\n");
}

void email_test(void) {
    printf("\n=== Email Test ===\n");
    email_init();
    email_smtp_send("friend@163.com", "测试", "你好!");
    email_imap_list();
    email_imap_fetch("1");
    email_attachment("report.pdf");
    printf("==================\n\n");
}
