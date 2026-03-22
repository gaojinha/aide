# aide - AI Assistant

基于RK3568的AI助手设备固件。

## 功能特性

### 核心能力
- 语音交互 (STT/TTS)
- 自然语言理解
- 人脸识别
- 物体检测
- 人格对话

### 安全
- 安全启动
- 加密存储
- 用户认证
- ACL权限控制
- 防火墙

### 驱动
- WiFi/蓝牙
- 音频播放/录音
- 视频播放
- 传感器 (12种)
- GPIO控制

## 快速开始

```bash
# 编译
cd aide
mkdir build && cd build
cmake ..
make

# 运行
./aide

# 交叉编译 (RK3568)
../scripts/build-rk3568.sh

# 安装服务
sudo ../scripts/install.sh
sudo systemctl start aide
```

## 文档

- [快速开始](docs/QUICKSTART.md)
- [API文档](docs/API.md)
- [命令列表](docs/COMMANDS.md)
- [架构说明](docs/ARCH.md)
- [模块说明](docs/MODULES.md)
- [驱动API](docs/DRIVER_API.md)
- [配置说明](docs/CONFIG.md)
- [设备树](device-tree/PINOUT.md)

## 版本

当前版本: **v0.1.0**

## 仓库

https://gitcode.com/gaojinha/aide.git

## 许可

MIT License
