#include <stdio.h>
#include <string.h>

// 用户角色 (与auth.c一致)
typedef enum {
    ROLE_GUEST,
    ROLE_USER,
    ROLE_ADMIN,
    ROLE_OWNER
} user_role_t;

#define MAX_PERMS 50

typedef enum {
    RES_SYSTEM, RES_FILE, RES_NETWORK, RES_VOICE,
    RES_CAMERA, RES_SENSOR, RES_GPIO, RES_USER, RES_DATA
} resource_t;

typedef enum {
    OP_READ, OP_WRITE, OP_EXEC, OP_DELETE
} operation_t;

typedef struct {
    int id;
    user_role_t role;
    resource_t resource;
    operation_t operation;
    int allowed;
} permission_t;

static permission_t permissions[MAX_PERMS];
static int perm_count = 0;

int acl_init(void) {
    printf("[ACL] Initialized\n");
    acl_add_rule(ROLE_OWNER, RES_SYSTEM, OP_READ, 1);
    acl_add_rule(ROLE_OWNER, RES_SYSTEM, OP_WRITE, 1);
    acl_add_rule(ROLE_ADMIN, RES_SYSTEM, OP_READ, 1);
    acl_add_rule(ROLE_ADMIN, RES_FILE, OP_WRITE, 1);
    acl_add_rule(ROLE_USER, RES_VOICE, OP_READ, 1);
    acl_add_rule(ROLE_GUEST, RES_SENSOR, OP_READ, 1);
    printf("  Rules: %d\n", perm_count);
    return 0;
}

int acl_add_rule(user_role_t role, resource_t resource, operation_t op, int allow) {
    if (perm_count >= MAX_PERMS) return -1;
    permissions[perm_count].id = perm_count + 1;
    permissions[perm_count].role = role;
    permissions[perm_count].resource = resource;
    permissions[perm_count].operation = op;
    permissions[perm_count].allowed = allow;
    perm_count++;
    return 0;
}

int acl_check(user_role_t role, resource_t resource, operation_t op) {
    for (int i = 0; i < perm_count; i++) {
        if (permissions[i].role == role && 
            permissions[i].resource == resource && 
            permissions[i].operation == op) {
            return permissions[i].allowed;
        }
    }
    return 0;
}

const char* acl_resource_name(resource_t r) {
    const char *names[] = {"system","file","network","voice","camera","sensor","gpio","user","data"};
    return names[r];
}

const char* acl_operation_name(operation_t op) {
    const char *names[] = {"read", "write", "exec", "delete"};
    return names[op];
}

void acl_list(void) {
    printf("\n=== ACL Rules (%d) ===\n", perm_count);
    const char *role_names[] = {"GUEST", "USER", "ADMIN", "OWNER"};
    for (int i = 0; i < perm_count; i++) {
        printf("%d. %s.%s -> %s\n", permissions[i].id,
            role_names[permissions[i].role],
            acl_operation_name(permissions[i].operation),
            acl_resource_name(permissions[i].resource));
    }
    printf("==================\n\n");
}

void acl_test(void) {
    printf("\n=== ACL Test ===\n");
    acl_list();
    printf("OWNER system.write: %s\n", acl_check(ROLE_OWNER, RES_SYSTEM, OP_WRITE) ? "ALLOW" : "DENY");
    printf("ADMIN file.write: %s\n", acl_check(ROLE_ADMIN, RES_FILE, OP_WRITE) ? "ALLOW" : "DENY");
    printf("USER camera.write: %s\n", acl_check(ROLE_USER, RES_CAMERA, OP_WRITE) ? "ALLOW" : "DENY");
    printf("GUEST file.write: %s\n", acl_check(ROLE_GUEST, RES_FILE, OP_WRITE) ? "ALLOW" : "DENY");
    printf("==================\n\n");
}
