#!/bin/bash
# 自动构建脚本

set -e

echo "=== aide 构建脚本 ==="

# 检查工具
command -v aarch64-linux-gnu-gcc >/dev/null 2>&1 || { 
    echo "错误: 需要安装 ARM 工具链"
    echo "运行: sudo apt install gcc-aarch64-linux-gnu"
    exit 1
}

# 创建目录
mkdir -p build
cd build

# 配置
echo "[1/3] 配置..."
cmake ..

# 编译
echo "[2/3] 编译..."
make -j$(nproc)

# 输出
echo "[3/3] 完成!"
echo "输出: build/ai_assistant"
ls -lh ai_assistant
