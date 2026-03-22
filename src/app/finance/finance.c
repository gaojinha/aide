#include <stdio.h>
#include <string.h>

typedef struct { char type[32]; int amount; char desc[64]; } record_t;
static record_t records[50];
static int record_count = 0;

void finance_account_init(void) {
    printf("[Finance] Account initialized\n");
    printf("  活期: ¥150,000\n");
    printf("  理财: ¥50,000\n");
    printf("  基金: ¥30,000\n");
}

void finance_record_init(void) {
    printf("[Finance] Records initialized\n");
    record_t *r = &records[record_count++];
    strcpy(r->type, "支出"); r->amount = -50; strcpy(r->desc, "午餐");
    r = &records[record_count++];
    strcpy(r->type, "收入"); r->amount = 10000; strcpy(r->desc, "工资");
    r = &records[record_count++];
    strcpy(r->type, "支出"); r->amount = -200; strcpy(r->desc, "购物");
    printf("  Records: %d\n", record_count);
}

void finance_records_list(void) {
    printf("\n=== Finance Records (%d) ===\n", record_count);
    int total = 0;
    for (int i = 0; i < record_count; i++) {
        printf("%d. %s: %+d (%s)\n", i+1, records[i].type, records[i].amount, records[i].desc);
        total += records[i].amount;
    }
    printf("--------------------------\n");
    printf("本月合计: %+d\n", total);
    printf("==========================\n\n");
}

void finance_transfer(void) { printf("[Finance] 转账功能\n"); }
void finance_payment(void) { printf("[Finance] 缴费功能: 电费/水费/燃气\n"); }
void finance_invest(void) { printf("[Finance] 投资: 基金+理财\n"); }
void finance_insurance(void) { printf("[Finance] 保险: 2份保单\n"); }

void finance_dashboard(void) {
    printf("\n");
    printf("╔═══════════════════════════════════════╗\n");
    printf("║        Finance Dashboard             ║\n");
    printf("╠═══════════════════════════════════════╣\n");
    printf("║ 💰 总资产: ¥230,000                 ║\n");
    printf("║ 📈 本月收入: ¥10,000                ║\n");
    printf("║ 📉 本月支出: ¥2,500                 ║\n");
    printf("║ 💳 可用额度: ¥50,000                ║\n");
    printf("║ 🏦 理财收益: ¥500/月                ║\n");
    printf("╚═══════════════════════════════════════╝\n\n");
}

void finance_test(void) {
    printf("\n=== Finance Test ===\n");
    finance_account_init();
    finance_record_init(); finance_records_list();
    finance_transfer(); finance_payment();
    finance_invest(); finance_insurance();
    finance_dashboard();
    printf("==================\n\n");
}
