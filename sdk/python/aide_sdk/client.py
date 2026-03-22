"""
Aide Client - HTTP 客户端
"""

import requests
from typing import Optional, Dict, Any

class AideClient:
    """Aide SDK 客户端"""
    
    def __init__(
        self,
        base_url: str = "http://localhost:8080",
        api_key: Optional[str] = None,
        timeout: int = 30
    ):
        """
        初始化客户端
        
        Args:
            base_url: Aide API 服务器地址
            api_key: API 密钥
            timeout: 请求超时时间(秒)
        """
        self.base_url = base_url.rstrip("/")
        self.api_key = api_key
        self.timeout = timeout
        self.session = requests.Session()
        
        if api_key:
            self.session.headers["Authorization"] = f"Bearer {api_key}"
    
    def _request(self, method: str, path: str, **kwargs) -> Dict[str, Any]:
        """发送 HTTP 请求"""
        url = f"{self.base_url}{path}"
        kwargs.setdefault("timeout", self.timeout)
        
        response = self.session.request(method, url, **kwargs)
        response.raise_for_status()
        return response.json()
    
    def get(self, path: str, **kwargs) -> Dict[str, Any]:
        return self._request("GET", path, **kwargs)
    
    def post(self, path: str, **kwargs) -> Dict[str, Any]:
        return self._request("POST", path, **kwargs)
    
    def put(self, path: str, **kwargs) -> Dict[str, Any]:
        return self._request("PUT", path, **kwargs)
    
    def delete(self, path: str, **kwargs) -> Dict[str, Any]:
        return self._request("DELETE", path, **kwargs)
    
    # ========== 系统状态 ==========
    def get_status(self) -> Dict[str, Any]:
        """获取系统状态"""
        return self.get("/api/v1/status")
    
    # ========== 语音 ==========
    def voice_push(self, device: str, text: str) -> Dict[str, Any]:
        """推送语音到设备"""
        return self.post("/api/v1/voice", json={
            "device": device,
            "text": text
        })
    
    def stt(self, audio_path: str) -> Dict[str, Any]:
        """语音转文字"""
        with open(audio_path, "rb") as f:
            return self.post("/api/v1/stt", files={"audio": f})
    
    def tts(self, text: str, voice: str = "zh-CN-XiaoxiaoNeural") -> Dict[str, Any]:
        """文字转语音"""
        return self.post("/api/v1/tts", json={
            "text": text,
            "voice": voice
        })
    
    # ========== 消息推送 ==========
    def send_notification(self, device: str, title: str, body: str) -> Dict[str, Any]:
        """发送通知"""
        return self.post("/api/v1/notification", json={
            "device": device,
            "title": title,
            "body": body
        })
    
    # ========== 远程控制 ==========
    def remote_control(self, device: str, action: str) -> Dict[str, Any]:
        """远程控制设备"""
        return self.post("/api/v1/control", json={
            "device": device,
            "action": action
        })
    
    # ========== 传感器 ==========
    def get_sensors(self) -> Dict[str, Any]:
        """获取传感器数据"""
        return self.get("/api/v1/sensors")
    
    # ========== 摄像头 ==========
    def camera_snap(self, device: str = "default") -> Dict[str, Any]:
        """拍照"""
        return self.post("/api/v1/camera/snap", json={
            "device": device
        })
    
    # ========== 文件 ==========
    def list_files(self, path: str = "/") -> Dict[str, Any]:
        """列出文件"""
        return self.get(f"/api/v1/files?path={path}")
    
    def upload_file(self, local_path: str, remote_path: str) -> Dict[str, Any]:
        """上传文件"""
        with open(local_path, "rb") as f:
            return self.post("/api/v1/files/upload", files={"file": f}, data={
                "path": remote_path
            })
    
    def download_file(self, remote_path: str, local_path: str) -> Dict[str, Any]:
        """下载文件"""
        response = self.get(f"/api/v1/files/download?path={remote_path}")
        with open(local_path, "wb") as f:
            f.write(response.content)
        return {"status": "ok", "path": local_path}
    
    # ========== 设置 ==========
    def get_settings(self) -> Dict[str, Any]:
        """获取设置"""
        return self.get("/api/v1/settings")
    
    def update_settings(self, **kwargs) -> Dict[str, Any]:
        """更新设置"""
        return self.put("/api/v1/settings", json=kwargs)
    
    # ========== 对话 ==========
    def chat(self, message: str, context: Optional[Dict] = None) -> Dict[str, Any]:
        """发送对话消息"""
        data = {"message": message}
        if context:
            data["context"] = context
        return self.post("/api/v1/chat", json=data)
    
    # ========== 技能 ==========
    def list_skills(self) -> Dict[str, Any]:
        """列出技能"""
        return self.get("/api/v1/skills")
    
    def call_skill(self, skill_name: str, params: Dict[str, Any] = None) -> Dict[str, Any]:
        """调用技能"""
        return self.post(f"/api/v1/skills/{skill_name}", json=params or {})
    
    # ========== 场景 ==========
    def list_scenes(self) -> Dict[str, Any]:
        """列出场景"""
        return self.get("/api/v1/scenes")
    
    def switch_scene(self, scene_name: str) -> Dict[str, Any]:
        """切换场景"""
        return self.post("/api/v1/scenes/switch", json={"scene": scene_name})
    
    # ========== 健康 ==========
    def get_health(self) -> Dict[str, Any]:
        """获取健康数据"""
        return self.get("/api/v1/health")
    
    # ========== 设备管理 ==========
    def list_devices(self) -> Dict[str, Any]:
        """列出设备"""
        return self.get("/api/v1/devices")
    
    def find_device(self, device_id: str) -> Dict[str, Any]:
        """查找设备"""
        return self.post(f"/api/v1/devices/{device_id}/find", json={})
    
    # ========== 关闭连接 ==========
    def close(self):
        """关闭会话"""
        self.session.close()
    
    def __enter__(self):
        return self
    
    def __exit__(self, exc_type, exc_val, exc_tb):
        self.close()
