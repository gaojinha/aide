# 快速开始

## 环境要求

- Ubuntu 24.04+
- ARM交叉编译工具链

## 快速构建

```bash
# 克隆项目
git clone https://gitcode.com/gaojinha/aide.git
cd aide

# 编译
mkdir build && cd build
cmake ..
make
```

## 运行

```bash
# 在x86上测试
./ai_assistant

# 交叉编译后拷贝到RK3568开发板运行
```

## 示例代码

```bash
# 编译示例
cd examples
gcc -o hello 01_hello.c ../src/core/system.c -I../include
```

## 模块列表

| 模块 | 路径 | 说明 |
|------|------|------|
| 核心 | src/core/ | 系统/进程/IPC/存储/安全 |
| AI | src/ai/ | 人格/记忆/语音/模型 |
| 驱动 | src/driver/ | 摄像头/传感器/网络 |
| 应用 | src/app/ | 电话/消息/设置 |
| UI | src/ui/ | 界面 |
| 协议 | src/core/protocol/ | HTTP/WebSocket |

## 下一步

1. 阅读 [API文档](./API.md)
2. 阅读 [架构图](./ARCH.md)
3. 阅读 [技术方案](./SPEC.md)
