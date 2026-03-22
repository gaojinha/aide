#include <stdio.h>
#include <time.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_BOOKS 50
#define MAX_NOTES 50

// 单词
typedef struct {
    char word[64];
    char meaning[256];
    char example[256];
    int mastered;  // 0:新学 1:复习中 2:已掌握
} word_t;

// 书籍
typedef struct {
    char title[128];
    char author[64];
    int pages;
    int read_pages;
} book_t;

// 笔记
typedef struct {
    char title[128];
    char content[512];
    char tags[128];
    time_t created;
} note_t;

static word_t words[MAX_WORDS];
static int word_count = 0;
static book_t books[MAX_BOOKS];
static int book_count = 0;
static note_t notes[MAX_NOTES];
static int note_count = 0;

// 背单词
void study_words_init(void) {
    printf("[Study] Words initialized\n");
    
    word_t *w = &words[word_count++];
    strcpy(w->word, "artificial");
    strcpy(w->meaning, "人工的，人造的");
    strcpy(w->example, "AI is artificial intelligence");
    w->mastered = 0;
    
    w = &words[word_count++];
    strcpy(w->word, "intelligence");
    strcpy(w->meaning, "智力，智能");
    strcpy(w->example, "Artificial intelligence");
    w->mastered = 1;
    
    w = &words[word_count++];
    strcpy(w->word, "algorithm");
    strcpy(w->meaning, "算法");
    strcpy(w->example, "This algorithm is efficient");
    w->mastered = 2;
    
    printf("  Words: %d\n", word_count);
}

// 单词列表
void study_words_list(void) {
    const char *status_name[] = {"新学", "复习中", "已掌握"};
    
    printf("\n=== Words (%d) ===\n", word_count);
    for (int i = 0; i < word_count; i++) {
        printf("%d. [%s] %s\n", i+1, status_name[words[i].mastered], words[i].word);
        printf("   %s\n", words[i].meaning);
    }
    printf("=====================\n\n");
}

// 背单词测试
void study_words_test(void) {
    printf("\n=== Word Test ===\n");
    printf("Q1: algorithm 是什么意思?\n");
    printf("A: 算法 ✨\n");
    printf("Q2: intelligence 是什么意思?\n");
    printf("A: 智力 ✨\n");
    printf("Correct: 2/2\n\n");
}

// 阅读
void study_books_init(void) {
    printf("[Study] Books initialized\n");
    
    book_t *b = &books[book_count++];
    strcpy(b->title, "《人工智能导论》");
    strcpy(b->author, "张三");
    b->pages = 300;
    b->read_pages = 120;
    
    b = &books[book_count++];
    strcpy(b->title, "《Python编程》");
    strcpy(b->author, "李四");
    b->pages = 500;
    b->read_pages = 500;
    
    printf("  Books: %d\n", book_count);
}

// 书籍列表
void study_books_list(void) {
    printf("\n=== Books (%d) ===\n", book_count);
    for (int i = 0; i < book_count; i++) {
        int progress = books[i].read_pages * 100 / books[i].pages;
        printf("%d. %s\n", i+1, books[i].title);
        printf("   作者: %s\n", books[i].author);
        printf("   进度: %d%% (%d/%d页)\n", 
            progress, books[i].read_pages, books[i].pages);
    }
    printf("=====================\n\n");
}

// 笔记
void study_notes_init(void) {
    printf("[Study] Notes initialized\n");
    
    note_t *n = &notes[note_count++];
    strcpy(n->title, "AI核心概念");
    strcpy(n->content, "机器学习是AI的一个分支...");
    strcpy(n->tags, "AI,机器学习");
    
    n = &notes[note_count++];
    strcpy(n->title, "Python技巧");
    strcpy(n->content, "列表推导式: [x for x in list]");
    strcpy(n->tags, "Python,编程");
    
    printf("  Notes: %d\n", note_count);
}

// 笔记列表
void study_notes_list(void) {
    printf("\n=== Notes (%d) ===\n", note_count);
    for (int i = 0; i < note_count; i++) {
        printf("%d. %s\n", i+1, notes[i].title);
        printf("   %s\n", notes[i].content);
        printf("   Tags: %s\n", notes[i].tags);
    }
    printf("=====================\n\n");
}

// 错题本
void study_errors_init(void) {
    printf("[Study] Error book initialized\n");
    printf("  Errors: 5\n");
    printf("  Categories: 数学,英语,编程\n");
}

void study_errors_list(void) {
    printf("\n=== Error Book ===\n");
    printf("1. [数学] 求导公式忘记了\n");
    printf("2. [英语] 单词拼写错误\n");
    printf("3. [编程] 数组越界\n");
    printf("4. [数学] 几何定理\n");
    printf("5. [英语] 语法错误\n");
    printf("======================\n\n");
}

// 考试
void study_exam_init(void) {
    printf("[Study] Exam mode\n");
    printf("  Next exam: 2026-04-15\n");
    printf("  Days left: 24\n");
}

void study_exam_plan(void) {
    printf("\n=== Exam Plan ===\n");
    printf("日期       科目     内容\n");
    printf("2026-03-23 数学     概率论\n");
    printf("2026-03-25 英语     单词复习\n");
    printf("2026-03-27 编程     算法题\n");
    printf("2026-03-29 数学     线性代数\n");
    printf("2026-03-31 英语     阅读理解\n");
    printf("====================\n\n");
}

// 学习统计
void study_stats(void) {
    printf("\n");
    printf("╔═══════════════════════════════════════╗\n");
    printf("║         Learning Stats              ║\n");
    printf("╠═══════════════════════════════════════╣\n");
    printf("║ 📚 Words:   %d (mastered: %d)         ║\n", word_count, 1);
    printf("║ 📖 Books:   %d (progress: 60%%)        ║\n", book_count);
    printf("║ 📝 Notes:   %d                          ║\n", note_count);
    printf("║ ❌ Errors:  5                          ║\n");
    printf("║ 📅 Streak:  7 days                    ║\n");
    printf("║ ⏱️  Today:   2 hours                  ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");
}

// 测试
void study_test(void) {
    printf("\n=== Study Test ===\n");
    
    study_words_init();
    study_words_list();
    study_words_test();
    
    study_books_init();
    study_books_list();
    
    study_notes_init();
    study_notes_list();
    
    study_errors_init();
    study_errors_list();
    
    study_exam_init();
    study_exam_plan();
    
    study_stats();
    
    printf("==================\n\n");
}
