#include "stm32f10x.h"
#include "OLED.h"
#include "Timer2.h"

uint32_t count = 0;

/**
 * 内部定时器中断
 * CK_CNT_OV=CK_CNT/(ARR+1)=CK_PSC/(PSC+1)/(ARR+1)
 * 定时频率=时钟频率/(预分频器的值+1)/(自动重装器的值+1)
 * 定时1s=1hz=72MHz/(7200)/(10000)
 */
int main()
{
  OLED_Init(RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_11, GPIOB, GPIO_Pin_10);
  Timer2_Init(7200 - 1, 10000 - 9, NVIC_PriorityGroup_2, 1, 1);
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
