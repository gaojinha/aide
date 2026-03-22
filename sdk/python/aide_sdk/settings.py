"""
Settings Module - 设置管理
"""

from typing import Optional, Dict, Any
from .client import AideClient

class Settings:
    """设置管理"""
    
    def __init__(self, client: AideClient):
        self.client = client
    
    def get(self) -> Dict[str, Any]:
        """获取所有设置"""
        return self.client.get_settings()
    
    def update(self, **kwargs) -> Dict[str, Any]:
        """更新设置"""
        return self.client.update_settings(**kwargs)
    
    # 常用设置快捷方法
    def set_language(self, lang: str) -> Dict[str, Any]:
        """设置语言"""
        return self.update(language=lang)
    
    def set_volume(self, volume: int) -> Dict[str, Any]:
        """设置音量 (0-100)"""
        return self.update(volume=volume)
    
    def set_brightness(self, brightness: int) -> Dict[str, Any]:
        """设置亮度 (0-100)"""
        return self.update(brightness=brightness)
    
    def set_api_key(self, api_key: str) -> Dict[str, Any]:
        """设置 API Key"""
        return self.update(api_key=api_key)
    
    def set_wake_word(self, wake_word: str) -> Dict[str, Any]:
        """设置唤醒词"""
        return self.update(wake_word=wake_word)
    
    def set_model(self, model: str) -> Dict[str, Any]:
        """设置模型"""
        return self.update(model=model)
