#include "stm32f10x.h"
#include "OLED.h"
#include "InfraredSensor.h"

uint32_t count = 0;

/**
 * 对射式/反射式红外传感器
 */
int main()
{
  OLED_Init(RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_11, GPIOB, GPIO_Pin_10);
  // 1、GPIO
  InfraredSensor_Init(RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_14);
  // 2、AFIO(中断引脚选择) GPIO连接到EXTI
  InfraredSensor_Init_AFIO(RCC_APB2Periph_AFIO, GPIO_PortSourceGPIOB, GPIO_PinSource14);
  // 3、EXTI(边沿检测及控制)
  // EXTI和NVIC不需要手动开启时钟
  InfraredSensor_Init_EXTI(EXTI_Line14, EXTI_Trigger_Falling);
  // 4、配置NVIC(优先级)
  // 使用的EXTI_Line14位于EXTI15_10_IRQn中
  InfraredSensor_Init_NVIC(EXTI15_10_IRQn, NVIC_PriorityGroup_2, 1, 1);
  while (1)
  {
    OLED_ShowNumber(0, 0, count);
  }
}

// 5、执行中断程序
// 在startup_stm32f10x_md文件中存在EXTI15_10_IRQHandler中断函数
void EXTI15_10_IRQHandler(void)
{
  // 判断是否为指定中断线进来的中断
  if (EXTI_GetITStatus(EXTI_Line14) == SET)
  {
    count++;
    // 清除中断标志位
    EXTI_ClearITPendingBit(EXTI_Line14);
  }
}
