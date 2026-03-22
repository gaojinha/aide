"""
Skills Module - 技能管理
"""

from typing import Optional, Dict, Any
from .client import AideClient

class Skills:
    """技能管理"""
    
    def __init__(self, client: AideClient):
        self.client = client
    
    def list(self) -> Dict[str, Any]:
        """列出所有技能"""
        return self.client.list_skills()
    
    def call(self, skill_name: str, **params) -> Dict[str, Any]:
        """调用技能"""
        return self.client.call_skill(skill_name, params)
    
    # 常用技能快捷方法
    def weather(self, city: str = "北京") -> Dict[str, Any]:
        """天气查询"""
        return self.call("weather", city=city)
    
    def play_music(self, song: str = None, artist: str = None) -> Dict[str, Any]:
        """播放音乐"""
        return self.call("music_play", song=song, artist=artist)
    
    def set_alarm(self, time: str, message: str = "") -> Dict[str, Any]:
        """设置闹钟"""
        return self.call("alarm", time=time, message=message)
    
    def tell_story(self, topic: str = None) -> Dict[str, Any]:
        """讲故事"""
        return self.call("story", topic=topic)
    
    def translate(self, text: str, to_lang: str = "en") -> Dict[str, Any]:
        """翻译"""
        return self.call("translate", text=text, to=to_lang)
    
    def calculate(self, expression: str) -> Dict[str, Any]:
        """计算"""
        return self.call("math", expr=expression)
