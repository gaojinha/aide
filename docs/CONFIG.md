# aide 配置文件说明

## 配置文件位置

- 默认配置: `config/default.json`
- 用户配置: `config/user.json`

## 配置项

### 系统配置
| 字段 | 类型 | 默认值 | 说明 |
|------|------|--------|------|
| version | string | "0.1.0" | 版本号 |
| log_level | string | "info" | 日志级别 |
| log_file | string | "/var/log/aide.log" | 日志文件 |

### 网络配置
| 字段 | 类型 | 默认值 | 说明 |
|------|------|--------|------|
| wifi.auto_connect | bool | true | WiFi自动连接 |
| wifi.saved_networks | array | [] | 保存的WiFi |
| bt.enabled | bool | true | 蓝牙启用 |

### 音频配置
| 字段 | 类型 | 默认值 | 说明 |
|------|------|--------|------|
| voice.volume | int | 70 | 音量 0-100 |
| voice.stt_engine | string | "whisper" | 语音识别引擎 |
| voice.tts_engine | string | "edge-tts" | 语音合成引擎 |
| voice.voice | string | "zh-CN-XiaoxiaoNeural" | 默认音色 |

### AI模型配置
| 字段 | 类型 | 默认值 | 说明 |
|------|------|--------|------|
| model.provider | string | "minimax" | 模型提供商 |
| model.name | string | "abab6.5s-chat" | 模型名称 |
| model.api_key | string | "" | API密钥 |
| model.endpoint | string | "" | 自定义端点 |

### 安全配置
| 字段 | 类型 | 默认值 | 说明 |
|------|------|--------|------|
| security.secure_boot | bool | true | 安全启动 |
| security.encryption | bool | true | 加密存储 |
| security.firewall | bool | true | 防火墙 |
| auth.default_user | string | "admin" | 默认用户 |
| auth.default_pass | string | "admin123" | 默认密码 |

### 电源配置
| 字段 | 类型 | 默认值 | 说明 |
|------|------|--------|------|
| power.battery_threshold | int | 20 | 低电量阈值 |
| power.suspend_timeout | int | 300 | 休眠超时(秒) |
| power.eco_mode | bool | false | 省电模式 |

## 使用示例

```json
{
  "version": "0.1.0",
  "system": {
    "log_level": "debug"
  },
  "voice": {
    "volume": 80,
    "voice": "zh-CN-YunxiNeural"
  },
  "model": {
    "provider": "minimax",
    "api_key": "sk-xxx"
  }
}
```
