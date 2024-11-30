#include "stm32f10x.h"
#include "OLED.h"
#include "InfraredSensor.h"

uint32_t count = 0;

/**
 * 对射式/反射式红外传感器
 * 对射式/反射式红外传感器接B12[DO(数字信号)](线路板AODO标反，需要接AO)
 * 被遮挡/距离过近触发
 */
int main()
{
  OLED_Init(RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_11, GPIOB, GPIO_Pin_10);
  // 1、GPIO
  InfraredSensor_Init(RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_12);
  // 2、AFIO(中断引脚选择) GPIO连接到EXTI
  InfraredSensor_Init_AFIO(RCC_APB2Periph_AFIO, GPIO_PortSourceGPIOB, GPIO_PinSource12);
  // 3、EXTI(边沿检测及控制)
  // EXTI和NVIC不需要手动开启时钟
  InfraredSensor_Init_EXTI(EXTI_Line12, EXTI_Trigger_Falling);
  // 4、配置NVIC(优先级)
  // 使用的 EXTI_Line12 位于 EXTI15_10_IRQn 中
  InfraredSensor_Init_NVIC(EXTI15_10_IRQn, NVIC_PriorityGroup_2, 1, 1);
  while (1)
  {
    OLED_ShowNumber(0, 0, count);
  }
}

// 5、执行中断程序
// 在startup_stm32f10x_md文件中存在 EXTI15_10_IRQHandler 中断函数
void EXTI15_10_IRQHandler(void)
{
  // 判断是否为指定中断线进来的中断
  if (EXTI_GetITStatus(EXTI_Line12) == SET)
  {
    count++;
    // 清除中断标志位
    EXTI_ClearITPendingBit(EXTI_Line12);
  }
}
