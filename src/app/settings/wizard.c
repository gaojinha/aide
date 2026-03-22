/**
 * 首次设置向导 - 语音+界面同步
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

// 语音播报函数(外部定义)
extern void wizard_speak(const char *text);

int wizard_is_done(void) { return wizard_done; }
void wizard_reset(void) { current_step = WIZARD_WELCOME; wizard_done = 0; }

// 语音+界面同步
void wizard_show(const char *title, const char *voice_text) {
    // 界面显示
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║ %-36s║\n", title);
    printf("╚════════════════════════════════════════╝\n");
    
    // 语音播报
    if (voice_text) {
        wizard_speak(voice_text);
    }
}

void wizard_welcome(void) {
    wizard_show("🎉 Welcome to aide!", 
        "你好！欢迎使用 aide，我来帮你完成设置。");
    
    printf("\nI'll guide you through the setup.\n");
    printf("About 2 minutes.\n");
    printf("\nReady? (say 'start' or press enter)\n");
}

void wizard_ask_name(void) {
    wizard_show("📝 Step 1: Your Name",
        "第一步，设置我的名字。");
    
    printf("What's my name? e.g.:\n");
    printf("  - Wang Er Gou\n");
    printf("  - Xiao Ai\n");
    printf("  - Assistant\n");
    printf("\nTell me: [speak or type]\n");
    wizard_speak("请告诉我你想叫我什么名字");
}

void wizard_ask_wake_word(void) {
    wizard_show("🔔 Step 2: Wake Word",
        "第二步，设置唤醒词。");
    
    printf("Say this to wake me:\n");
    printf("  - hello aide\n");
    printf("  - hey assistant\n");
    printf("  - xiao ai\n");
    printf("\nSet it: [speak or type]\n");
    wizard_speak("以后叫我的时候就说这个词");
}

void wizard_ask_api_key(void) {
    wizard_show("🔑 Step 3: API Key",
        "第三步，设置API密钥。");
    
    printf("To make me smarter, set API Key.\n");
    printf("\nRecommended: MiniMax API\n");
    printf("1. Visit https://platform.minimax.cn\n");
    printf("2. Register and get API Key\n");
    printf("3. Tell me the Key\n");
    printf("\nOr say 'skip' to continue without:\n");
    wizard_speak("可以让我更聪明，也可以先跳过");
}

void wizard_ask_output_mode(void) {
    wizard_show("📊 Step 4: Response Detail",
        "第四步，设置回答详细程度。");
    
    printf("How detailed should I respond?\n");
    printf("\n");
    printf("  1. Simple   - short: 'ok', 'sunny'\n");
    printf("  2. Normal   - conversational\n");
    printf("  3. Detailed - with data and suggestions\n");
    printf("\nChoose 1/2/3: [speak or type]\n");
    wizard_speak("我回答问题时，要多详细？简单、适中、还是详尽？");
}

void wizard_complete(void) {
    wizard_show("✅ Setup Complete!",
        "设置完成！我是你的AI助理了！");
    
    printf("\nRemember:\n");
    printf("  Wake: hello aide\n");
    printf("  Name: Wang Er Gou\n");
    printf("\nTry: say 'hello aide'\n");
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
