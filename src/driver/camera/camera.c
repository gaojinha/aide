/**
 * 摄像头驱动
 */

#include <stdio.h>

int camera_init(void) {
    printf("[Driver/Camera] Initialized\n");
    return 0;
}

int camera_capture(void *frame) {
    // TODO: 拍照
    return 0;
}

int camera_stream_start(void) {
    // TODO: 开始预览
    return 0;
}

int camera_stream_stop(void) {
    // TODO: 停止预览
    return 0;
}
