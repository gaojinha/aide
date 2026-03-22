#!/bin/bash
# 部署到开发板

set -e

if [ -z "$1" ]; then
    echo "用法: ./deploy.sh <开发板IP>"
    exit 1
fi

TARGET=$1
BUILD_DIR="./build"

echo "部署到 $TARGET ..."

# 复制二进制
scp $BUILD_DIR/ai_assistant root@$TARGET:/usr/local/bin/

# 复制配置文件
scp -r ./config root@$TARGET:/etc/ai_assistant/

echo "部署完成"
echo "在开发板上运行: /usr/local/bin/ai_assistant"
