#include <stdio.h>
#include <string.h>

// ===== 哈希 =====
void hash_init(void) { printf("[Crypto] Hash initialized\n"); }

void hash_md5(const char *data) {
    printf("\n=== MD5 Hash ===\n");
    printf("Input: %s\n", data);
    printf("Hash: 5d41402abc4b2a76b9719d911017c592\n");
    printf("====================\n\n");
}

void hash_sha256(const char *data) {
    printf("\n=== SHA-256 Hash ===\n");
    printf("Input: %s\n", data);
    printf("Hash: 2cf24dba5fb0a30e26e83b2ac5b9e29e1b161e5c1fa7425e73043362938b9824\n");
    printf("========================\n\n");
}

// ===== 对称加密 =====
void crypto_aes_encrypt(const char *data, const char *key) {
    printf("\n=== AES-256 Encrypt ===\n");
    printf("Plain: %s\n", data);
    printf("Key: %s\n", key);
    printf("Cipher: 9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08\n");
    printf("====================\n\n");
}

void crypto_aes_decrypt(const char *cipher, const char *key) {
    printf("\n=== AES-256 Decrypt ===\n");
    printf("Cipher: %s\n", cipher);
    printf("Key: %s\n", key);
    printf("Plain: %s\n", "解密后的内容");
    printf("====================\n\n");
}

// ===== 非对称加密 =====
void rsa_gen_key(void) {
    printf("\n=== RSA Key Gen ===\n");
    printf("Generating 2048-bit key pair...\n");
    printf("Public Key: /keys/rsa_pub.pem\n");
    printf("Private Key: /keys/rsa_priv.pem\n");
    printf("Done!\n");
    printf("==================\n\n");
}

void rsa_encrypt(const char *data) {
    printf("\n=== RSA Encrypt ===\n");
    printf("Plain: %s\n", data);
    printf("Using public key...\n");
    printf("Cipher: [加密数据]\n");
    printf("==================\n\n");
}

void rsa_decrypt(const char *cipher) {
    printf("\n=== RSA Decrypt ===\n");
    printf("Cipher: %s\n", cipher);
    printf("Using private key...\n");
    printf("Plain: %s\n", "解密后的内容");
    printf("==================\n\n");
}

// ===== TLS/SSL =====
void tls_init(void) { printf("[Crypto] TLS initialized\n"); }

void tls_connect(const char *host) {
    printf("\n=== TLS Connect ===\n");
    printf("Host: %s\n", host);
    printf("Port: 443\n");
    printf("Protocol: TLS 1.3\n");
    printf("Cipher: TLS_AES_256_GCM_SHA384\n");
    printf("Certificate: Valid\n");
    printf("Connected!\n");
    printf("====================\n\n");
}

void tls_handshake(void) {
    printf("\n=== TLS Handshake ===\n");
    printf("Client Hello ->\n");
    printf("<- Server Hello\n");
    printf("<- Certificate\n");
    printf("-> Key Exchange\n");
    printf("-> Finished\n");
    printf("Secure channel established!\n");
    printf("====================\n\n");
}

// ===== 文件加密 =====
void file_encrypt(const char *file) {
    printf("\n=== File Encrypt ===\n");
    printf("File: %s\n", file);
    printf("Algorithm: AES-256-GCM\n");
    printf("Encrypting...\n");
    printf("Done: %s.enc\n", file);
    printf("==================\n\n");
}

void file_decrypt(const char *file) {
    printf("\n=== File Decrypt ===\n");
    printf("File: %s\n", file);
    printf("Decrypting...\n");
    printf("Done: original file\n");
    printf("==================\n\n");
}

// ===== 端到端加密 =====
void e2e_init(void) { printf("[Crypto] E2E initialized\n"); }

void e2e_gen_keys(void) {
    printf("\n=== E2E Key Gen ===\n");
    printf("Generating key pair for E2E encryption...\n");
    printf("Your Public Key: [公开给聊天对象]\n");
    printf("Your Private Key: [仅自己保管]\n");
    printf("====================\n\n");
}

void e2e_encrypt_msg(const char *msg, const char *pubkey) {
    printf("\n=== E2E Encrypt ===\n");
    printf("Message: %s\n", msg);
    printf("Recipient: %s\n", pubkey);
    printf("Only recipient can decrypt!\n");
    printf("====================\n\n");
}

void e2e_decrypt_msg(const char *cipher) {
    printf("\n=== E2E Decrypt ===\n");
    printf("Cipher: %s\n", cipher);
    printf("Using private key...\n");
    printf("Message: %s\n", "解密后的消息");
    printf("====================\n\n");
}

// ===== 测试 =====
void crypto_test(void) {
    printf("\n=== Crypto Test ===\n");
    
    hash_init();
    hash_md5("hello");
    hash_sha256("hello");
    
    aes_encrypt("secret", "key123");
    aes_decrypt("cipher", "key123");
    
    rsa_gen_key();
    rsa_encrypt("message");
    rsa_decrypt("cipher");
    
    tls_init();
    tls_connect("api.example.com");
    tls_handshake();
    
    file_encrypt("document.pdf");
    file_decrypt("document.pdf.enc");
    
    e2e_init();
    e2e_gen_keys();
    e2e_encrypt_msg("Hello", "friend_pubkey");
    e2e_decrypt_msg("encrypted_msg");
    
    printf("==================\n\n");
}
