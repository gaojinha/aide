/**
 * AIDE SDK TypeScript Definitions
 */

export interface AideOptions {
    baseURL?: string;
    apiKey?: string;
    timeout?: number;
}

export interface ChatMessage {
    role: 'user' | 'assistant';
    content: string;
}

export interface ChatContext {
    history?: ChatMessage[];
    user_id?: string;
    [key: string]: any;
}

export interface SkillParams {
    [key: string]: any;
}

export declare class AideClient {
    constructor(options?: AideOptions);
    
    // System
    getStatus(): Promise<any>;
    
    // Voice
    tts(text: string, voice?: string): Promise<any>;
    stt(audioPath: string): Promise<any>;
    voicePush(device: string, text: string): Promise<any>;
    
    // Chat
    chat(message: string, context?: ChatContext): Promise<any>;
    chatStream(message: string): AsyncGenerator<string>;
    
    // Notification
    notify(device: string, title: string, body: string): Promise<any>;
    
    // Control
    control(device: string, action: string): Promise<any>;
    
    // Sensors
    getSensors(): Promise<any>;
    
    // Camera
    cameraSnap(device?: string): Promise<any>;
    
    // Files
    listFiles(path?: string): Promise<any>;
    uploadFile(localPath: string, remotePath: string): Promise<any>;
    downloadFile(remotePath: string, localPath: string): Promise<any>;
    
    // Settings
    getSettings(): Promise<any>;
    updateSettings(settings: Record<string, any>): Promise<any>;
    
    // Skills
    listSkills(): Promise<any>;
    callSkill(skillName: string, params?: SkillParams): Promise<any>;
    weather(city?: string): Promise<any>;
    playMusic(song: string, artist?: string): Promise<any>;
    setAlarm(time: string, message?: string): Promise<any>;
    tellStory(topic?: string): Promise<any>;
    translate(text: string, to?: string): Promise<any>;
    
    // Scenes
    listScenes(): Promise<any>;
    switchScene(sceneName: string): Promise<any>;
    
    // Devices
    listDevices(): Promise<any>;
    findDevice(deviceId: string): Promise<any>;
    
    // Health
    getHealth(): Promise<any>;
}
