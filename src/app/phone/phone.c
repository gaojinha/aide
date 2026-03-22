/**
 * 电话应用
 */

#include <stdio.h>

int phone_init(void) {
    printf("[App/Phone] Initialized\n");
    return 0;
}

int phone_call(const char *number) {
    printf("[App/Phone] Calling: %s\n", number);
    return 0;
}

int phone_answer(void) {
    return 0;
}

int phone_hangup(void) {
    return 0;
}

// ===== 通话记录 =====
void phone_call_history(void) {
    printf("\n=== Call History ===\n");
    printf("1. 老婆 - 13800138001 - 10:30 - 5分钟 - 已接\n");
    printf("2. 同事A - 13800138002 - 昨天 - 2分钟 - 已接\n");
    printf("3. 快递 - 13800138003 - 昨天 - 未接\n");
    printf("4. 老板 - 13800138004 - 前天 - 10分钟 - 已接\n");
    printf("======================\n\n");
}

// ===== 通话录音 =====
void phone_record_start(void) { printf("[Phone] Recording started\n"); }
void phone_record_stop(void) {
    printf("\n=== Recording ===\n");
    printf("时长: 5分钟\n");
    printf("保存: /sdcall/record_001.m4a\n");
    printf("====================\n\n");
}

// ===== 免提/静音 =====
void phone_speaker_on(void) { printf("[Phone] Speaker ON\n"); }
void phone_speaker_off(void) { printf("[Phone] Speaker OFF\n"); }
void phone_mute_on(void) { printf("[Phone] Mute ON\n"); }
void phone_mute_off(void) { printf("[Phone] Mute OFF\n"); }
