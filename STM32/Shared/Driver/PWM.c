#include "stm32f10x.h"

/**
 * @brief  初始化PWM在PA0口(定时器2通道1)
 * PWM频率=CK_PSC/(PSC+1)/(ARR+1)
 * PWM占空比(高电平所占比例)=CCR/(ARR+1)
 * PWM分辨率(调节精度)=1/(ARR+1)
 * 频率1kHz 占空比50% 分辨率1%
 * 72M/(PSC+1)/(ARR+1)=1000 --> PSC+1=720
 * CCR/(ARR+1)=50% --> CCR=50
 * 1/(ARR+1)=1% --> ARR+1=100
 * @param TIM_Prescaler 预分频器(PSC)的值
 * @param TIM_Period 自动重装器(ARR)的值
 * @param TIM_Pulse 脉冲(CCR寄存器值)
 */
void PWM_Init_PA0(uint16_t TIM_Prescaler, uint16_t TIM_Period, uint16_t TIM_Pulse)
{
  // 初始化TIM2
  // 在stm32f10x_tim文件里
  // TIM_OC1Init配置输出比较(Output Compare)通道
  // TIM_OCStructInit给输出比较模块结构体默认值
  // TIM_CtrlPWMOutputs高级定时器PWM输出使能
  // TIM_ForcedOC1Config配置强制输出模式
  // TIM_OC1PreloadConfig配置CCR寄存器预装功能
  // TIM_OC1FastConfig配置快速使能
  // TIM_ClearOC1Ref外部事件时清除REF信号
  // TIM_OC1PolarityConfig设置定时器输出比较极性
  // TIM_OC1NPolarityConfig高级定时器互补通道配置
  // TIM_CCxCmd、TIM_CCxNCmd修改输出使能
  // TIM_SelectOCxM选择输出比较模式
  // TIM_SetCompare1修改CCR寄存器值
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  TIM_InternalClockConfig(TIM2);
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
  TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInitStructure.TIM_Prescaler = TIM_Prescaler;
  TIM_TimeBaseInitStructure.TIM_Period = TIM_Period;
  TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
  TIM_Cmd(TIM2, ENABLE);
  // 初始化输出比较通道
  TIM_OCInitTypeDef TIM_OCInitStructure;
  // 给个默认值，不配置高级定时器参数
  TIM_OCStructInit(&TIM_OCInitStructure);
  // 模式
  // TIM_OCMode_Timing冻结
  // TIM_OCMode_Active高电平
  // TIM_OCMode_Inactive低电平
  // TIM_OCMode_Toggle电平反转
  // TIM_OCMode_PWM1 PWM模式1
  // TIM_OCMode_PWM2 PWM模式2
  // TIM_ForcedAction_Active强制高电平输出
  // TIM_ForcedAction_InActive强制低电平输出
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  // 极性
  // TIM_OCPolarity_High正常
  // TIM_OCPolarity_Low翻转
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  // 使能
  // TIM_OutputState_Disable失能
  // TIM_OutputState_Enable使能
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  // CCR寄存器值
  TIM_OCInitStructure.TIM_Pulse = TIM_Pulse;
  TIM_OC1Init(TIM2, &TIM_OCInitStructure);
  // 初始化PA0引脚
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  // 要使用复用推挽输出模式
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**
 * @brief  初始化PWM在PA15口(定时器2通道1)
 * PWM频率=CK_PSC/(PSC+1)/(ARR+1)
 * PWM占空比(高电平所占比例)=CCR/(ARR+1)
 * PWM分辨率(调节精度)=1/(ARR+1)
 * 频率1kHz 占空比50% 分辨率1%
 * 72M/(PSC+1)/(ARR+1)=1000 --> PSC+1=720
 * CCR/(ARR+1)=50% --> CCR=50
 * 1/(ARR+1)=1% --> ARR+1=100
 * @param TIM_Prescaler 预分频器(PSC)的值
 * @param TIM_Period 自动重装器(ARR)的值
 * @param TIM_Pulse 脉冲(CCR寄存器值)
 */
void PWM_Init_PA15(uint16_t TIM_Prescaler, uint16_t TIM_Period, uint16_t TIM_Pulse)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  TIM_InternalClockConfig(TIM2);
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
  TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInitStructure.TIM_Prescaler = TIM_Prescaler;
  TIM_TimeBaseInitStructure.TIM_Period = TIM_Period;
  TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
  TIM_Cmd(TIM2, ENABLE);
  TIM_OCInitTypeDef TIM_OCInitStructure;
  TIM_OCStructInit(&TIM_OCInitStructure);
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = TIM_Pulse;
  TIM_OC1Init(TIM2, &TIM_OCInitStructure);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  // 引脚重映射
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  // 默认功能TIM2_CH1_ETR在PA0-WKUP引脚上，可以重映射到PA15引脚(参考手册8.3.7 TIM2复用功能重映像，使用部分重映射1)
  // 由于PA15默认功能是JTDI调试，还需要禁用掉
  GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);
  // GPIO_Remap_SWJ_NoJTRST解除NJTRST调试(PB4)
  // GPIO_Remap_SWJ_JTAGDisable解除JTAG调试(PA15、PB3、PB4)
  // GPIO_Remap_SWJ_Disable解除SWD和JTAG调试(PA13、PA14、PA15、PB3、PB4) 谨慎使用，否则STLINK无法下载重新
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
}

/**
 * @brief  初始化PWM在PA1口(定时器2通道2)
 * PWM频率=CK_PSC/(PSC+1)/(ARR+1)
 * PWM占空比(高电平所占比例)=CCR/(ARR+1)
 * PWM分辨率(调节精度)=1/(ARR+1)
 * 频率1kHz 占空比50% 分辨率1%
 * 72M/(PSC+1)/(ARR+1)=1000 --> PSC+1=720
 * CCR/(ARR+1)=50% --> CCR=50
 * 1/(ARR+1)=1% --> ARR+1=100
 * @param TIM_Prescaler 预分频器(PSC)的值
 * @param TIM_Period 自动重装器(ARR)的值
 * @param TIM_Pulse 脉冲(CCR寄存器值)
 */
void PWM_Init_PA1(uint16_t TIM_Prescaler, uint16_t TIM_Period, uint16_t TIM_Pulse)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  TIM_InternalClockConfig(TIM2);
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
  TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInitStructure.TIM_Prescaler = TIM_Prescaler;
  TIM_TimeBaseInitStructure.TIM_Period = TIM_Period;
  TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
  TIM_Cmd(TIM2, ENABLE);
  TIM_OCInitTypeDef TIM_OCInitStructure;
  TIM_OCStructInit(&TIM_OCInitStructure);
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = TIM_Pulse;
  TIM_OC2Init(TIM2, &TIM_OCInitStructure);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**
 * @brief  初始化PWM在PA2口(定时器2通道3)
 * PWM频率=CK_PSC/(PSC+1)/(ARR+1)
 * PWM占空比(高电平所占比例)=CCR/(ARR+1)
 * PWM分辨率(调节精度)=1/(ARR+1)
 * 频率1kHz 占空比50% 分辨率1%
 * 72M/(PSC+1)/(ARR+1)=1000 --> PSC+1=720
 * CCR/(ARR+1)=50% --> CCR=50
 * 1/(ARR+1)=1% --> ARR+1=100
 * @param TIM_Prescaler 预分频器(PSC)的值
 * @param TIM_Period 自动重装器(ARR)的值
 * @param TIM_Pulse 脉冲(CCR寄存器值)
 */
void PWM_Init_PA2(uint16_t TIM_Prescaler, uint16_t TIM_Period, uint16_t TIM_Pulse)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  TIM_InternalClockConfig(TIM2);
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
  TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInitStructure.TIM_Prescaler = TIM_Prescaler;
  TIM_TimeBaseInitStructure.TIM_Period = TIM_Period;
  TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
  TIM_Cmd(TIM2, ENABLE);
  TIM_OCInitTypeDef TIM_OCInitStructure;
  TIM_OCStructInit(&TIM_OCInitStructure);
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = TIM_Pulse;
  TIM_OC3Init(TIM2, &TIM_OCInitStructure);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**
 * @brief  初始化PWM在PA3口(定时器2通道4)
 * PWM频率=CK_PSC/(PSC+1)/(ARR+1)
 * PWM占空比(高电平所占比例)=CCR/(ARR+1)
 * PWM分辨率(调节精度)=1/(ARR+1)
 * 频率1kHz 占空比50% 分辨率1%
 * 72M/(PSC+1)/(ARR+1)=1000 --> PSC+1=720
 * CCR/(ARR+1)=50% --> CCR=50
 * 1/(ARR+1)=1% --> ARR+1=100
 * @param TIM_Prescaler 预分频器(PSC)的值
 * @param TIM_Period 自动重装器(ARR)的值
 * @param TIM_Pulse 脉冲(CCR寄存器值)
 */
void PWM_Init_PA3(uint16_t TIM_Prescaler, uint16_t TIM_Period, uint16_t TIM_Pulse)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  TIM_InternalClockConfig(TIM2);
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
  TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInitStructure.TIM_Prescaler = TIM_Prescaler;
  TIM_TimeBaseInitStructure.TIM_Period = TIM_Period;
  TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
  TIM_Cmd(TIM2, ENABLE);
  TIM_OCInitTypeDef TIM_OCInitStructure;
  TIM_OCStructInit(&TIM_OCInitStructure);
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = TIM_Pulse;
  TIM_OC4Init(TIM2, &TIM_OCInitStructure);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}
