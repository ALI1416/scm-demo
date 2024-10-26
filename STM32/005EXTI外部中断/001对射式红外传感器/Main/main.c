#include "stm32f10x.h"
#include "OLED.h"
#include "Delay.h"

/**
 * 对射式红外传感器
 */
int main()
{
  OLED_Init(RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_11, GPIOB, GPIO_Pin_10);
  OLED_ShowString(0, 0, "Hello, World!");
  /* 配置外部中断 */
  // 1、配置RCC 打开时钟(EXTI和NVIC不需要手动开启)
  // 开启GPIOB时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  // 开启AFIO时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  // 2、配置GPIO 选择端口为输入模式
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  // 3、配置AFIO(中断引脚选择) GPIO连接到EXTI
  // 位于stm32f10x_gpio文件里
  // GPIO_AFIODeInit复位AFIO外设
  // GPIO_PinLockConfig锁定GPIO配置
  // GPIO_EventOutputConfig和GPIO_EventOutputCmd配置AFIO事件输出功能
  // GPIO_PinRemapConfig引脚重映射(常用)
  // GPIO_EXTILineConfig外部中断(常用)
  // GPIO_ETH_MediaInterfaceConfig以太网
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);
  // 4、配置EXTI(边沿检测及控制) 选择边沿触发方式(上升、下降、双边)和触发响应方式(中断、事件)
  // 位于stm32f10x_exti文件里
  // EXTI_DeInit复位EXTI配置
  // EXTI_Init初始化EXTI
  // EXTI_StructInit通过结构体初始化EXTI
  // EXTI_GenerateSWInterrupt软件触发外部中断
  // EXTI_GetFlagStatus和EXTI_GetITStatus(中断函数内部使用)获取标志位是否被置1
  // EXTI_ClearFlag和EXTI_ClearITPendingBit(中断函数内部使用)对置1的标志位进行清除
  EXTI_InitTypeDef EXTI_InitInitStructure;
  // 中断线
  EXTI_InitInitStructure.EXTI_Line = EXTI_Line14;
   // 状态：ENABLE开启、DISABLE关闭
  EXTI_InitInitStructure.EXTI_LineCmd = ENABLE;
 // 模式：EXTI_Mode_Interrupt中断模式、EXTI_Mode_Event事件模式
  EXTI_InitInitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  // 触发信号的有效边沿：EXTI_Trigger_Rising上升、EXTI_Trigger_Falling下降、EXTI_Trigger_Rising_Falling双边
  EXTI_InitInitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_Init(&EXTI_InitInitStructure);
  // 5、配置NVIC(优先级)
  // 位于misc文件里
  // NVIC_PriorityGroupConfig中断分组配置(芯片只能用一种、代码只执行一次就可以)
  // NVIC_Init初始化NVIC
  // NVIC_SetVectorTable设置中断向量表
  // NVIC_SystemLPConfig系统低功耗配置
  // pre-emption priority先占(抢占)优先级、subpriority从占(响应)优先级
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  NVIC_InitTypeDef* NVIC_InitStructure;
  // 通道选择stm32f10x文件查找IRQn_Type类型，本芯片使用的是STM32F10X_MD中等密度
  // 使用EXTI_Line14位于EXTI15_10_IRQn中
  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
  // 状态：ENABLE开启、DISABLE关闭
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  // 抢占优先级
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  // 响应优先级
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_Init(NVIC_InitStructure);
  // 6、执行中断程序

  while (1)
  {
  }
}
