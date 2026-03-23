/**
 * AIDE SDK Test
 */

const AideClient = require('./src/index');

async function main() {
    const client = new AideClient({
        baseURL: 'http://localhost:8080'
    });
    
    try {
        // 获取状态
        console.log('Status:', await client.getStatus());
        
        // 对话
        console.log('Chat:', await client.chat('你好'));
        
        // 技能列表
        console.log('Skills:', await client.listSkills());
        
    } catch (err) {
        console.error('Error:', err.message);
    }
}

main();
