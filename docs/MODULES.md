# aide 模块说明

## 核心模块 (src/core/)

| 模块 | 文件 | 功能 |
|------|------|------|
| 日志 | log.c | 分级日志输出 |
| 配置 | config.c | JSON配置管理 |
| 进程 | process.c | 进程管理 |
| 安全 | security.c | AES256/X25519加密 |
| 用户认证 | auth.c | 密码/指纹认证 |
| 权限管理 | acl.c | ACL访问控制 |
| 安全启动 | secureboot.c | 启动链验证 |
| 安全存储 | secure_storage.c | 加密分区 |
| 防火墙 | firewall.c | iptables规则 |
| 错误处理 | error/error.c | 错误码定义 |
| NTP | ntp/ntp.c | 时间同步 |
| OTA | ota/ota.c | 远程升级 |
| IPC | ipc/ipc.c | 进程间通信 |

## 驱动模块 (src/driver/)

| 模块 | 文件 | 功能 |
|------|------|------|
| GPIO | gpio/gpio.c | LED/按键控制 |
| 传感器 | sensor/sensor.c | 12种传感器 |
| WiFi | wifi/wifi.c | WiFi管理 |
| 蓝牙 | bluetooth/bluetooth.c | 蓝牙管理 |
| 音频 | audio/audio.c | 播放/录音 |
| 视频 | video/video.c | FFmpeg播放 |
| 电源 | power/power.c | 电池/充电 |
| 红外 | ir/ir.c | 遥控解码 |

## 应用模块 (src/app/)

| 模块 | 文件 | 功能 |
|------|------|------|
| 设置向导 | settings/wizard.c | 首次设置 |
| 推送 | push/push.c | 消息推送 |
| 调度 | scheduler/scheduler.c | 定时任务 |
| 消息 | messaging/messaging.c | 消息管理 |
| 电话 | phone/phone.c | VoIP通话 |
| 文件管理 | filemanager/file_manager.c | 文件操作 |

## AI模块 (src/ai/)

| 模块 | 文件 | 功能 |
|------|------|------|
| 语音 | speech/speech.c | STT/TTS |
| NLP | nlp/nlp.c | 自然语言处理 |
| 视觉 | vision/vision.c | 人脸/物体识别 |
| 模型 | model/model.c | AI模型调用 |
| 人格 | personality.c | 人格配置 |
| 记忆 | memory/memory.c | 对话记忆 |

## 头文件 (include/)

| 文件 | 说明 |
|------|------|
| ai_assistant.h | 主头文件 |
| wizard.h | 向导API |
| log.h | 日志API |
| config.h | 配置API |
| ntp.h | NTP API |
| ota.h | OTA API |
| security.h | 安全API |
| auth.h | 认证API |
| acl.h | 权限API |
| error.h | 错误码API |
