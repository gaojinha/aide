FROM ubuntu:22.04

LABEL maintainer="aide@project.com"
LABEL version="0.1.0"

# 安装依赖
RUN apt-get update && apt-get install -y \
    cmake \
    build-essential \
    && rm -rf /var/lib/apt/lists/*

# 创建工作目录
WORKDIR /app

# 复制源码
COPY . .

# 编译
RUN mkdir -p build && \
    cd build && \
    cmake .. && \
    make -j$(nproc)

# 创建非root用户
RUN useradd -m -s /bin/bash aide
USER aide

# 运行
CMD ["./build/aide"]
