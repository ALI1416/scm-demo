#include "stm32f10x.h"

/**
 * @brief  初始化编码器在PA6和PA7口(定时器3通道1和通道2)
 */
void Encoder_Init_PA6_PA7(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  TIM_InternalClockConfig(TIM3);
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
  TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
  // 预分频器(PSC) 不需要
  TIM_TimeBaseInitStructure.TIM_Prescaler = 0;
  // 自动重装器(ARR)的值设置为最大 防止计数溢出
  TIM_TimeBaseInitStructure.TIM_Period = 65535;
  TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
  // 初始化TIM3
  // 在stm32f10x_tim文件里
  // TIM_EncoderInterfaceConfig 配置编码器接口
  TIM_ICInitTypeDef TIM_ICInitStructure;
  // 给个默认值 只需要配置通道和滤波器即可
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
  TIM_ICInitStructure.TIM_ICFilter = 0xF;
  TIM_ICInit(TIM3, &TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
  TIM_ICInit(TIM3, &TIM_ICInitStructure);
  // TIM_EncoderMode编码器模式
  // TIM_EncoderMode_TI1 仅在TI1FP1计数
  // TIM_EncoderMode_TI2 仅在TI1FP2计数
  // TIM_EncoderMode_TI12 在TI1FP1和TI1FP2计数
  // TIM_IC1Polarity 和 TIM_IC2Polarity 极性 如果需要反向，只改一个就行
  // TIM_ICPolarity_Falling 下降沿(通道反向)
  // TIM_ICPolarity_Rising 上升沿(通道不反向)
  TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
  TIM_Cmd(TIM3, ENABLE);
  // 初始化PA6和PA7
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  // 要使用上拉输入模式
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}
