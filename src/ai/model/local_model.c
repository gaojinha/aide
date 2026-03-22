#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MODELS 10

typedef struct { char name[64]; char path[128]; int size_mb; int loaded; } model_t;
static model_t models[MAX_MODELS];
static int model_count = 0;
static int current = -1;
static int online = 1;

int model_init(void) {
    printf("[Model] Initialized\n");
    printf("  Cloud: MiniMax API\n");
    printf("  Local: llama.cpp\n");
    
    model_t *m = &models[model_count++];
    strcpy(m->name, "Qwen2.5-0.5B"); m->size_mb = 350; m->loaded = 0;
    m = &models[model_count++];
    strcpy(m->name, "Phi-4-mini"); m->size_mb = 2000; m->loaded = 0;
    
    printf("  Models: %d\n", model_count);
    return 0;
}

int is_online(void) { return online; }

void check_network(void) { online = 1; printf("[Model] Network: %s\n", online?"ONLINE":"OFFLINE"); }

int load_local(int id) {
    if (id < 0 || id >= model_count) return -1;
    printf("[Local] Loading %s...\n", models[id].name);
    models[id].loaded = 1; current = id;
    return 0;
}

int infer_local(const char *p, char *r, int len) {
    if (current < 0) { snprintf(r, len, "No model loaded"); return -1; }
    snprintf(r, len, "[本地 %s] %s (llama.cpp)", models[current].name, p);
    return 0;
}

int infer(const char *prompt, char *response, int max_len) {
    check_network();
    if (online) {
        printf("[Model] Cloud mode\n");
        snprintf(response, max_len, "[云端] %s (MiniMax)", prompt);
    } else {
        printf("[Model] Offline mode\n");
        if (current < 0 && model_count > 0) load_local(0);
        return infer_local(prompt, response, max_len);
    }
    return 0;
}
