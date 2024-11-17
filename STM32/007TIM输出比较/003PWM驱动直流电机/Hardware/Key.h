#ifndef __KEY_H
#define __KEY_H

/**
 * @brief  初始化Key(低电平触发) B0
 */
void Key_Init(void);
/**
 * @brief  获取键码值
 * @retval 键码值
 * 0 没有按下
 * 1 B0
 */
uint8_t Key_GetNum(void);

#endif
