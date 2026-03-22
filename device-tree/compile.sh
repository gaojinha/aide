#!/bin/bash

# 设备树编译脚本

DTOOL=/usr/bin/dtc
DTB_OUT="aide-rk3568.dtb"

echo "Compiling Device Tree..."

if [ ! -f "aide-rk3568.dts" ]; then
    echo "Error: aide-rk3568.dts not found"
    exit 1
fi

# 编译 DTS -> DTB
$DTOOL -I dts -O dtb -o $DTB_OUT aide-rk3568.dts

if [ $? -eq 0 ]; then
    echo "Success: $DTB_OUT"
    ls -lh $DTB_OUT
else
    echo "Error: Compilation failed"
    exit 1
fi

echo ""
echo "Usage:"
echo "  Copy to boot: scp $DTB_OUT root@<device>:/boot/"
echo "  Or via U-Boot: tftp 0x00000000 $DTB_OUT"
