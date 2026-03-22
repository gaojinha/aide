# API文档

## 系统API

### ai_system_init
```c
int ai_system_init(void);
```
初始化系统。

**返回值**: 0成功，-1失败

### ai_system_start
```c
int ai_system_start(void);
```
启动系统。

**返回值**: 0成功，-1失败

### ai_system_stop
```c
int ai_system_stop(void);
```
停止系统。

**返回值**: 0成功，-1失败

### ai_system_get_state
```c
system_state_t ai_system_get_state(void);
```
获取系统状态。

**返回值**: 系统状态

---

## 进程管理API

### process_create
```c
int process_create(const char *name, void (*entry)(void));
```
创建新进程。

**参数**:
- name: 进程名称
- entry: 入口函数

**返回值**: 0成功，-1失败

### process_kill
```c
int process_kill(pid_t pid);
```
终止进程。

**参数**: pid: 进程ID

**返回值**: 0成功，-1失败

---

## 存储API

### storage_write
```c
int storage_write(const char *key, const void *data, size_t len);
```
写入数据。

### storage_read
```c
int storage_read(const char *key, void *data, size_t len);
```
读取数据。

### storage_delete
```c
int storage_delete(const char *key);
```
删除数据。

---

## 安全API

### security_encrypt
```c
int security_encrypt(const void *in, void *out, size_t len);
```
加密数据。

### security_decrypt
```c
int security_decrypt(const void *in, void *out, size_t len);
```
解密数据。

---

## NLP API

### nlp_understand
```c
int nlp_understand(const char *text, void *intent);
```
理解文本意图。

### nlp_generate
```c
int nlp_generate(const void *intent, char *response);
```
生成回复。

---

## 语音API

### speech_stt
```c
int speech_stt(const void *audio, char *text);
```
语音转文字。

### speech_tts
```c
int speech_tts(const char *text, void *audio);
```
文字转语音。

---

## 视觉API

### vision_detect
```c
int vision_detect(const void *frame, void *result);
```
目标检测。

### vision_recognize
```c
int vision_recognize(const void *face, void *id);
```
人脸识别。

---

## 网络API

### network_connect
```c
int network_connect(const char *ssid, const char *pass);
```
连接WiFi。

### network_send
```c
int network_send(const void *data, size_t len);
```
发送数据。

### network_recv
```c
int network_recv(void *data, size_t len);
```
接收数据。
