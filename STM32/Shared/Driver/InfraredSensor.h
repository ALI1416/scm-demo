#ifndef __INFRARED_SENSOR_H
#define __INFRARED_SENSOR_H

#include "stm32f10x.h"

/**
 * @brief  初始化红外传感器
 * @param RCC_APB2Periph 外设组
 * @param GPIOx 外设名
 * @param GPIO_Pin 外设针脚
 */
void InfraredSensor_Init(uint32_t RCC_APB2Periph, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
/**
 * @brief  初始化红外传感器AFIO
 * @param RCC_APB2Periph 外设组
 * @param GPIO_PortSource 端口
 * @param GPIO_PinSource 针脚
 */
void InfraredSensor_Init_AFIO(uint32_t RCC_APB2Periph, uint8_t GPIO_PortSource, uint8_t GPIO_PinSource);
/**
 * @brief  初始化红外传感器EXTI
 * @param EXTI_Line 中断线
 * EXTI_Line0 ~ EXTI_Line15
 * @param EXTI_Trigger 触发信号的有效边沿
 * EXTI_Trigger_Rising 上升沿
 * EXTI_Trigger_Falling 下降沿
 * EXTI_Trigger_Rising_Falling 双边沿
 */
void InfraredSensor_Init_EXTI(uint32_t EXTI_Line, EXTITrigger_TypeDef EXTI_Trigger);
/**
 * @brief  初始化红外传感器NVIC
 * (芯片只能用一种、代码只执行一次就可以)
 * @param NVIC_IRQChannel 通道(stm32f10x文件查找IRQn_Type类型)
 * @param NVIC_PriorityGroup 中断分组(0 ~ 4)
 * @param NVIC_IRQChannelPreemptionPriority 抢占优先级(0 ~ 15)
 * @param NVIC_IRQChannelSubPriority 响应优先级(0 ~ 15)
 */
void InfraredSensor_Init_NVIC(uint8_t NVIC_IRQChannel, uint32_t NVIC_PriorityGroup, uint8_t NVIC_IRQChannelPreemptionPriority, uint8_t NVIC_IRQChannelSubPriority);

#endif
