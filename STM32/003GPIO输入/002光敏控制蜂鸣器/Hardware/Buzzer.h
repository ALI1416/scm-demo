#ifndef __BUZZER_H
#define __BUZZER_H

/**
 * @brief  初始化蜂鸣器(低电平触发) B12
 */
void Buzzer_Init(void);
/**
 * @brief  蜂鸣器响
 */
void Buzzer_ON(void);
/**
 * @brief  蜂鸣器停
 */
void Buzzer_OFF(void);

#endif
