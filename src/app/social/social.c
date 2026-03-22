#include <stdio.h>
#include <string.h>

// ===== 朋友圈 =====
void social_moments_init(void) { printf("[Social] Moments initialized\n"); }
void social_moments_list(void) {
    printf("\n=== Moments ===\n");
    printf("1. [照片] 今日风景 (20赞)\n");
    printf("2. [文字] 心情记录 (5赞)\n");
    printf("3. [视频] 旅游视频 (50赞)\n");
    printf("=====================\n\n");
}
void social_moments_post_photo(const char *desc) {
    printf("\n=== Post Photo ===\n");
    printf("描述: %s\n", desc);
    printf("上传: photo.jpg\n");
    printf("位置: 永济\n");
    printf("可见: 全部好友\n");
    printf("发布成功! 🎉\n");
    printf("==================\n\n");
}
void social_moments_post_text(const char *text) {
    printf("\n=== Post Text ===\n");
    printf("内容: %s\n", text);
    printf("可见: 全部好友\n");
    printf("发布成功! 🎉\n");
    printf("==================\n\n");
}
void social_moments_like(const char *id) {
    printf("[Social] Liked: %s\n", id);
}
void social_moments_comment(const char *id, const char *comment) {
    printf("[Social] Commented on %s: %s\n", id, comment);
}

// ===== 好友 =====
void social_friends_init(void) { printf("[Social] Friends initialized\n"); }
void social_friends_list(void) {
    printf("\n=== Friends (128) ===\n");
    printf("1. 张三 👨\n");
    printf("2. 李四 👩\n");
    printf("3. 王五 👨‍💻\n");
    printf("=====================\n\n");
}
void social_friends_add(const char *name) {
    printf("\n=== Add Friend ===\n");
    printf("搜索: %s\n", name);
    printf("发送好友请求\n");
    printf("等待对方确认\n");
    printf("================\n\n");
}

// ===== 聊天 =====
void social_chat_init(void) { printf("[Social] Chat initialized\n"); }
void social_chat_list(void) {
    printf("\n=== Chats ===\n");
    printf("1. 老婆 (3条未读)\n");
    printf("2. 同事A (0条未读)\n");
    printf("3. 家人群 (10条未读)\n");
    printf("=====================\n\n");
}
void social_chat_send(const char *to, const char *msg) {
    printf("\n=== Send Message ===\n");
    printf("To: %s\n", to);
    printf("Msg: %s\n", msg);
    printf("发送成功 ✓\n");
    printf("================\n\n");
}

// ===== 群聊 =====
void social_group_init(void) { printf("[Social] Group initialized\n"); }
void social_group_create(const char *name, int count) {
    printf("\n=== Create Group ===\n");
    printf("名称: %s\n", name);
    printf("成员: %d人\n", count);
    printf("群号: 123456789\n");
    printf("创建成功! 🎉\n");
    printf("================\n\n");
}
void social_group_list(void) {
    printf("\n=== Groups ===\n");
    printf("1. 家人群 (5人)\n");
    printf("2. 同事群 (20人)\n");
    printf("3. 同学群 (30人)\n");
    printf("=====================\n\n");
}

// ===== 测试 =====
void social_test(void) {
    printf("\n=== Social Test ===\n");
    
    social_moments_init(); social_moments_list();
    social_moments_post_photo("美丽夕阳");
    social_moments_post_text("今天开心");
    social_moments_like("1"); social_moments_comment("1", "真美!");
    
    social_friends_init(); social_friends_list(); social_friends_add("赵六");
    
    social_chat_init(); social_chat_list(); social_chat_send("老婆", "晚点回家");
    
    social_group_init(); social_group_create("旅行团", 10); social_group_list();
    
    printf("==================\n\n");
}
