# AIDE SDK - C Library

AI手机助手 C 语言 SDK

## 安装

```bash
cd sdk/c
mkdir build && cd build
cmake ..
make
sudo make install
```

## 使用

```c
#include <aide/aide.h>

int main() {
    aide_client_t *client = aide_client_new("http://localhost:8080", NULL);
    
    // 对话
    char buf[4096];
    aide_chat(client, "你好", buf, sizeof(buf));
    printf("%s\n", buf);
    
    aide_client_free(client);
    return 0;
}
```

## 编译

```bash
gcc -o demo demo.c -laide -lcurl
```
