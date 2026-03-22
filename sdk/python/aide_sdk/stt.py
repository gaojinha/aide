"""
STT Module - 语音识别
"""

from typing import Optional
from .client import AideClient

class STT:
    """语音识别"""
    
    def __init__(self, client: AideClient):
        self.client = client
    
    def recognize(self, audio_path: str) -> Dict:
        """识别音频文件"""
        return self.client.stt(audio_path)
    
    def recognize_stream(self, audio_stream) -> Dict:
        """识别音频流"""
        files = {"audio": audio_stream}
        import requests
        response = requests.post(
            f"{self.client.base_url}/api/v1/stt/stream",
            files=files,
            timeout=self.client.timeout
        )
        return response.json()
