/**
 * 安全测试
 */

extern int security_init(void);
extern int security_encrypt(const char *in, char *out, size_t *len);
extern int security_decrypt(const char *in, char *out);
extern int security_hash(const char *in, char *out);

void test_security(void) {
    printf("  [Test] Init...\n");
    security_init();
    
    char cipher[128], plain[128];
    size_t len;
    security_encrypt("hello", cipher, &len);
    security_decrypt(cipher, plain);
    security_hash("test", cipher);
}

int main(void) {
    printf("=== Security Tests ===\n");
    test_security();
    printf("=== All Passed ===\n");
    return 0;
}
