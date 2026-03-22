# aide SDK

AI手机助手 Python SDK

## 安装

```bash
pip install aide-sdk
```

## 快速开始

```python
from aide_sdk import AideClient

client = AideClient(base_url="http://localhost:8080")
result = client.chat("你好")
print(result)
```
## API

### 对话
```python
client.chat("你好")
```

### 语音合成
```python
client.tts("你好")
```

### 技能调用
```python
client.skills.weather("北京")
client.skills.play_music(song="演员")
```
