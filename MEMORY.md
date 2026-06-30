# openclaw — MEMORY（记忆设计与 API）

目标
- 提供短期会话上下文与长期个性化记忆的设计，保证隐私、可控与检索效率，支持 RAG 与个性化响应。

记忆层次
1. Short-term session (临时会话上下文)
   - Scope: 单次会话或 24 小时
   - 用途：保存最近对话、当前未完成任务、上下文窗口摘要
   - 存储位置：高速缓存（Redis）+ 元数据落盘（Postgres）
   - TTL: default 24h（可配置）

2. Long-term memory (长期记忆)
   - Scope: 持续性用户偏好、联系人、固定约定、长期项目要点
   - 用途：个性化、偏好、常用模板
   - 存储位置：向量数据库（Pinecone/Weaviate/Milvus）用于语义检索 + Postgres 存 metadata
   - Retention: 用户可管理（默认保留，用户可删除）

记忆 Schema（示例 JSON）
```json
{
  "memory_id": "string",
  "user_id": "string",
  "type": "preference|contact|note|meeting_summary|credentialless_fact",
  "content_text": "string",
  "embedding_id": "string",
  "metadata": {"source":"email|upload|manual","created_at":"ISO8601","tags":["projectA"]},
  "visibility": "private|shared",
  "ttl": "ISO8601|null"
}
```

向量化与 chunking 策略
- 文档切分：按语义段落或 N tokens（建议 200–500 tokens）切分并保留上下文 window overlap（10–20%）
- 嵌入模型：使用稳定可复现的 embedding 模型（例如 OpenAI text-embedding-3 或本地方案）
- 元数据保留：chunk -> {doc_id, chunk_index, text_snippet, created_at, source_url, tags}
- 检索 scoring：结合向量 score + metadata_boost（时间新近度、作者权重）

读取与写入 API（���例）
- POST /memory/add
  - body: {user_id, type, content, source}
  - 返回: {memory_id, status}
- POST /memory/search
  - body: {user_id, query, top_k}
  - 返回: [{memory_id, snippet, score, metadata}]
- DELETE /memory/{memory_id}
  - 权限: 仅用户本人或经授权的管理员
- GET /memory/export?user_id=
  - 导出用户所有长期记忆为 JSON（供导出/迁移）

访问控制与隐私
- 记忆默认 private；若分享须记录 share_log 并可撤销
- 敏感信息检测：在写入阶段对 content_text 做 PII 检测并标注/加密或拒绝
- 删除保证：DELETE 请求需要软删除（立即在检索层脱敏，后端异步彻底删除），并返回删除任务 id

一致性与可回溯
- 每次记忆写入记录 write_trace（trace_id, agent_id, user_confirmed）
- 记忆版本化：支持 snapshot 与 rollback（用户操作历史）

保全与合规
- 提供用户控制接口：查看、删除、导出、下载
- 审计日志：记录访问 memory 的 agent 与时间，保留 90 天
```
