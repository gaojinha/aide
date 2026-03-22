"""
TTS Module - 语音合成
"""

from typing import Optional
from .client import AideClient

class TTS:
    """语音合成"""
    
    VOICES = {
        "zh-CN-XiaoxiaoNeural": "中文女声(晓晓)",
        "zh-CN-YunxiNeural": "中文男声(云希)",
        "zh-CN-YunyangNeural": "中文男声(云扬)",
        "en-US-JennyNeural": "英文女声(Jenny)",
        "en-US-GuyNeural": "英文男声(Guy)",
    }
    
    def __init__(self, client: AideClient):
        self.client = client
    
    def speak(self, text: str, voice: str = "zh-CN-XiaoxiaoNeural") -> Dict:
        """合成语音"""
        return self.client.tts(text, voice)
    
    def list_voices(self) -> list:
        """列出可用声音"""
        return [{"id": k, "name": v} for k, v in self.VOICES.items()]
