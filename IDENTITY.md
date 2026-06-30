# openclaw — IDENTITY（服务与账号配置）

服务概述
- service_name: openclaw-assistant
- environment: dev / staging / prod
- default_locale: zh-CN
- default_tone: professional, concise

认证与凭证管理
- OAuth 客户端（示例）
  - google:
    - client_id: <GOOGLE_CLIENT_ID>
    - client_secret: <encrypted in KMS>
    - redirect_uris: ["https://yourdomain.com/auth/google/callback"]
  - microsoft:
    - client_id: <MS_CLIENT_ID>
    - client_secret: <encrypted>
- 服务账号（后端）
  - vault_path: secret/openclaw/service_account
  - KMS: 使用云 KMS（AWS KMS / GCP KMS / Azure KeyVault）存储加密密钥
- API Key 轮换策略
  - rotate_every: 90 days
  - rotation_workflow: create new key → switch consumers → revoke old key

角色与权限（RBAC）
- admin: 全权限（审计访问、策略修改、部署权限）
- ops: 部署与监控（无用户数据导出权限）
- dev: 开发与测试（访问沙箱数据）
- auditor: 审计日志读取（脱敏数据）
- user: 仅能管理自己的账户与偏好

品牌与外显
- product_display_name: OpenClaw 助手
- legal: 显示隐私政策与服务条款链接在第一次 OAuth 同意前
- support_contact: support@yourdomain.com

默认设置（用户未配置时）
- time_zone: UTC
- work_hours: 09:00-18:00 (Mon-Fri)
- meeting_length_default: 30m
- confirm_external_actions: true

可审计的身份变更
- 记录以下事件：
  - 用户连接/断开第三方账户
  - 权限 scope 变更
  - 高风险操作的批准/拒绝记录
