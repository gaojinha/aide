#include <stdio.h>
#include <string.h>

void wizard_speak(const char *text) { printf("[Voice] 🔊 %s\n", text); }

void show(const char *title, const char *voice) {
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║ %-36s║\n", title);
    printf("╚════════════════════════════════════════╝\n");
    wizard_speak(voice);
    printf("\n");
}

int main() {
    printf("╔════════════════════════════════════════╗\n");
    printf("║        aide 向导每步界面展示          ║\n");
    printf("╚════════════════════════════════════════╝\n");
    
    // 步骤1: 语言
    show("🌐 第一步：选择语言 / Language", 
         "你好！请选择你熟悉的语言。");
    printf("  显示: 中文 / English 选项\n");
    
    // 步骤2: 欢迎
    show("🎉 欢迎使用 aide! / Welcome!",
         "你好！欢迎使用 aide，我来帮你完成设置。");
    printf("  显示: 2分钟设置说明\n");
    
    // 步骤3: 名字
    show("📝 第二步：设置名字 / Set Name",
         "第一步，设置我的名字。");
    printf("  显示: 王二狗、小爱、助手\n");
    
    // 步骤4: 唤醒词
    show("🔔 第三步：设置唤醒词 / Wake Word",
         "第二步，设置唤醒词。");
    printf("  显示: 你好 aide、嘿助手、小爱同学\n");
    
    // 步骤5: API Key
    show("🔑 第四步：设置API Key",
         "第三步，设置API密钥。");
    printf("  显示: MiniMax网址、输入框\n");
    
    // 步骤6: 输出模式
    show("📊 第五步：回答详细程度 / Response",
         "第四步，设置回答详细程度。");
    printf("  显示: 简单/适中/详尽 三档\n");
    
    // 步骤7: 完成
    show("✅ 设置完成! / Setup Complete!",
         "设置完成！我是你的AI助理了！");
    printf("  显示: 唤醒词、名字、试用提示\n");
    
    return 0;
}
