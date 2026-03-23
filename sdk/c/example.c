/**
 * AIDE SDK C Example
 */

#include <aide/aide.h>
#include <stdio.h>

int main() {
    // 创建客户端
    aide_client_t *client = aide_client_new("http://localhost:8080", NULL);
    if (!client) {
        printf("Failed to create client\n");
        return 1;
    }
    
    // 设置超时
    aide_client_set_timeout(client, 10000);
    
    // 获取状态
    char buf[4096];
    int ret = aide_get_status(client, buf, sizeof(buf));
    if (ret == 200) {
        printf("Status: %s\n", buf);
    }
    
    // 对话
    ret = aide_chat(client, "你好", buf, sizeof(buf));
    if (ret == 200) {
        printf("Reply: %s\n", buf);
    }
    
    // 语音合成
    aide_tts(client, "你好", "zh-CN-XiaoxiaoNeural");
    
    // 设置
    aide_set_setting(client, "volume", "80");
    
    // 清理
    aide_client_free(client);
    
    printf("Done!\n");
    return 0;
}
