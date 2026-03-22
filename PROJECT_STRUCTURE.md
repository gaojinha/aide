# 项目结构

## 目录说明

```
aide/
│
├── docs/                  # 项目文档
│   ├── SPEC.md           # 完整方案（第一章-第九章）
│   ├── SPEC_CHAPTER1.md  # 第一章：愿景与目标
│   ├── SPEC_CHAPTER2.md  # 第二章：用户需求
│   ├── SPEC_CHAPTER3.md  # 第三章：场景规划
│   ├── SPEC_CHAPTER4.md  # 第四章：底层架构
│   ├── SPEC_CHAPTER5.md  # 第五章：技术选型
│   ├── SPEC_CHAPTER6.md  # 第六章：无瓶颈设计
│   ├── SPEC_CHAPTER7.md  # 第七章：商业模式
│   ├── SPEC_CHAPTER8.md  # 第八章：发展路线（待细化）
│   └── SPEC_CHAPTER9.md  # 第九章：关键创新（待细化）
│
├── src/                   # 源代码
│   ├── kernel/           # 内核层
│   │   └── linux-config  # Linux内核配置
│   │
│   ├── runtime/          # 运行时层
│   │   ├── systemd      # 服务管理
│   │   ├── dbus        # IPC
│   │   └── driver      # 驱动管理
│   │
│   ├── services/        # 系统服务层
│   │   ├── telephony   # 电话服务
│   │   ├── network     # 网络服务
│   │   ├── storage     # 存储服务
│   │   ├── security    # 安全服务
│   │   └── sensor      # 传感器服务
│   │
│   ├── api/             # API抽象层
│   │   ├── phone-api   # 电话API
│   │   ├── message-api # 消息API
│   │   ├── sensor-api  # 传感器API
│   │   └── ai-api      # AI能力API
│   │
│   ├── ai/              # AI能力层
│   │   ├── stt         # 语音识别
│   │   ├── tts         # 语音合成
│   │   ├── llm         # 大模型推理
│   │   ├── memory     # 记忆系统
│   │   └── nlu        # 自然语言理解
│   │
│   └── apps/            # 场景应用
│       ├── assistant   # 核心助理
│       ├── life        # 生活场景
│       ├── work        # 工作场景
│       └── health      # 健康场景
│
├── config/               # 配置文件
│   ├── default/         # 默认配置
│   └── variants/        # 变体配置
│
├── scripts/             # 脚本工具
│   ├── build/          # 构建脚本
│   ├── deploy/         # 部署脚本
│   └── tools/          # 工具脚本
│
├── tests/               # 测试用例
│   ├── unit/           # 单元测试
│   ├── integration/    # 集成测试
│   └── scenario/       # 场景测试
│
└── tools/               # 工具链
    ├── docker/         # Docker环境
    └── ci/            # CI/CD配置
```

## 开发阶段

### 阶段一：最小可运行系统（0-3月）
- [ ] Linux内核配置
- [ ] 基础驱动
- [ ] 通话服务
- [ ] 最小桌面

### 阶段二：核心能力（3-6月）
- [ ] 短信/网络
- [ ] 基础AI
- [ ] 语音交互

### 阶段三：能力开放（6-9月）
- [ ] API层
- [ ] 文档
- [ ] SDK

### 阶段四：生态初现（9-12月）
- [ ] 适配器
- [ ] 示例应用

---

**项目状态：🟡 规划中**
