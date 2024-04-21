#ifndef __BUZZER_H
#define __BUZZER_H

#include "stm32f10x.h"

/**
 * @brief  初始化蜂鸣器(低电平触发)
 * @param RCC_APB2Periph 外设组
 * @param GPIOx 外设名
 * @param GPIO_Pin 外设针脚
 */
void Buzzer_Init(uint32_t RCC_APB2Periph, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
/**
 * @brief  蜂鸣器响
 */
void Buzzer_ON(void);
/**
 * @brief  蜂鸣器停
 */
void Buzzer_OFF(void);

#endif
