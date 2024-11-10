#include "stm32f10x.h"
#include "OLED.h"
#include "Timer2.h"

uint32_t count = 0;

/**
 * 定时器外部时钟
 * 对射式红外传感器接A0
 * 每次CNT+1
 * 每10次NUM+1
 */
int main()
{
  OLED_Init(RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_11, GPIOB, GPIO_Pin_10);
  Timer2_External_Init(1 - 1, 10 - 1, NVIC_PriorityGroup_2, 1, 1);
  while (1)
  {
    OLED_ShowFixedNumber(0, 0, count, 3);
    OLED_ShowFixedNumber(1, 0, TIM_GetCounter(TIM2), 5);
  }
}

// 执行中断程序
// 在startup_stm32f10x_md文件中存在TIM2_IRQHandler中断函数
void TIM2_IRQHandler(void)
{
  // 判断是否为指定中断线进来的中断
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
  {
    count++;
    // 清除中断标志位
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
  }
}
