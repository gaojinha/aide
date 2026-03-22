# AI Aide - 编译指南

## 环境要求

- Ubuntu 24.04+
- ARM交叉编译工具链: `gcc-aarch64-linux-gnu`

## 编译步骤

```bash
# 1. 进入项目目录
cd aide

# 2. 创建编译目录
mkdir build && cd build

# 3. 配置
cmake ..

# 4. 编译
make

# 5. 生成的二进制文件
# build/aide
```

## 目录结构

```
src/
├── main.c          # 主程序入口
├── core/           # 核心模块
│   └── system.c   # 系统管理
├── ai/             # AI模块
│   ├── nlp/        # 自然语言处理
│   ├── vision/     # 视觉
│   ├── speech/     # 语音
│   └── memory/      # 记忆
├── driver/         # 驱动
│   ├── camera/     # 摄像头
│   ├── sensor/     # 传感器
│   ├── display/    # 显示
│   └── network/    # 网络
├── app/            # 应用
│   ├── phone/      # 电话
│   ├── messaging/  # 消息
│   └── settings/   # 设置
└── ui/             # 界面
```

## 开发流程

1. 在 `src/` 目录添加代码
2. 重新 `make`
3. 拷贝 `build/aide` 到开发板
4. 在开发板上运行测试
