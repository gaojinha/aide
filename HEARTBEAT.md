# openclaw — HEARTBEAT（健康检查与可观测）

目标
- 定义服务存活检测、关键指标、报警阈值及自动化自愈策略，保证个人助理在用户期望的 SLA 下稳定运行。

健康检查端点（示例）
- /health/liveness — 返回 200 表示进程存活
- /health/readiness — 返回 200 表示服务已就绪，可处理请求（包括依赖检测）
- /health/deps — 返回第三方依赖状态（calendar API, email API, vector DB, LLM endpoint）

依赖检测（readiness）
- 检查项：
  - LLM endpoint reachable & latency < 3s
  - Vector DB reachable & query_time < 500ms
  - OAuth providers connectivity (token refresh check)
  - Object storage (S3) write/read sample
- 每项应返回 {status: ok|fail, last_checked: ISO8601, detail: string}

指标（Metrics）
- 基本：
  - request_rate (RPS)
  - error_rate (%)
  - p95_latency (ms)
  - tool_call_success_rate (%)
- 业务：
  - task_success_rate (最终完成率)
  - daily_active_users
  - avg_tasks_per_user
- 安全：
  - blocked_actions_count (per day)
  - manual_approvals_pending

报警策略（示例）
- LLM 请求失败率 > 5% 且持续 5 分钟 → P1 警报（PagerDuty）
- Vector DB 查询延迟 p95 > 1s → P2 警报（Slack）
- tool_call_success_rate < 90% → P1（影响任务执行）
- 高风险操作误阻断率（误阻断/总阻断）> 10% → SRE + Product Review

自动化自愈
- 对 transient network errors：自动重试（指数退避）；超过阈值启用降级模式（只生成草稿不发送）
- 对依赖中断：切换到备用 endpoint 或返回 degraded mode 说明给用户

日志与追踪
- 分布式追踪（trace_id）贯穿用户请求、assistant.core、agent、tool adapter
- 审计日志与监控日志分离（审计保留更长周期）
- 每次外部写操作含 client_request_id 以便查询与回滚

SLA 建议
- 可用性目标：99.9%（月度）
- 支付/关键业务需更高 SLA（视经营模式）
