"""
Health Module - 健康管理
"""

from typing import Optional
from .client import AideClient

class Health:
    """健康管理"""
    
    def __init__(self, client: AideClient):
        self.client = client
    
    def get_status(self) -> Dict:
        """获取健康状态"""
        return self.client.get_health()
    
    def get_steps(self) -> Dict:
        """获取步数"""
        data = self.get_status()
        return {"steps": data.get("steps", 0), "goal": data.get("steps_goal", 10000)}
    
    def get_sleep(self) -> Dict:
        """获取睡眠数据"""
        data = self.get_status()
        return data.get("sleep", {})
    
    def get_heart_rate(self) -> Dict:
        """获取心率"""
        data = self.get_status()
        return {"heart_rate": data.get("heart_rate", 0)}
    
    def get_diet(self) -> Dict:
        """获取饮食记录"""
        data = self.get_status()
        return data.get("diet", {})
