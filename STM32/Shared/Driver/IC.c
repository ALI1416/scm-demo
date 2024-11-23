#include "stm32f10x.h"

/**
 * @brief 初始化输入捕获(测量周期法，最大测量频率1MHz)在PA6口(定时器3通道1)
 */
void IC_Init_PA6()
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  TIM_InternalClockConfig(TIM3);
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
  TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
  // 预分频器(PSC)的值 最大测量频率1MHz
  TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;
  // 自动重装器(ARR)的值设置为最大 防止计数溢出
  TIM_TimeBaseInitStructure.TIM_Period = 65535;
  TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
  // 初始化TIM3
  // 在stm32f10x_tim文件里
  // TIM_ICInit初始化输入比较(Input Compare)
  // TIM_PWMIConfig配置输入比较交叉配置
  // TIM_ICStructInit给输入比较模块结构体默认值
  // TIM_SelectInputTrigger选择输入触发源(TRGI)
  // TIM_SelectOutputTrigger选择输出触发源(TRGO)
  // TIM_SelectSlaveMode选择从模式
  // TIM_SetIC1Prescaler配置分频器
  // TIM_GetCapture1获取CCR寄存器值(和TIM_SetCompare1对应)
  TIM_ICInitTypeDef TIM_ICInitStructure;
  // 通道
  // TIM_Channel_1 通道1
  // TIM_Channel_2 通道2
  // TIM_Channel_3 通道3
  // TIM_Channel_4 通道4
  TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
  // 滤波器0x0~0xF
  TIM_ICInitStructure.TIM_ICFilter = 0xF;
  // 极限
  // TIM_ICPolarity_Rising上升沿
  // TIM_ICPolarity_Falling下降沿
  // TIM_ICPolarity_BothEdge双边沿
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
  // 分频器
  // TIM_ICPSC_DIV1不分频
  // TIM_ICPSC_DIV2 2分频
  // TIM_ICPSC_DIV4 4分频
  // TIM_ICPSC_DIV8 8分频
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  // 数据选择器
  // TIM_ICSelection_DirectTI直连通道
  // TIM_ICSelection_IndirectTI交叉通道
  // TIM_ICSelection_TRC TRC引脚
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInit(TIM3, &TIM_ICInitStructure);
  // 配置TRGI的触发源为TI1FP1
  TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1);
  // 选择从模式 复位CNT
  TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);
  TIM_Cmd(TIM3, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  // 要使用上拉输入模式
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}
