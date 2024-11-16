#ifndef __PWM_H
#define __PWM_H

#include "stm32f10x.h"

/**
 * @brief  初始化PWM在PA0口
 * PWM频率=CK_PSC/(PSC+1)/(ARR+1)
 * PWM占空比(高电平所占比例)=CCR/(ARR+1)
 * PWM分辨率(调节精度)=1/(ARR+1)
 * 频率1kHz 占空比50% 分辨率1%
 * 72M/(PSC+1)/(ARR+1)=1000 --> PSC=720
 * CCR/(ARR+1)=50% --> CCR=50
 * 1/(ARR+1)=1% --> ARR+1=100
 * @param TIM_Prescaler 预分频器(PSC)的值
 * @param TIM_Period 自动重装器(ARR)的值
 * @param TIM_Pulse 脉冲(CCR寄存器值)
 */
void PWM_Init_PA0(uint16_t TIM_Prescaler, uint16_t TIM_Period, uint16_t TIM_Pulse);
/**
 * @brief  初始化PWM在PA15口
 * PWM频率=CK_PSC/(PSC+1)/(ARR+1)
 * PWM占空比(高电平所占比例)=CCR/(ARR+1)
 * PWM分辨率(调节精度)=1/(ARR+1)
 * 频率1kHz 占空比50% 分辨率1%
 * 72M/(PSC+1)/(ARR+1)=1000 --> PSC=720
 * CCR/(ARR+1)=50% --> CCR=50
 * 1/(ARR+1)=1% --> ARR+1=100
 * @param TIM_Prescaler 预分频器(PSC)的值
 * @param TIM_Period 自动重装器(ARR)的值
 * @param TIM_Pulse 脉冲(CCR寄存器值)
 */
void PWM_Init_PA15(uint16_t TIM_Prescaler, uint16_t TIM_Period, uint16_t TIM_Pulse);

#endif
