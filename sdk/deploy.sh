#!/bin/bash
# AIDE 部署脚本 - 交叉编译并部署到 RK3568 开发板

# 开发板配置
BOARD_IP="${BOARD_IP:-192.168.1.100}"
BOARD_USER="${BOARD_USER:-root}"
BOARD_PATH="${BOARD_PATH:-/root/aide}"

echo "=== AIDE 部署脚本 ==="
echo "目标: $BOARD_USER@$BOARD_IP"
echo ""

# 1. 交叉编译
echo "[1/4] 交叉编译..."
mkdir -p build-arm64
cd build-arm64
cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake/aarch64-linux-gnu.cmake
make -j4
cd ..

# 2. 创建部署包
echo "[2/4] 创建部署包..."
mkdir -p deploy
cp build-arm64/aide deploy/
cp -r src app config deploy/ 2>/dev/null || true
tar -czvf aide-deploy.tar.gz deploy/

# 3. 上传到开发板
echo "[3/4] 上传到开发板..."
ssh $BOARD_USER@$BOARD_IP "mkdir -p $BOARD_PATH"
scp aide-deploy.tar.gz $BOARD_USER@$BOARD_IP:$BOARD_PATH/

# 4. 解压运行
echo "[4/4] 远程部署..."
ssh $BOARD_USER@$BOARD_IP << 'SSH'
cd $BOARD_PATH
tar -xzvf aide-deploy.tar.gz
cd deploy
chmod +x aide
./aide
SSH

echo "=== 部署完成 ==="
