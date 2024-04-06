#ifndef __KEY_H
#define __KEY_H

/**
 * @brief  初始化Key B0、B1和B11
 */
void Key_Init(void);
/**
 * @brief  获取键码值
 * @retval 键码值
 * 0 没有按下
 * 1 B0
 * 2 B1
 * 3 B11
 */
uint8_t Key_GetNum(void);

#endif
