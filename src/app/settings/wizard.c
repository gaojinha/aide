/**
 * 首次设置向导
 */

#include <stdio.h>
#include <string.h>

typedef enum {
    WIZARD_WELCOME,
    WIZARD_NAME,
    WIZARD_WAKE_WORD,
    WIZARD_API_KEY,
    WIZARD_OUTPUT_MODE,
    WIZARD_COMPLETE
} wizard_step_t;

static wizard_step_t current_step = WIZARD_WELCOME;
static int wizard_done = 0;

int wizard_is_done(void) { return wizard_done; }
void wizard_reset(void) { current_step = WIZARD_WELCOME; wizard_done = 0; }

void wizard_welcome(void) {
    printf("\n");
    printf("╔════════════════════════════════════════╗\n");
    printf("║        🎉 Welcome to aide! 🎉         ║\n");
    printf("╚════════════════════════════════════════╝\n");
    printf("\n");
    printf("I'll guide you through the setup.\n");
    printf("About 2 minutes.\n");
    printf("\n");
    printf("Ready? (say 'start' or press enter)\n");
}

void wizard_ask_name(void) {
    printf("\n");
    printf("📝 Step 1: Your Name\n");
    printf("What's my name? e.g.:\n");
    printf("  - Wang Er Gou\n");
    printf("  - Xiao Ai\n");
    printf("  - Assistant\n");
    printf("\n");
    printf("Tell me: [speak or type]\n");
}

void wizard_ask_wake_word(void) {
    printf("\n");
    printf("🔔 Step 2: Wake Word\n");
    printf("Say this to wake me:\n");
    printf("  - hello aide\n");
    printf("  - hey assistant\n");
    printf("  - xiao ai\n");
    printf("\n");
    printf("Set it: [speak or type]\n");
}

void wizard_ask_api_key(void) {
    printf("\n");
    printf("🔑 Step 3: API Key\n");
    printf("To make me smarter, set API Key.\n");
    printf("\n");
    printf("Recommended: MiniMax API\n");
    printf("1. Visit https://platform.minimax.cn\n");
    printf("2. Register and get API Key\n");
    printf("3. Tell me the Key\n");
    printf("\n");
    printf("Or say 'skip' to continue without:\n");
}

void wizard_ask_output_mode(void) {
    printf("\n");
    printf("📊 Step 4: Response Detail\n");
    printf("How detailed should I respond?\n");
    printf("\n");
    printf("  1. Simple   - short: 'ok', 'sunny'\n");
    printf("  2. Normal   - conversational\n");
    printf("  3. Detailed - with data and suggestions\n");
    printf("\n");
    printf("Choose 1/2/3: [speak or type]\n");
}

void wizard_complete(void) {
    printf("\n");
    printf("╔════════════════════════════════════════╗\n");
    printf("║        ✅ Setup Complete! 🎉          ║\n");
    printf("╚════════════════════════════════════════╝\n");
    printf("\n");
    printf("Remember:\n");
    printf("  Wake: hello aide\n");
    printf("  Name: Wang Er Gou\n");
    printf("\n");
    printf("Try: say 'hello aide'\n");
    printf("\n");
    wizard_done = 1;
}

int wizard_run(void) {
    if (wizard_done) return 0;
    
    switch (current_step) {
        case WIZARD_WELCOME:
            wizard_welcome();
            current_step = WIZARD_NAME;
            break;
        case WIZARD_NAME:
            wizard_ask_name();
            current_step = WIZARD_WAKE_WORD;
            break;
        case WIZARD_WAKE_WORD:
            wizard_ask_wake_word();
            current_step = WIZARD_API_KEY;
            break;
        case WIZARD_API_KEY:
            wizard_ask_api_key();
            current_step = WIZARD_OUTPUT_MODE;
            break;
        case WIZARD_OUTPUT_MODE:
            wizard_ask_output_mode();
            current_step = WIZARD_COMPLETE;
            break;
        case WIZARD_COMPLETE:
            wizard_complete();
            break;
    }
    return 0;
}
