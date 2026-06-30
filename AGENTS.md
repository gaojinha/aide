# openclaw — AGENTS 设计文档

概述
- 本文件定义 openclaw 系统中的 Agent（代理/角色）集合、职责、能力边界、触发条件与度量指标。目的是把“个人助理”拆解成可复用、可组合的子 Agent，以便逐步交付与测试。

Agents 列表（优先级从高到低）
1. assistant.core
   - 目的：总体对话协调器，负责意图识别、对话管理、策略决策与任务分配。
   - 能力：
     - 意图分类与槽位抽取（fast small model）
     - 任务规划（分解复杂请求）
     - 路由到相应工具或子 Agent
     - 负责安全策略检查（guardrail）
   - 使用的 Tools：email.compose_and_send、calendar.*、docs.search、notifier.send
   - Prompts（示例）：
     - System: 你是 openclaw 的对话协调器。接收用户指令并以 JSON 输出 {intent, slots, confidence, action_plan}。
   - KPI：意图识别准确率、任务成功率、平均处理时长

2. scheduler.agent
   - 目的：日程调度与空档查找。
   - 能力：
     - 查找可用时段（跨时区）
     - 冲突检测与建议
     - 创建/修改/取消事件并发送邀请
   - 使用的 Tools：calendar.find_availability、calendar.create_event
   - Prompts（示例）：
     - User intent -> scheduler: “安排 30 分钟专注时间，下周二上午”
   - KPI：调度成功率、用户确认次数（澄清轮次）

3. mail.agent
   - 目的：邮件读取、分类、草拟、发送与归档。
   - 能力：
     - 自动将邮件分为“重要/普通/垃圾”
     - 生成回复草稿并等待用户确认（或根据策略自动发送）
     - 处理附件并交给 drive.upload
   - 使用的 Tools：email.compose_and_send、drive.upload
   - Prompts（示例）：
     - System: 根据邮件内容生成 3 个可选回复草稿（正式/友好/简单）
   - KPI：草稿通过率（用户直接发送占比）、误分类率

4. docs.agent
   - 目的：文档检索、摘要与引用（RAG 服务）
   - 能力：
     - 向量检索、片段抽取、生成引用与置信度
     - 生成文档摘要与行动项
   - 使用的 Tools：docs.search
   - KPI：来源引用率、hallucination 指标（人工评估）

5. notifier.agent
   - 目的：消息投递（Push/Slack/WeChat/Email）。
   - 能力：
     - 根据用户偏好发��日程摘要、待办提醒、重要邮件摘要
   - 使用的 Tools：notifier.send
   - KPI：消息送达率、用户打开率

6. orchestrator.agent
   - 目的：负责多步骤事务的一致性（事务回滚、幂等、重试）。
   - 能力：
     - 管理排列组合任务、处理失败补偿、日志化每一步
   - KPI：复杂任务成功率、补偿动作次数

Agent 边界与交互原则
- 单一职责：每个 Agent 只做一类任务，复杂任务由 assistant.core 分解并协调。
- 明确确认：所有会导致外部真实操作（发送邮件、创建事件、删除文件）的 Agent 必须遵守安全策略（确认/二次审批/人工介入）。
- 可观测性：每次 Agent 行动需产生日志条目（inputs, outputs, tool_calls, timestamps）。

示例工作流：安排会议
1. 用户 → assistant.core：请求安排会议
2. assistant.core → scheduler.agent：提取时间偏好与与会者
3. scheduler.agent 使用 calendar.find_availability；若冲突则澄清
4. 用户确认后，scheduler.agent 调用 calendar.create_event（send_invitations=true）
5. orchestrator.agent 记录事务日志并报告结果给 assistant.core，assistant.core 把结果展示给用户

变更与扩展
- 可根据新需求新增 agent（例如 expense.agent、recruiting.agent）。
- 新 agent 必须提交能力声明（capabilities.json）并通过安全审核。
