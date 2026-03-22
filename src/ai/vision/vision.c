/**
 * 视觉模块
 */

#include <stdio.h>

int vision_init(void) {
    printf("[AI/Vision] Initialized\n");
    return 0;
}

int vision_detect(const void *frame, void *result) {
    // TODO: 目标检测
    return 0;
}

int vision_recognize(const void *face, void *id) {
    // TODO: 人脸识别
    return 0;
}
