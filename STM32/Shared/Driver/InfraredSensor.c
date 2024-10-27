#include "stm32f10x.h"

/**
 * @brief  初始化红外传感器
 * @param RCC_APB2Periph 外设组
 * @param GPIOx 外设名
 * @param GPIO_Pin 外设针脚
 */
void InfraredSensor_Init(uint32_t RCC_APB2Periph, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOx, &GPIO_InitStructure);
}

/**
 * @brief  初始化红外传感器AFIO
 * @param RCC_APB2Periph 外设组
 * @param GPIO_PortSource 端口
 * @param GPIO_PinSource 针脚
 */
void InfraredSensor_Init_AFIO(uint32_t RCC_APB2Periph, uint8_t GPIO_PortSource, uint8_t GPIO_PinSource)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph, ENABLE);
  // 位于stm32f10x_gpio文件里
  // GPIO_AFIODeInit复位AFIO外设
  // GPIO_PinLockConfig锁定GPIO配置
  // GPIO_EventOutputConfig和GPIO_EventOutputCmd配置AFIO事件输出功能
  // GPIO_PinRemapConfig引脚重映射(常用)
  // GPIO_EXTILineConfig外部中断(常用)
  // GPIO_ETH_MediaInterfaceConfig以太网
  GPIO_EXTILineConfig(GPIO_PortSource, GPIO_PinSource);
}

/**
 * @brief  初始化红外传感器EXTI
 * @param EXTI_Line 中断线
 * EXTI_Line0 ~ EXTI_Line15
 * @param EXTI_Trigger 触发信号的有效边沿
 * EXTI_Trigger_Rising 上升沿
 * EXTI_Trigger_Falling 下降沿
 * EXTI_Trigger_Rising_Falling 双边沿
 */
void InfraredSensor_Init_EXTI(uint32_t EXTI_Line, EXTITrigger_TypeDef EXTI_Trigger)
{
  // 位于stm32f10x_exti文件里
  // EXTI_DeInit复位EXTI配置
  // EXTI_Init初始化EXTI
  // EXTI_StructInit通过结构体初始化EXTI
  // EXTI_GenerateSWInterrupt软件触发外部中断
  // EXTI_GetFlagStatus和EXTI_GetITStatus(中断函数内部使用)获取标志位是否被置SET
  // EXTI_ClearFlag和EXTI_ClearITPendingBit(中断函数内部使用)对置SET的标志位进行清除
  EXTI_InitTypeDef EXTI_InitInitStructure;
  // 中断线
  EXTI_InitInitStructure.EXTI_Line = EXTI_Line;
  // 状态：ENABLE开启、DISABLE关闭
  EXTI_InitInitStructure.EXTI_LineCmd = ENABLE;
  // 模式：EXTI_Mode_Interrupt中断模式、EXTI_Mode_Event事件模式
  EXTI_InitInitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  // 触发信号的有效边沿：EXTI_Trigger_Rising上升沿、EXTI_Trigger_Falling下降沿、EXTI_Trigger_Rising_Falling双边沿
  EXTI_InitInitStructure.EXTI_Trigger = EXTI_Trigger;
  EXTI_Init(&EXTI_InitInitStructure);
}

/**
 * @brief  初始化红外传感器NVIC
 * (芯片只能用一种、代码只执行一次就可以)
 * @param NVIC_IRQChannel 通道(stm32f10x文件查找IRQn_Type类型)
 * @param NVIC_PriorityGroup 中断分组(0 ~ 4)
 * @param NVIC_IRQChannelPreemptionPriority 抢占优先级(0 ~ 15)
 * @param NVIC_IRQChannelSubPriority 响应优先级(0 ~ 15)
 */
void InfraredSensor_Init_NVIC(uint8_t NVIC_IRQChannel, uint32_t NVIC_PriorityGroup, uint8_t NVIC_IRQChannelPreemptionPriority, uint8_t NVIC_IRQChannelSubPriority)
{
  // 位于misc文件里
  // NVIC_PriorityGroupConfig中断分组配置(芯片只能用一种、代码只执行一次就可以)
  // NVIC_Init初始化NVIC
  // NVIC_SetVectorTable设置中断向量表
  // NVIC_SystemLPConfig系统低功耗配置
  // pre-emption priority先占(抢占)优先级、subpriority从占(响应)优先级
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup);
  NVIC_InitTypeDef NVIC_InitStructure;
  // 通道选择stm32f10x文件查找IRQn_Type类型，本芯片使用的是STM32F10X_MD中等密度
  NVIC_InitStructure.NVIC_IRQChannel = NVIC_IRQChannel;
  // 状态：ENABLE开启、DISABLE关闭
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  // 抢占优先级
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_IRQChannelPreemptionPriority;
  // 响应优先级
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_IRQChannelSubPriority;
  NVIC_Init(&NVIC_InitStructure);
}
