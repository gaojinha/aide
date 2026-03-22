#include <stdio.h>
#include <string.h>

typedef struct { char name[32]; char phone[32]; char email[64]; char group[32]; } contact_t;
static contact_t contacts[100];
static int contact_count = 0;

void contacts_init(void) {
    printf("[Contacts] Initialized\n");
    contact_t *c = &contacts[contact_count++];
    strcpy(c->name, "老婆"); strcpy(c->phone, "13800138001"); strcpy(c->email, "wife@test.com"); strcpy(c->group, "家人");
    c = &contacts[contact_count++];
    strcpy(c->name, "老板"); strcpy(c->phone, "13800138002"); strcpy(c->email, "boss@test.com"); strcpy(c->group, "工作");
    c = &contacts[contact_count++];
    strcpy(c->name, "张三"); strcpy(c->phone, "13800138003"); strcpy(c->email, "zhang@test.com"); strcpy(c->group, "朋友");
    printf("  Contacts: %d\n", contact_count);
}

void contacts_list(void) {
    printf("\n=== Contacts (%d) ===\n", contact_count);
    for (int i = 0; i < contact_count; i++) {
        printf("%d. %s - %s (%s)\n", i+1, contacts[i].name, contacts[i].phone, contacts[i].group);
    }
    printf("======================\n\n");
}

void contacts_add(const char *name, const char *phone, const char *group) {
    contact_t *c = &contacts[contact_count++];
    strncpy(c->name, name, 31);
    strncpy(c->phone, phone, 31);
    strcpy(c->group, group);
    printf("[Contacts] Added: %s\n", name);
}

void contacts_group_list(const char *group) {
    printf("\n=== Group: %s ===\n", group);
    for (int i = 0; i < contact_count; i++) {
        if (strcmp(contacts[i].group, group) == 0) {
            printf("%s - %s\n", contacts[i].name, contacts[i].phone);
        }
    }
    printf("======================\n\n");
}

void contacts_search(const char *keyword) {
    printf("\n=== Search: %s ===\n", keyword);
    for (int i = 0; i < contact_count; i++) {
        if (strstr(contacts[i].name, keyword) || strstr(contacts[i].phone, keyword)) {
            printf("%s - %s\n", contacts[i].name, contacts[i].phone);
        }
    }
    printf("======================\n\n");
}

void contacts_test(void) {
    printf("\n=== Contacts Test ===\n");
    contacts_init();
    contacts_list();
    contacts_add("李四", "13800138004", "同事");
    contacts_group_list("家人");
    contacts_search("老");
    printf("==================\n\n");
}
