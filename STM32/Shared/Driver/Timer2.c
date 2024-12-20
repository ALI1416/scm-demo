#include "stm32f10x.h"

// CNT计数器从0开始每次+1，数值到ARR自动重装器的值时，ARR+1，CNT清零
// ARR到PSC预分频器的值时，ARR清零，产生中断

/**
 * @brief  初始化定时器2(内部时钟)
 * CK_CNT_OV=CK_CNT/(ARR+1)=CK_PSC/(PSC+1)/(ARR+1)
 * 定时频率=时钟频率/(预分频器的值+1)/(自动重装器的值+1)
 * 定时1s=1hz=72MHz/(7200)/(10000)
 * @param TIM_Prescaler 预分频器(PSC)的值
 * @param TIM_Period 自动重装器(ARR)的值
 * @param NVIC_PriorityGroup 中断分组(0 ~ 4)
 * @param NVIC_IRQChannelPreemptionPriority 抢占优先级(0 ~ 15)
 * @param NVIC_IRQChannelSubPriority 响应优先级(0 ~ 15)
 */
void Timer2_Init(uint16_t TIM_Prescaler, uint16_t TIM_Period, uint32_t NVIC_PriorityGroup, uint8_t NVIC_IRQChannelPreemptionPriority, uint8_t NVIC_IRQChannelSubPriority)
{
  // 1、开启RCC内部时钟
  // 在stm32f10x_tim文件里
  // TIM_DeInit 恢复默认配置
  // TIM_TimeBaseInit 初始化时基单元
  // TIM_TimeBaseStructInit 给时基单元结构体默认值
  // TIM_Cmd 使能计数器
  // TIM_ITConfig 使能中断输出信号
  // TIM_InternalClockConfig 内部时钟
  // TIM_ITRxExternalClockConfig 选择ITRx其他定时器时钟
  // TIM_TIxExternalClockConfig 选择TIx捕获通道时钟
  // TIM_ETRClockMode1Config 选择ETR通过外部时钟模式1输入的时钟
  // TIM_ETRClockMode2Config 选择ETR通过外部时钟模式2输入的时钟
  // TIM_ETRConfig 配置ETR引脚参数
  // TIM_PrescalerConfig 配置预分频配置
  // TIM_CounterModeConfig 配置计数器的计数模式
  // TIM_ARRPreloadConfig 配置自动重装器预装功能
  // TIM_SetCounter 修改计数器的值
  // TIM_SetAutoreload 修改自动重装器的值
  // TIM_GetCounter 获取计数器的值
  // TIM_GetPrescaler 获取预分频器的值
  // TIM_GetFlagStatus 和 TIM_GetITStatus (中断函数内部使用) 获取标志位是否被置SET
  // TIM_ClearFlag 和 TIM_ClearITPendingBit (中断函数内部使用) 对置SET的标志位进行清除
  // 初始化TIM2通用定时器
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  // 2、选择内部时钟源(默认使用内部时钟，可以不写)
  TIM_InternalClockConfig(TIM2);
  // 3、配置时基单元
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
  // 时钟分频(不分频)
  TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  // 计数器模式
  // TIM_CounterMode_Up 向上计数
  // TIM_CounterMode_Down 向下计数
  // TIM_CounterMode_CenterAligned1 TIM_CounterMode_CenterAligned2 TIM_CounterMode_CenterAligned3 中央对齐模式123
  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
  // 预分频器的值
  TIM_TimeBaseInitStructure.TIM_Prescaler = TIM_Prescaler;
  // 自动重装器的值
  TIM_TimeBaseInitStructure.TIM_Period = TIM_Period;
  // 重复计数器的值(高级定时器才有)
  TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
  // TIM_TimeBaseInit函数的最后，手动生成了更新事件，会进入更新中断
  // 清除更新中断标志位，防止立即进入中断
  TIM_ClearFlag(TIM2, TIM_FLAG_Update);
  // 4、配置输出中断配置，允许更新中断输出到NVIC
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  // 5、配置NVIC，打开定时器中断通道，分配优先级
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup);
  NVIC_InitTypeDef NVIC_InitStructure;
  // 定时器2通道
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_IRQChannelPreemptionPriority;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_IRQChannelSubPriority;
  NVIC_Init(&NVIC_InitStructure);
  // 6、运行控制(开启计数器)
  TIM_Cmd(TIM2, ENABLE);
}

/**
 * @brief  初始化定时器2(外部时钟只能接在A0上)
 * CK_CNT_OV=CK_CNT/(ARR+1)=CK_PSC/(PSC+1)/(ARR+1)
 * 定时频率=时钟频率/(预分频器的值+1)/(自动重装器的值+1)
 * 定时1s=1hz=72MHz/(7200)/(10000)
 * @param TIM_Prescaler 预分频器(PSC)的值
 * @param TIM_Period 自动重装器(ARR)的值
 * @param NVIC_PriorityGroup 中断分组(0 ~ 4)
 * @param NVIC_IRQChannelPreemptionPriority 抢占优先级(0 ~ 15)
 * @param NVIC_IRQChannelSubPriority 响应优先级(0 ~ 15)
 */
void Timer2_External_Init(uint16_t TIM_Prescaler, uint16_t TIM_Period, uint32_t NVIC_PriorityGroup, uint8_t NVIC_IRQChannelPreemptionPriority, uint8_t NVIC_IRQChannelSubPriority)
{
  // 开启外部时钟的外设时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  // 官方推荐浮空输入，但是不建议
  // 可以使用上拉输入
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  // 选择ETR通过外部时钟模式2输入的时钟
  // TIM_ExtTRGPrescaler 外部触发预分频器 TIM_ExtTRGPSC_OFF不需要分频
  // TIM_ExtTRGPolarity 外部触发极性
  // TIM_ExtTRGPolarity_Inverted 反向：低电平或下降沿有效
  // TIM_ExtTRGPolarity_NonInverted 不反向：高电平或上升沿有效
  // ExtTRGFilter 外部触发滤波器 0x0F最大 消除抖动
  TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0x0F);
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
  TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInitStructure.TIM_Prescaler = TIM_Prescaler;
  TIM_TimeBaseInitStructure.TIM_Period = TIM_Period;
  TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
  TIM_ClearFlag(TIM2, TIM_FLAG_Update);
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup);
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_IRQChannelPreemptionPriority;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_IRQChannelSubPriority;
  NVIC_Init(&NVIC_InitStructure);
  TIM_Cmd(TIM2, ENABLE);
}

// 执行中断程序
// 在startup_stm32f10x_md文件中存在 TIM2_IRQHandler 中断函数
// void TIM2_IRQHandler(void)
// {
//   // 判断是否为指定中断线进来的中断
//   if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
//   {
//     /* 执行代码 */
//     // 清除中断标志位
//     TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
//   }
// }
