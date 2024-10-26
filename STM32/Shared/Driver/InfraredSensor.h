#ifndef __INFRARED_SENSOR_H
#define __INFRARED_SENSOR_H

#include "stm32f10x.h"

/**
 * @brief  初始化对射式红外传感器
 * @param RCC_APB2Periph 外设组
 * @param GPIOx 外设名
 * @param GPIO_Pin 外设针脚
 */
void InfraredSensor_Init(uint32_t RCC_APB2Periph, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

#endif
