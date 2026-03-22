/**
 * @file user_memory.h
 * @brief 用户记忆系统头文件
 * 
 * 提供用户习惯学习和记忆功能
 * 
 * @author AI Assistant Team
 * @version 0.1.0
 */

#ifndef USER_MEMORY_H
#define USER_MEMORY_H

/**
 * @brief 初始化记忆系统
 * @return 0成功
 */
int memory_init(void);

/**
 * @brief 记住信息
 * @param key 键
 * @param value 值
 * @return 0成功
 */
int memory_remember(const char *key, const char *value);

/**
 * @brief 回忆信息
 * @param key 键
 * @param value 值(输出)
 * @return 0成功，-1未找到
 */
int memory_recall(const char *key, char *value);

/**
 * @brief 遗忘信息
 * @param key 键
 * @return 0成功
 */
int memory_forget(const char *key);

/**
 * @brief 学习习惯
 * @param action 动作
 * @param time 时间
 * @return 0成功
 */
int memory_learn_context(const char *action, const char *time, const char *location);

/**
 * @brief 预测用户行为
 * @param context 上下文
 * @param prediction 预测结果(输出)
 * @return 0成功
 */
int memory_predict(const char *context, char *prediction);

/**
 * @brief 获取主动建议
 * @param suggestion 建议(输出)
 * @return 0成功
 */
int memory_suggest(char *suggestion);

/**
 * @brief 列出所有记忆
 */
void memory_list(void);

#endif // USER_MEMORY_H
