#ifndef __LIGHT_SENSOR_H
#define __LIGHT_SENSOR_H

#include "stm32f10x.h"

/**
 * @brief  初始化光敏/热敏传感器
 * @param RCC_APB2Periph 外设组
 * @param GPIOx 外设名
 * @param GPIO_Pin 外设针脚
 */
void LightSensor_Init(uint32_t RCC_APB2Periph, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
/**
 * @brief  获取值
 * @retval
 * 1 光线暗/温度低
 * 0 光线亮/温度高
 */
uint8_t LightSensor_Get(void);

#endif
