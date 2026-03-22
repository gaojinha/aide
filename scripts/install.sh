#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
APP_DIR="/home/gao/aide"

echo "Installing aide service..."

# 复制服务文件
sudo cp $SCRIPT_DIR/aide.service /etc/systemd/system/

# 重新加载
sudo systemctl daemon-reload

# 启用服务
sudo systemctl enable aide

echo "Done! Use:"
echo "  sudo systemctl start aide"
echo "  sudo systemctl stop aide"
echo "  sudo systemctl status aide"
