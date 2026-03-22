"""
Chat Module - 对话功能
"""

from typing import Optional, Dict, Any, List
from .client import AideClient

class Chat:
    """对话管理"""
    
    def __init__(self, client: AideClient):
        self.client = client
    
    def send(self, message: str, context: Optional[Dict] = None) -> Dict[str, Any]:
        """发送消息"""
        return self.client.chat(message, context)
    
    def send_with_history(
        self,
        message: str,
        history: List[Dict[str, str]]
    ) -> Dict[str, Any]:
        """带历史记录发送"""
        context = {"history": history}
        return self.client.chat(message, context)
    
    def stream(self, message: str):
        """流式响应 (需服务器支持)"""
        import sseclient
        import requests
        
        response = requests.post(
            f"{self.client.base_url}/api/v1/chat/stream",
            json={"message": message},
            stream=True
        )
        
        client = sseclient.SSEClient(response)
        for event in client.events():
            if event.data:
                yield event.data
