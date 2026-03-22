/**
 * 用户认证模块 - 登录/密码/指纹
 */

#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_USERS 10

// 用户角色
typedef enum {
    ROLE_GUEST,     // 访客
    ROLE_USER,      // 普通用户
    ROLE_ADMIN,     // 管理员
    ROLE_OWNER      // 所有者
} user_role_t;

// 用户状态
typedef enum {
    USER_ACTIVE,
    USER_LOCKED,
    USER_DISABLED
} user_status_t;

// 用户
typedef struct {
    int id;
    char username[32];
    char password_hash[64];
    char fingerprint_id[32];
    user_role_t role;
    user_status_t status;
    int login_count;
    time_t last_login;
} user_t;

static user_t users[MAX_USERS];
static int user_count = 0;
static int current_user_id = -1;

// 初始化
int auth_init(void) {
    printf("[Auth] Initialized\n");
    // 默认用户
    auth_add_user("admin", "admin123", ROLE_ADMIN);
    auth_add_user("gao", "password", ROLE_OWNER);
    printf("  Default: admin, gao\n");
    return 0;
}

// 添加用户
int auth_add_user(const char *username, const char *password, user_role_t role) {
    if (user_count >= MAX_USERS) return -1;
    
    user_t *u = &users[user_count];
    u->id = user_count + 1;
    strncpy(u->username, username, 31);
    // 简单hash
    snprintf(u->password_hash, 64, "hash_%s", password);
    u->role = role;
    u->status = USER_ACTIVE;
    u->login_count = 0;
    user_count++;
    
    printf("[Auth] User added: %s (role: %d)\n", username, role);
    return u->id;
}

// 密码验证
int auth_verify_password(const char *username, const char *password) {
    char expected[64];
    snprintf(expected, 64, "hash_%s", password);
    
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0) {
            if (users[i].status != USER_ACTIVE) {
                printf("[Auth] User locked: %s\n", username);
                return -1;
            }
            // 简单比较
            if (strcmp(users[i].password_hash, expected) == 0) {
                users[i].login_count++;
                users[i].last_login = time(NULL);
                current_user_id = i;
                printf("[Auth] Login OK: %s\n", username);
                return 0;
            }
        }
    }
    printf("[Auth] Login failed: %s\n", username);
    return -1;
}

// 指纹验证
int auth_verify_fingerprint(const char *fp_id) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].fingerprint_id, fp_id) == 0) {
            current_user_id = i;
            printf("[Auth] Fingerprint OK: %s\n", users[i].username);
            return 0;
        }
    }
    return -1;
}

// 注册指纹
int auth_register_fingerprint(const char *username, const char *fp_id) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0) {
            strncpy(users[i].fingerprint_id, fp_id, 31);
            printf("[Auth] Fingerprint registered: %s\n", username);
            return 0;
        }
    }
    return -1;
}

// 登出
int auth_logout(void) {
    if (current_user_id >= 0) {
        printf("[Auth] Logout: %s\n", users[current_user_id].username);
        current_user_id = -1;
    }
    return 0;
}

// 获取当前用户
const char* auth_get_current_user(void) {
    if (current_user_id >= 0) {
        return users[current_user_id].username;
    }
    return NULL;
}

// 检查权限
int auth_check_permission(user_role_t required) {
    if (current_user_id < 0) {
        printf("[Auth] No user logged in\n");
        return 0;
    }
    return users[current_user_id].role >= required;
}

// 锁定用户
int auth_lock_user(const char *username) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0) {
            users[i].status = USER_LOCKED;
            printf("[Auth] User locked: %s\n", username);
            return 0;
        }
    }
    return -1;
}

// 解锁用户
int auth_unlock_user(const char *username) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0) {
            users[i].status = USER_ACTIVE;
            printf("[Auth] User unlocked: %s\n", username);
            return 0;
        }
    }
    return -1;
}

// 列出用户
void auth_list_users(void) {
    printf("\n=== Users (%d) ===\n", user_count);
    const char *role_names[] = {"GUEST", "USER", "ADMIN", "OWNER"};
    const char *status_names[] = {"ACTIVE", "LOCKED", "DISABLED"};
    
    for (int i = 0; i < user_count; i++) {
        printf("%d. %s [role:%s status:%s] login:%d\n",
            users[i].id,
            users[i].username,
            role_names[users[i].role],
            status_names[users[i].status],
            users[i].login_count);
    }
    printf("Current: %s\n", auth_get_current_user() ? auth_get_current_user() : "(none)");
    printf("==================\n\n");
}

// 测试
void auth_test(void) {
    printf("\n=== Auth Test ===\n");
    
    auth_list_users();
    
    // 登录测试
    printf("Login test:\n");
    int ret = auth_verify_password("admin", "admin123");
    printf("admin/admin123: %s\n", ret == 0 ? "OK" : "FAIL");
    
    ret = auth_verify_password("gao", "password");
    printf("gao/password: %s\n", ret == 0 ? "OK" : "FAIL");
    
    // 权限测试
    printf("\nPermission test:\n");
    ret = auth_check_permission(ROLE_ADMIN);
    printf("Is admin? %s\n", ret ? "YES" : "NO");
    
    // 指纹测试
    auth_register_fingerprint("gao", "fp_12345");
    ret = auth_verify_fingerprint("fp_12345");
    printf("Fingerprint: %s\n", ret == 0 ? "OK" : "FAIL");
    
    auth_logout();
    auth_list_users();
    
    printf("==================\n\n");
}
