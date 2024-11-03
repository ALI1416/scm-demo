#ifndef __TIMER2_H
#define __TIMER2_H

#include "stm32f10x.h"

/**
 * @brief  初始化定时器2
 * CK_CNT_OV=CK_CNT/(ARR+1)=CK_PSC/(PSC+1)/(ARR+1)
 * 定时频率=时钟频率/(预分频器的值+1)/(自动重装器的值+1)
 * 定时1s=1hz=72MHz/(7200)/(10000)
 * @param TIM_Prescaler 预分频器(PSC)的值
 * @param TIM_Period 自动重装器(ARR)的值
 * @param NVIC_PriorityGroup 中断分组(0 ~ 4)
 * @param NVIC_IRQChannelPreemptionPriority 抢占优先级(0 ~ 15)
 * @param NVIC_IRQChannelSubPriority 响应优先级(0 ~ 15)
 */
void Timer2_Init(uint16_t TIM_Prescaler, uint16_t TIM_Period, uint32_t NVIC_PriorityGroup, uint8_t NVIC_IRQChannelPreemptionPriority, uint8_t NVIC_IRQChannelSubPriority);

#endif
