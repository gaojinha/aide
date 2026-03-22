/**
 * 防火墙 - iptables规则
 */

#include <stdio.h>
#include <string.h>

#define MAX_RULES 100

// 协议
typedef enum {
    PROTO_TCP,
    PROTO_UDP,
    PROTO_ICMP,
    PROTO_ALL
} protocol_t;

// 动作
typedef enum {
    ACTION_ACCEPT,
    ACTION_DROP,
    ACTION_REJECT,
    ACTION_LOG
} firewall_action_t;

// 规则
typedef struct {
    int id;
    char name[32];
    protocol_t proto;
    char src_ip[24];
    char dst_ip[24];
    int src_port;
    int dst_port;
    firewall_action_t action;
    int enabled;
} firewall_rule_t;

static firewall_rule_t rules[MAX_RULES];
static int rule_count = 0;
static int firewall_enabled = 1;

// 初始化
int firewall_init(void) {
    printf("[Firewall] Initialized\n");
    
    // 默认规则
    firewall_add_rule("SSH", PROTO_TCP, "0.0.0.0/0", "0.0.0.0/0", 0, 22, ACTION_ACCEPT);
    firewall_add_rule("HTTP", PROTO_TCP, "0.0.0.0/0", "0.0.0.0/0", 0, 80, ACTION_ACCEPT);
    firewall_add_rule("HTTPS", PROTO_TCP, "0.0.0.0/0", "0.0.0.0/0", 0, 443, ACTION_ACCEPT);
    firewall_add_rule("DNS", PROTO_UDP, "0.0.0.0/0", "0.0.0.0/0", 0, 53, ACTION_ACCEPT);
    firewall_add_rule("Block Telnet", PROTO_TCP, "0.0.0.0/0", "0.0.0.0/0", 0, 23, ACTION_DROP);
    firewall_add_rule("Block SMB", PROTO_TCP, "0.0.0.0/0", "0.0.0.0/0", 0, 445, ACTION_DROP);
    
    printf("  Rules: %d\n", rule_count);
    return 0;
}

// 添加规则
int firewall_add_rule(const char *name, protocol_t proto, const char *src_ip, const char *dst_ip, int src_port, int dst_port, firewall_action_t action) {
    if (rule_count >= MAX_RULES) return -1;
    
    firewall_rule_t *r = &rules[rule_count];
    r->id = rule_count + 1;
    strncpy(r->name, name, 31);
    r->proto = proto;
    strncpy(r->src_ip, src_ip, 23);
    strncpy(r->dst_ip, dst_ip, 23);
    r->src_port = src_port;
    r->dst_port = dst_port;
    r->action = action;
    r->enabled = 1;
    rule_count++;
    
    return 0;
}

// 启用/禁用防火墙
int firewall_enable(int enable) {
    firewall_enabled = enable;
    printf("[Firewall] %s\n", enable ? "Enabled" : "Disabled");
    return 0;
}

// 启用/禁用规则
int firewall_rule_enable(int id, int enable) {
    for (int i = 0; i < rule_count; i++) {
        if (rules[i].id == id) {
            rules[i].enabled = enable;
            return 0;
        }
    }
    return -1;
}

// 检查规则匹配
int firewall_check_packet(const char *src_ip, const char *dst_ip, int port, protocol_t proto) {
    if (!firewall_enabled) return ACTION_ACCEPT;
    
    for (int i = 0; i < rule_count; i++) {
        if (!rules[i].enabled) continue;
        
        // 简化匹配
        if (rules[i].dst_port == port || rules[i].dst_port == 0) {
            printf("[Firewall] Matched rule: %s\n", rules[i].name);
            return rules[i].action;
        }
    }
    
    // 默认拒绝
    return ACTION_DROP;
}

// 列出规则
void firewall_list(void) {
    printf("\n=== Firewall Rules (%d) ===\n", rule_count);
    const char *proto_names[] = {"TCP", "UDP", "ICMP", "ALL"};
    const char *action_names[] = {"ACCEPT", "DROP", "REJECT", "LOG"};
    
    for (int i = 0; i < rule_count; i++) {
        printf("%d. [%s] %s %s:%d -> %s:%d %s\n",
            rules[i].id,
            rules[i].enabled ? "ON " : "OFF",
            proto_names[rules[i].proto],
            rules[i].src_ip,
            rules[i].src_port,
            rules[i].dst_ip,
            rules[i].dst_port,
            action_names[rules[i].action]);
    }
    printf("Status: %s\n", firewall_enabled ? "ENABLED" : "DISABLED");
    printf("==========================\n\n");
}

// 应用规则 (模拟iptables)
int firewall_apply(void) {
    printf("[Firewall] Applying rules...\n");
    // TODO: 实际执行 iptables 命令
    printf("[Firewall] iptables -A INPUT -p tcp --dport 22 -j ACCEPT\n");
    printf("[Firewall] iptables -A INPUT -p tcp --dport 80 -j ACCEPT\n");
    printf("[Firewall] iptables -A INPUT -p tcp --dport 443 -j ACCEPT\n");
    printf("[Firewall] iptables -A INPUT -j DROP\n");
    printf("[Firewall] Applied %d rules\n", rule_count);
    return 0;
}

// 测试
void firewall_test(void) {
    printf("\n=== Firewall Test ===\n");
    
    firewall_list();
    
    // 测试数据包
    printf("Packet tests:\n");
    
    int action = firewall_check_packet("192.168.1.100", "192.168.1.1", 22, PROTO_TCP);
    printf("SSH (port 22): %s\n", action == ACTION_ACCEPT ? "ACCEPT" : "DROP");
    
    action = firewall_check_packet("192.168.1.100", "192.168.1.1", 80, PROTO_TCP);
    printf("HTTP (port 80): %s\n", action == ACTION_ACCEPT ? "ACCEPT" : "DROP");
    
    action = firewall_check_packet("192.168.1.100", "192.168.1.1", 23, PROTO_TCP);
    printf("Telnet (port 23): %s\n", action == ACTION_DROP ? "DROP" : "ACCEPT");
    
    action = firewall_check_packet("192.168.1.100", "192.168.1.1", 3389, PROTO_TCP);
    printf("RDP (port 3389): %s\n", action == ACTION_DROP ? "DROP" : "ACCEPT");
    
    firewall_apply();
    
    printf("==================\n\n");
}
