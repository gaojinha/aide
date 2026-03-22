/**
 * 示例6: 安全使用
 */

#include <stdio.h>
#include "security.h"

int main(void) {
    // 初始化安全
    security_init();
    
    // 加密数据
    char cipher[128], plain[128];
    size_t len;
    security_encrypt("敏感信息", cipher, &len);
    printf("加密后: %s\n", cipher);
    
    // 解密
    security_decrypt(cipher, plain);
    printf("解密后: %s\n", plain);
    
    // 哈希
    security_hash("password", cipher);
    printf("哈希: %s\n", cipher);
    
    // Token
    char token[128];
    security_generate_token("user1", token);
    printf("Token: %s\n", token);
    
    return 0;
}
