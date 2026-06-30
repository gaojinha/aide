# openclaw — USER（用户模型与隐私/同意）

用户数据模型（JSON Schema 示例）
```json
{
  "user_id": "string",
  "display_name": "string",
  "primary_email": "string",
  "emails": ["string"],
  "time_zone": "string",
  "locale": "string",
  "preferences": {
    "meeting_length_default": "string",
    "work_hours": {"start":"HH:MM","end":"HH:MM"},
    "notification_channels": ["email","slack","wechat"],
    "auto_send_emails": false
  },
  "contacts": [
    {"name":"string","email":"string","type":"personal|work"}
  ],
  "connected_accounts": [
    {"provider":"google","scopes":["..."],"connected_at":"ISO8601"}
  ],
  "privacy_consent": {
    "accepted_at":"ISO8601",
    "version":"string"
  },
  "created_at":"ISO8601",
  "last_active":"ISO8601"
}
```

隐私与同意（Onboarding）
- 第一次使用需要明确获取：
  - 第三方账户连接权限说明（逐项列出 scope 与用途）
  - 数据保存与删除政策（保留期、导出途径）
  - 审计日志公开范围
- 提供“隐私中心”：用户能查看/导出/删除其长期记忆与连接的第三方账户。

权限范围（scope）
- 最小权限原则：仅申请必需权限。示例（Google）：
  - calendar.events.readonly → calendar.events.write（升级仅在需要时请求）
  - gmail.readonly → gmail.compose（对于发送邮件需要明确二次同意）
  - drive.file（仅访问由应用创建或用户明确上传的文件）

用户操作日志
- 对用户敏感操作（删除记忆、撤销发送）记录操作人、时间戳与变更摘要。

数据保留与删除策略
- 短期会话数据：默认保留 24 小时（可配置）
- 审计日志：90 天（脱敏后可延长）
- 长期记忆：用户可查看并按条删除；系统提供一键删除所有长期记忆的功能
- 导出：支持 JSON 导出（包含 metadata、连接账户、记忆摘要）

错误反馈与支持
- 提供便捷的“撤回最近操作（24h）”入口及一键联系 support 的通道
- 当发生误操作（例如误发邮件）时，展示补救步骤与人工介入联系方式
