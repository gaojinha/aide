#ifndef VISION_H
#define VISION_H

typedef struct {
    char label[64];
    float confidence;
} detection_t;

typedef struct {
    char id[64];
    char name[64];
    float confidence;
} face_result_t;

int vision_init(void);
int vision_detect(const void *frame, void *detections, int max);
int vision_detect_face(const void *frame, int *count);
int vision_recognize_face(const void *face, void *result);
int vision_ocr(const void *frame, char *text, int max_len);

#endif
