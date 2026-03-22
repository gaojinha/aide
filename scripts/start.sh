#!/bin/bash

APP_DIR="/home/gao/aide"
BIN_DIR="$APP_DIR/build"

echo "Starting aide..."

# 检查二进制
if [ ! -f "$BIN_DIR/aide" ]; then
    echo "Error: aide binary not found"
    exit 1
fi

# 检查权限
if [ ! -x "$BIN_DIR/aide" ]; then
    chmod +x "$BIN_DIR/aide"
fi

# 启动
cd $BIN_DIR
./aide
