# 开发环境配置

## 当前开发机

| 项目 | 当前状态 |
|------|----------|
| 系统 | Ubuntu 24.04 |
| 架构 | x86_64 |
| GCC | 13.3.0 ✅ |
| Make | 4.3 ✅ |
| Python | 3.12 ✅ |
| ARM工具链 | ✅ 已安装 |

## 需要安装

### 1. RK3568 SDK (待获取)

从瑞芯微官网下载：
- 地址: https://www.rockchip.com.cn/
- 提取密码: (待获取)

### 2. 串口驱动

```bash
sudo apt install -y screen minicom
```

### 3. 网络工具

```bash
sudo apt install -y nfs-kernel-server tftp-hpa
```

### 4. 其他开发工具

```bash
sudo apt install -y build-essential git curl wget
sudo apt install -y libssl-dev libffi-dev python3-dev
```

## 开发流程

```
1. 在电脑(Ubuntu)上用ARM工具链编译
2. 通过网络(TFTP/NFS)传到开发板
3. 在开发板上运行测试
```

## 验证安装

```bash
# 验证ARM工具链
aarch64-linux-gnu-gcc --version

# 查看开发板IP
# 通过路由器后台或串口查看

# 连接开发板串口
screen /dev/ttyUSB0 115200
```

## 下一步

1. 获取RK3568开发板
2. 获取SDK
3. 搭建开发环境
