/**
 * 首次设置向导
 */

#include <stdio.h>
#include <string.h>

typedef enum {
    WIZARD_LANGUAGE,
    WIZARD_NAME,
    WIZARD_WAKE_WORD,
    WIZARD_API_KEY,
    WIZARD_OUTPUT_MODE,
    WIZARD_COMPLETE
} wizard_step_t;

static wizard_step_t current_step = WIZARD_LANGUAGE;
static int wizard_done = 0;
static char current_lang[16] = "zh-CN";

void wizard_speak(const char *text) { printf("[Voice] %s\n", text); }

int wizard_is_done(void) { return wizard_done; }
void wizard_reset(void) { current_step = WIZARD_LANGUAGE; wizard_done = 0; }

void wizard_show(const char *title, const char *voice) {
    printf("\n=== %s ===\n", title);
    if (voice) wizard_speak(voice);
}

void wizard_language(void) {
    wizard_show("Language", "Select language");
    printf("1. Chinese (中文)\n");
    printf("2. English\n");
}

void wizard_language_zh(void) {
    strcpy(current_lang, "zh-CN");
    wizard_show("Chinese", "Chinese selected");
}

void wizard_welcome_zh(void) {
    wizard_show("Welcome", "Welcome to aide");
    printf("2 minutes setup\n");
}

void wizard_name_zh(void) {
    wizard_show("Name", "Set my name");
    printf("Options: Wang Er Gou, Xiao Ai, Assistant\n");
}

void wizard_wake_word_zh(void) {
    wizard_show("Wake Word", "Set wake word");
    printf("Options: hello aide, hey assistant\n");
}

void wizard_api_key_zh(void) {
    wizard_show("API Key", "Set API key");
    printf("Get key from minimax.cn\n");
    printf("Or say 'skip'\n");
}

void wizard_output_mode_zh(void) {
    wizard_show("Output Mode", "Set detail level");
    printf("1. Simple  2. Normal  3. Detailed\n");
}

void wizard_complete_zh(void) {
    wizard_show("Done", "Setup complete!");
    printf("Wake: hello aide\n");
    printf("Name: Wang Er Gou\n");
    wizard_done = 1;
}

int wizard_run(void) {
    if (wizard_done) return 0;
    switch (current_step) {
        case WIZARD_LANGUAGE:
            wizard_language();
            wizard_language_zh();
            current_step = WIZARD_NAME;
            break;
        case WIZARD_NAME:
            wizard_welcome_zh();
            wizard_name_zh();
            current_step = WIZARD_WAKE_WORD;
            break;
        case WIZARD_WAKE_WORD:
            wizard_wake_word_zh();
            current_step = WIZARD_API_KEY;
            break;
        case WIZARD_API_KEY:
            wizard_api_key_zh();
            current_step = WIZARD_OUTPUT_MODE;
            break;
        case WIZARD_OUTPUT_MODE:
            wizard_output_mode_zh();
            current_step = WIZARD_COMPLETE;
            break;
        case WIZARD_COMPLETE:
            wizard_complete_zh();
            break;
    }
    return 0;
}
