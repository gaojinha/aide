/**
 * 首次设置向导 - 支持多语言
 */

#include <stdio.h>
#include <string.h>

typedef enum {
    WIZARD_LANGUAGE,     // 第一步：选择语言
    WIZARD_NAME,
    WIZARD_WAKE_WORD,
    WIZARD_API_KEY,
    WIZARD_OUTPUT_MODE,
    WIZARD_COMPLETE
} wizard_step_t;

static wizard_step_t current_step = WIZARD_LANGUAGE;
static int wizard_done = 0;
static char current_lang[16] = "zh-CN";  // 默认中文

// 语音播报
void wizard_speak(const char *text) {
    printf("[Voice] 🔊 %s\n", text);
}

int wizard_is_done(void) { return wizard_done; }
void wizard_reset(void) { current_step = WIZARD_LANGUAGE; wizard_done = 0; }

// 界面显示
void wizard_show(const char *title, const char *voice_text) {
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║ %-36s║\n", title);
    printf("╚════════════════════════════════════════╝\n");
    if (voice_text) wizard_speak(voice_text);
}

// 第一步：选择语言
void wizard_language(void) {
    wizard_show("🌐 Language / 语言选择",
        "你好！请选择你熟悉的语言。");
    
    printf("Choose your language / 请选择语言:\n");
    printf("\n");
    printf("  1. 中文 (Chinese)\n");
    printf("  2. English (English)\n");
    printf("\n");
    printf("Input / 输入: 1 或 2\n");
    wizard_speak("请说中文或英文");
}

void wizard_language_zh(void) {
    strcpy(current_lang, "zh-CN");
    wizard_show("✅ 已选择中文",
        "好的，我们用中文继续。");
}

void wizard_language_en(void) {
    strcpy(current_lang, "en-US");
    wizard_show("✅ English Selected",
        "OK, let's continue in English.");
}

// 中文界面
void wizard_welcome_zh(void) {
    wizard_show("🎉 欢迎使用 aide!", 
        "你好！欢迎使用 aide，我来帮你完成设置。");
    printf("大约需要 2 分钟。\n");
    printf("准备好了吗？（说"开始"或按回车）\n");
}

void wizard_name_zh(void) {
    wizard_show("📝 第一步：设置名字",
        "第一步，设置我的名字。");
    printf("你想叫我什么名字？比如：\n");
    printf("  • 王二狗\n");
    printf("  • 小爱\n");
    printf("  • 助手\n");
    printf("\n请告诉我：[直接说或打字]\n");
    wizard_speak("请告诉我你想叫我什么名字");
}

void wizard_wake_word_zh(void) {
    wizard_show("🔔 第二步：设置唤醒词",
        "第二步，设置唤醒词。");
    printf("每次叫我时需要说：\n");
    printf("  • 你好 aide\n");
    printf("  • 嘿助手\n");
    printf("  • 小爱同学\n");
    printf("\n请设置：[直接说或打字]\n");
    wizard_speak("以后叫我的时候就说这个词");
}

void wizard_api_key_zh(void) {
    wizard_show("🔑 第三步：设置API Key",
        "第三步，设置API密钥。");
    printf("为了让我更聪明，需要设置API Key。\n");
    printf("\n推荐使用 MiniMax API：\n");
    printf("1. 访问 https://platform.minimax.cn\n");
    printf("2. 注册账号并获取 API Key\n");
    printf("3. 告诉我 Key\n");
    printf("\n如果没有，可以说"跳过"以后再设置。\n");
    wizard_speak("可以让我更聪明，也可以先跳过");
}

void wizard_output_mode_zh(void) {
    wizard_show("📊 第四步：设置回答详细程度",
        "第四步，设置回答详细程度。");
    printf("我回答问题时，要多详细？\n");
    printf("\n");
    printf("  1. 简单   - 简短回应，如"好的"、"晴天"\n");
    printf("  2. 适中   - 正常对话\n");
    printf("  3. 详尽   - 详细解释\n");
    printf("\n请选择 1/2/3：[直接说或打字]\n");
    wizard_speak("我回答问题时，要多详细？简单、适中、还是详尽？");
}

void wizard_complete_zh(void) {
    wizard_show("✅ 设置完成！",
        "设置完成！我是你的AI助理了！");
    printf("\n记住我们的约定：\n");
    printf("  唤醒词：你好 aide\n");
    printf("  名字：王二狗\n");
    printf("\n现在试试对我说："你好 aide"\n");
    wizard_speak("设置完成！我是你的AI助理了！");
}

// 英文界面
void wizard_welcome_en(void) {
    wizard_show("🎉 Welcome to aide!", 
        "Hello! Welcome to aide. Let me help you set up.");
    printf("About 2 minutes.\n");
    printf("Ready? (say 'start' or press enter)\n");
}

void wizard_name_en(void) {
    wizard_show("📝 Step 1: Your Name",
        "Step 1, set my name.");
    printf("What's my name? e.g.:\n");
    printf("  - Wang Er Gou\n");
    printf("  - Xiao Ai\n");
    printf("  - Assistant\n");
    printf("\nTell me: [speak or type]\n");
    wizard_speak("Tell me what to call me");
}

void wizard_wake_word_en(void) {
    wizard_show("🔔 Step 2: Wake Word",
        "Step 2, set wake word.");
    printf("Say this to wake me:\n");
    printf("  - hello aide\n");
    printf("  - hey assistant\n");
    printf("  - xiao ai\n");
    printf("\nSet it: [speak or type]\n");
    wizard_speak("Say this to wake me up");
}

void wizard_api_key_en(void) {
    wizard_show("🔑 Step 3: API Key",
        "Step 3, set API key.");
    printf("To make me smarter, set API Key.\n");
    printf("\nRecommended: MiniMax API\n");
    printf("1. Visit https://platform.minimax.cn\n");
    printf("2. Register and get API Key\n");
    printf("3. Tell me the Key\n");
    printf("\nOr say 'skip' to continue without:\n");
    wizard_speak("Or skip for now");
}

void wizard_output_mode_en(void) {
    wizard_show("📊 Step 4: Response Detail",
        "Step 4, set response detail.");
    printf("How detailed should I respond?\n");
    printf("\n");
    printf("  1. Simple   - short: 'ok', 'sunny'\n");
    printf("  2. Normal   - conversational\n");
    printf("  3. Detailed - with data and suggestions\n");
    printf("\nChoose 1/2/3: [speak or type]\n");
    wizard_speak("How detailed should I respond?");
}

void wizard_complete_en(void) {
    wizard_show("✅ Setup Complete!",
        "Setup complete! I'm your AI assistant now!");
    printf("\nRemember:\n");
    printf("  Wake: hello aide\n");
    printf("  Name: Wang Er Gou\n");
    printf("\nTry: say 'hello aide'\n");
    wizard_speak("Setup complete!");
}

// 根据语言选择对应函数
int wizard_run(void) {
    if (wizard_done) return 0;
    
    switch (current_step) {
        case WIZARD_LANGUAGE:
            wizard_language();
            // 模拟选择中文
            wizard_language_zh();
            current_step = WIZARD_NAME;
            break;
        case WIZARD_NAME:
            if (strcmp(current_lang, "zh-CN") == 0) {
                wizard_welcome_zh();
                wizard_name_zh();
            } else {
                wizard_welcome_en();
                wizard_name_en();
            }
            current_step = WIZARD_WAKE_WORD;
            break;
        case WIZARD_WAKE_WORD:
            if (strcmp(current_lang, "zh-CN") == 0) {
                wizard_wake_word_zh();
            } else {
                wizard_wake_word_en();
            }
            current_step = WIZARD_API_KEY;
            break;
        case WIZARD_API_KEY:
            if (strcmp(current_lang, "zh-CN") == 0) {
                wizard_api_key_zh();
            } else {
                wizard_api_key_en();
            }
            current_step = WIZARD_OUTPUT_MODE;
            break;
        case WIZARD_OUTPUT_MODE:
            if (strcmp(current_lang, "zh-CN") == 0) {
                wizard_output_mode_zh();
            } else {
                wizard_output_mode_en();
            }
            current_step = WIZARD_COMPLETE;
            break;
        case WIZARD_COMPLETE:
            if (strcmp(current_lang, "zh-CN") == 0) {
                wizard_complete_zh();
            } else {
                wizard_complete_en();
            }
            wizard_done = 1;
            break;
    }
    return 0;
}
