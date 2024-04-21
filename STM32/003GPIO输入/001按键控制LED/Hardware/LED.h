#ifndef __LED_H
#define __LED_H

/**
 * @brief  初始化LED(低电平点亮) A0和A1
 */
void LED_Init(void);
/**
 * @brief  点亮LED A0
 */
void LED_ON_0(void);
/**
 * @brief  熄灭LED A0
 */
void LED_OFF_0(void);
/**
 * @brief  切换LED A0状态
 */
void LED_Toggle_0(void);
/**
 * @brief  点亮LED A1
 */
void LED_ON_1(void);
/**
 * @brief  熄灭LED A1
 */
void LED_OFF_1(void);
/**
 * @brief  切换LED A1状态
 */
void LED_Toggle_1(void);

#endif
