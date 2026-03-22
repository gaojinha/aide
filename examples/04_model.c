/**
 * 示例4: 大模型对话
 */

#include <stdio.h>
#include "local_model.h"

int main(void) {
    // 初始化模型
    model_init();
    
    // 加载本地模型
    model_load_local("/models/ai-assistant.bin");
    
    // 对话
    char response[512];
    model_infer_local("你好", response, 256);
    printf("AI: %s\n", response);
    
    // 云端对话
    model_infer_cloud("今天天气怎么样", response, 256);
    printf("AI(云端): %s\n", response);
    
    return 0;
}
