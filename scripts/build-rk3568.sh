#!/bin/bash

# RK3568 交叉编译脚本

export CROSS_PREFIX=aarch64-linux-gnu-
export CC=${CROSS_PREFIX}gcc
export CXX=${CROSS_PREFIX}g++

BUILD_DIR="build-rk3568"

echo "Building for RK3568..."

mkdir -p $BUILD_DIR
cd $BUILD_DIR

cmake .. \
    -DCMAKE_C_COMPILER=$CC \
    -DCMAKE_CXX_COMPILER=$CXX \
    -DCMAKE_BUILD_TYPE=Release

make -j$(nproc)

echo "Output: $BUILD_DIR/aide"
echo "Copy to device: scp $BUILD_DIR/aide root@<device-ip>:/usr/local/bin/"
