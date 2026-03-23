/**
 * AIDE SDK - JavaScript/TypeScript
 * AI Phone Assistant SDK
 */

const axios = require('axios');

class AideClient {
    constructor(options = {}) {
        this.baseURL = options.baseURL || 'http://localhost:8080';
        this.apiKey = options.apiKey || null;
        this.timeout = options.timeout || 30000;
        
        this.client = axios.create({
            baseURL: this.baseURL,
            timeout: this.timeout,
            headers: {
                'Content-Type': 'application/json',
                ...(this.apiKey ? { 'Authorization': `Bearer ${this.apiKey}` } : {})
            }
        });
    }
    
    // ========== 系统状态 ==========
    async getStatus() {
        const res = await this.client.get('/api/v1/status');
        return res.data;
    }
    
    // ========== 语音 ==========
    async tts(text, voice = 'zh-CN-XiaoxiaoNeural') {
        const res = await this.client.post('/api/v1/tts', { text, voice });
        return res.data;
    }
    
    async stt(audioPath) {
        const formData = new FormData();
        formData.append('audio', require('fs').createReadStream(audioPath));
        const res = await this.client.post('/api/v1/stt', formData, {
            headers: { 'Content-Type': 'multipart/form-data' }
        });
        return res.data;
    }
    
    async voicePush(device, text) {
        const res = await this.client.post('/api/v1/voice', { device, text });
        return res.data;
    }
    
    // ========== 对话 ==========
    async chat(message, context = null) {
        const data = { message };
        if (context) data.context = context;
        const res = await this.client.post('/api/v1/chat', data);
        return res.data;
    }
    
    async *chatStream(message) {
        const response = await this.client.post('/api/v1/chat/stream', 
            { message },
            { responseType: 'stream' }
        );
        
        for await (const chunk of response.data) {
            yield chunk.toString();
        }
    }
    
    // ========== 通知 ==========
    async notify(device, title, body) {
        const res = await this.client.post('/api/v1/notification', { device, title, body });
        return res.data;
    }
    
    // ========== 远程控制 ==========
    async control(device, action) {
        const res = await this.client.post('/api/v1/control', { device, action });
        return res.data;
    }
    
    // ========== 传感器 ==========
    async getSensors() {
        const res = await this.client.get('/api/v1/sensors');
        return res.data;
    }
    
    // ========== 摄像头 ==========
    async cameraSnap(device = 'default') {
        const res = await this.client.post('/api/v1/camera/snap', { device });
        return res.data;
    }
    
    // ========== 文件操作 ==========
    async listFiles(path = '/') {
        const res = await this.client.get('/api/v1/files', { params: { path } });
        return res.data;
    }
    
    async uploadFile(localPath, remotePath) {
        const formData = new FormData();
        formData.append('file', require('fs').createReadStream(localPath));
        formData.append('path', remotePath);
        const res = await this.client.post('/api/v1/files/upload', formData);
        return res.data;
    }
    
    async downloadFile(remotePath, localPath) {
        const res = await this.client.get('/api/v1/files/download', { 
            params: { path: remotePath },
            responseType: 'stream'
        });
        const fs = require('fs');
        const writer = fs.createWriteStream(localPath);
        res.data.pipe(writer);
        return new Promise((resolve, reject) => {
            writer.on('finish', resolve);
            writer.on('error', reject);
        });
    }
    
    // ========== 设置 ==========
    async getSettings() {
        const res = await this.client.get('/api/v1/settings');
        return res.data;
    }
    
    async updateSettings(settings) {
        const res = await this.client.put('/api/v1/settings', settings);
        return res.data;
    }
    
    // ========== 技能 ==========
    async listSkills() {
        const res = await this.client.get('/api/v1/skills');
        return res.data;
    }
    
    async callSkill(skillName, params = {}) {
        const res = await this.client.post(`/api/v1/skills/${skillName}`, params);
        return res.data;
    }
    
    // 常用技能快捷方法
    async weather(city = '北京') {
        return this.callSkill('weather', { city });
    }
    
    async playMusic(song, artist = null) {
        return this.callSkill('music_play', { song, artist });
    }
    
    async setAlarm(time, message = '') {
        return this.callSkill('alarm', { time, message });
    }
    
    async tellStory(topic = null) {
        return this.callSkill('story', { topic });
    }
    
    async translate(text, to = 'en') {
        return this.callSkill('translate', { text, to });
    }
    
    // ========== 场景 ==========
    async listScenes() {
        const res = await this.client.get('/api/v1/scenes');
        return res.data;
    }
    
    async switchScene(sceneName) {
        const res = await this.client.post('/api/v1/scenes/switch', { scene: sceneName });
        return res.data;
    }
    
    // ========== 设备 ==========
    async listDevices() {
        const res = await this.client.get('/api/v1/devices');
        return res.data;
    }
    
    async findDevice(deviceId) {
        const res = await this.client.post(`/api/v1/devices/${deviceId}/find`);
        return res.data;
    }
    
    // ========== 健康 ==========
    async getHealth() {
        const res = await this.client.get('/api/v1/health');
        return res.data;
    }
}

module.exports = AideClient;
