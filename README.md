# aide项目

> 让AI成为每个人的专属秘书，让技术服务于每个人。

## 愿景

创造一个永远在线、永不拒绝、永远懂你的AI伙伴。

## 核心理念

我们不追随生态，让生态来追随我们。

## 核心特性

| 特性 | 说明 |
|------|------|
| 永远能 | 7×24在线，永不拒绝 |
| 永远在 | 随时可用，永不掉线 |
| 永远懂你 | 记住习惯，越用越懂你 |
| 人格化 | 有名字、性格、感情 |
| 主动感知 | 主动观察环境，主动关心 |
| 主动执行 | 不仅提醒，还会直接执行 |
| 安全 | 除了本人，谁也无法破解 |

## 技术架构

- **硬件**: RK3568 (4x Cortex-A55, 8GB RAM)
- **内核**: Linux 6.x
- **AI**: 本地大模型 + 云端增强
- **语音**: Whisper (STT) + Edge TTS

## 模块结构

```
src/
├── core/           # 核心模块
│   ├── system.c   # 系统管理
│   ├── process.c  # 进程管理
│   ├── ipc.c      # 进程间通信
│   ├── storage.c  # 存储管理
│   └── security.c # 安全模块
│
├── ai/             # AI模块
│   ├── nlp/       # 自然语言理解
│   ├── vision/     # 视觉识别
│   ├── speech/     # 语音处理
│   └── memory/     # 记忆系统
│
├── driver/         # 驱动模块
│   ├── camera/     # 摄像头
│   ├── sensor/     # 传感器
│   ├── display/    # 显示
│   └── network/    # 网络
│
├── app/            # 应用模块
│   ├── phone/      # 电话
│   ├── messaging/  # 消息
│   └── settings/   # 设置
│
└── ui/             # 界面模块
```

## 编译

```bash
# 创建编译目录
mkdir build && cd build

# 配置
cmake ..

# 编译
make

# 输出
# build/ai_assistant (ARM64)
```

## 测试

```bash
# 运行单元测试
cd build
ctest

# 或单独运行
./test_core
./test_ai
```

## 开发进度

| 阶段 | 状态 |
|------|------|
| 环境搭建 | ✅ 完成 |
| 代码框架 | ✅ 完成 |
| 最小系统 | ⏳ 等SDK |
| 通信能力 | ⏳ 待开始 |
| AI对话 | ⏳ 待开始 |
| 语音能力 | ⏳ 待开始 |

## 文档

- [技术方案](./docs/SPEC.md)
- [任务拆解](./docs/TASKS.md)
- [开发环境](./docs/ENV.md)
- [编译指南](./BUILD.md)

## Git仓库

https://gitcode.com/gaojinha/ai-assistant-project

## 许可证

MIT License - 详见 [LICENSE](./LICENSE) 文件
