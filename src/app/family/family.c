#include <stdio.h>
#include <string.h>

typedef struct { char name[32]; char relation[16]; char phone[32]; } family_t;
static family_t members[10];
static int member_count = 0;

void family_init(void) {
    printf("[Family] Initialized\n");
    family_t *m = &members[member_count++];
    strcpy(m->name, "老婆"); strcpy(m->relation, "妻子"); strcpy(m->phone, "13800138001");
    m = &members[member_count++];
    strcpy(m->name, "姑娘"); strcpy(m->relation, "女儿"); strcpy(m->phone, "13800138002");
    m = &members[member_count++];
    strcpy(m->name, "老爸"); strcpy(m->relation, "父亲"); strcpy(m->phone, "13800138003");
    printf("  Members: %d\n", member_count);
}

void family_list(void) {
    printf("\n=== Family (%d) ===\n", member_count);
    for (int i = 0; i < member_count; i++) {
        printf("%d. %s (%s) - %s\n", i+1, members[i].name, members[i].relation, members[i].phone);
    }
    printf("=====================\n\n");
}

void family_call(const char *name) { printf("[Family] Calling %s...\n", name); }
void family_message(const char *name) { printf("[Family] Messaging %s\n", name); }
void family_photo(void) { printf("[Family] Photo gallery: 1280张\n"); }
void family_video(void) { printf("[Family] Video calls: 可用\n"); }
void family_monitor(void) { printf("[Family] Home monitor: 正常\n"); }

void family_child_story(void) { printf("\n=== Story for Child ===\n从前有座山...\n=====================\n\n"); }
void family_child_homework(void) { printf("\n=== Homework Help ===\n数学: 1+1=2\n====================\n\n"); }
void family_elder_care(void) { printf("\n=== Elder Care ===\n提醒: 14:00 测量血压\n====================\n\n"); }
void family_pet(void) { printf("\n=== Pet ===\n小花(猫): 已喂食\n====================\n\n"); }

void family_dashboard(void) {
    printf("\n");
    printf("╔═══════════════════════════════════════╗\n");
    printf("║        Family Dashboard             ║\n");
    printf("╠═══════════════════════════════════════╣\n");
    printf("║ 👨‍👩‍👧 成员: 3人                       ║\n");
    printf("║ 📞 快捷呼叫: 一键拨打              ║\n");
    printf("║ 🏠 家中监控: 正常                   ║\n");
    printf("║ 📸 照片: 1280张                    ║\n");
    printf("║ 🐱 宠物: 小花                       ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");
}

void family_test(void) {
    printf("\n=== Family Test ===\n");
    family_init(); family_list();
    family_call("老婆"); family_message("姑娘");
    family_photo(); family_video(); family_monitor();
    family_child_story(); family_child_homework();
    family_elder_care(); family_pet();
    family_dashboard();
    printf("==================\n\n");
}
