# AIDE SDK - JavaScript

AI手机助手 JavaScript/TypeScript SDK

## 安装

```bash
npm install aide-sdk
```

## 使用

```javascript
const AideClient = require('aide-sdk');

const client = new AideClient({
    baseURL: 'http://192.168.1.100:8080',
    apiKey: 'your-api-key'
});

// 对话
const reply = await client.chat('你好');
console.log(reply);

// 语音合成
await client.tts('你好');

// 技能
await client.weather('北京');
await client.playMusic('演员');

// 设置
await client.updateSettings({ volume: 80 });
```

## TypeScript

```typescript
import AideClient from 'aide-sdk';

const client = new AideClient({ baseURL: 'http://localhost:8080' });
```
