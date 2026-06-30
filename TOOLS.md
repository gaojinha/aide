# openclaw — TOOLS 定义与 schema

说明
- 本文件定义系统可调用的外部工具接口（Tool Adapters）。每个 tool schema 包括 description、inputs、outputs、safety 要求与示例调用。实现时后端需提供统一的 tool adapter 层，负责权限检查、retries 与幂等。

工具清单（主要）
1. auth.oauth_connect
2. calendar.find_availability
3. calendar.create_event
4. calendar.modify_event
5. email.list / email.get / email.compose_and_send
6. drive.upload
7. docs.search
8. notifier.send
9. storage.get_signed_url

示例 schema（JSON 风格）

```json
{
  "auth.oauth_connect": {
    "description": "开始 OAuth 流程并返回授权 URL",
    "inputs": {
      "provider": "string (google|microsoft)",
      "scopes": ["string"],
      "redirect_uri": "string",
      "state": "string"
    },
    "outputs": {
      "auth_url": "string"
    },
    "safety": {
      "expose_token": false
    }
  }
}
```

calendar.find_availability
```json
{
  "description": "查找用户在给定时间范围内的可用时段（考虑现有日程和工作时间）",
  "inputs": {
    "user_id": "string",
    "range_start": "ISO8601",
    "range_end": "ISO8601",
    "duration_minutes": "integer",
    "attendees": ["email"],
    "time_zone": "string",
    "preferences": {"earliest_hour": "int", "latest_hour": "int"}
  },
  "outputs": {
    "available_slots": [
      {"start": "ISO8601", "end": "ISO8601", "score": "number"}
    ],
    "conflicts": [
      {"event_id":"string","summary":"string","start":"ISO8601","end":"ISO8601"}
    ]
  },
  "safety": {
    "requires_confirmation_on_external_attendees": true
  }
}
```

calendar.create_event
```json
{
  "description": "在用户日历中创建事件并（可选）发送邀请",
  "inputs": {
    "user_id":"string",
    "calendar_id":"string",
    "title":"string",
    "start_time":"ISO8601",
    "end_time":"ISO8601",
    "attendees":["email"],
    "location":"string",
    "description":"string",
    "send_invitations":"boolean",
    "time_zone":"string"
  },
  "outputs": {
    "event_id":"string",
    "calendar_url":"string",
    "status":"success|failed",
    "warnings":["string"]
  },
  "safety": {
    "confirm_before_sending": true,
    "log_event": true
  }
}
```

email.compose_and_send
```json
{
  "description":"生成邮件草稿并可选自动发送",
  "inputs":{
    "user_id":"string",
    "to":["email"],
    "cc":["email"],
    "bcc":["email"],
    "subject":"string",
    "body":"string (markdown/html)",
    "attachments":["s3_url"],
    "auto_send":"boolean"
  },
  "outputs":{
    "draft_id":"string",
    "message_id":"string",
    "status":"draft|sent|failed"
  },
  "safety":{
    "requires_confirmation_if_external": true,
    "requires_confirmation_if_attachments": true
n  }
}
```

docs.search
```json
{
  "description":"对用户上传或索引的文档进行向量检索并返回片段与来源",
  "inputs":{
    "user_id":"string",
    "query":"string",
    "top_k":"integer"
  },
  "outputs":{
    "results":[
      {"doc_id":"string","snippet":"string","score":"number","source_url":"string"}
    ]
  },
  "safety":{
    "redact_sensitive": true
  }
}
```

notifier.send
```json
{
  "description":"发送通知（可支持多通道）",
  "inputs":{
    "user_id":"string",
    "channels":["email","slack","wechat","push"],
    "title":"string",
    "body":"string",
    "metadata":{"key":"value"},
    "priority":"low|normal|high"
  },
  "outputs":{
    "status":"sent|queued|failed",
    "channel_results":[{"channel":"string","status":"string","detail":"string"}]
  }
}
```

实现注意事项
- 幂等性：所有写操作（create_event, email.send, drive.upload）必须支持幂等 key（client_request_id）。  
- 重试策略：对 5xx 错误使用指数退避；对 4xx 明确抛出错误并回退到人工。  
- 日志与审计：每次工具调用需记录 context_id、agent_id、user_id、inputs（脱敏后）、outputs、timestamp。  
- 模拟模式（sandbox）：提供 sandbox 模式用于内测（不向真实服务发送请求，但返回模拟响应格式）。
