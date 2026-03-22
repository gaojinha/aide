#include <stdio.h>
#include <string.h>

// ===== 背单词 =====
void lang_words_init(void) { printf("[Language] Words initialized\n"); }
void lang_words_list(void) {
    printf("\n=== Words (50) ===\n");
    printf("1. hello - 你好\n");
    printf("2. world - 世界\n");
    printf("3. artificial - 人工的\n");
    printf("4. intelligence - 智能\n");
    printf("5. algorithm - 算法\n");
    printf("=====================\n\n");
}
void lang_words_test(void) {
    printf("\n=== Word Test ===\n");
    printf("Q: algorithm 意思?\n");
    printf("A: 算法 ✨\n");
    printf("正确: 1/1\n");
    printf("================\n\n");
}

// ===== 口语练习 =====
void lang_speak_init(void) { printf("[Language] Speaking initialized\n"); }
void lang_speak_practice(const char *topic) {
    printf("\n=== Speaking: %s ===\n", topic);
    printf("Topic: 自我介绍\n");
    printf("请朗读以下内容:\n");
    printf("Hello, my name is Wang. I am from China.\n");
    printf("\n评分: 85分\n");
    printf("发音: 良好\n");
    printf("语调: 自然\n");
    printf("================\n\n");
}
void lang_speak_recognize(void) {
    printf("\n=== Speech Recognition ===\n");
    printf("请说话...\n");
    printf("识别结果: 我想去吃饭\n");
    printf("置信度: 98%%\n");
    printf("======================\n\n");
}

// ===== 发音纠正 =====
void lang_pronounce_init(void) { printf("[Language] Pronounce initialized\n"); }
void lang_pronounce_correct(const char *word) {
    printf("\n=== Pronounce: %s ===\n", word);
    printf("单词: algorithm\n");
    printf("正确: /ˈælɡərɪðm/\n");
    printf("你的: /ˈɑːlɡərɪðm/\n");
    printf("\n纠正: 首音æ不是ɑː\n");
    printf("练习: 多听多跟读\n");
    printf("====================\n\n");
}
void lang_pronounce_demo(void) {
    printf("\n=== Pronounce Demo ===\n");
    printf("点击播放正确发音\n");
    printf("播放: algorithm.mp3\n");
    printf("====================\n\n");
}

// ===== 翻译 =====
void lang_translate_init(void) { printf("[Language] Translate initialized\n"); }
void lang_translate_cn2en(const char *text) {
    printf("\n=== CN -> EN ===\n");
    printf("原文: %s\n", text);
    printf("译文: I want to eat rice\n");
    printf("====================\n\n");
}
void lang_translate_en2cn(const char *text) {
    printf("\n=== EN -> CN ===\n");
    printf("原文: %s\n", text);
    printf("译文: 我想去吃饭\n");
    printf("====================\n\n");
}

// ===== 场景对话 =====
void lang_dialog_init(void) { printf("[Language] Dialog initialized\n"); }
void lang_dialog_scenario(const char *scene) {
    printf("\n=== Dialog: %s ===\n", scene);
    printf("场景: 餐厅点餐\n");
    printf("\nA: What would you like?\n");
    printf("B: I would like some rice and vegetables.\n");
    printf("A: Anything to drink?\n");
    printf("B: A cup of coffee, please.\n");
    printf("====================\n\n");
}

// ===== 测试 =====
void language_test(void) {
    printf("\n=== Language Test ===\n");
    
    lang_words_init(); lang_words_list(); lang_words_test();
    lang_speak_init(); lang_speak_practice("自我介绍"); lang_speak_recognize();
    lang_pronounce_init(); lang_pronounce_correct("algorithm"); lang_pronounce_demo();
    lang_translate_init(); lang_translate_cn2en("我想去吃饭");
    lang_dialog_init(); lang_dialog_scenario("餐厅");
    
    printf("==================\n\n");
}
