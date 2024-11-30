#include "stm32f10x.h"
#include "OLED.h"
#include "Timer2.h"
#include "Encoder.h"

int32_t speed = 0;

/**
 * 旋转编码器测速
 * 每秒测速，区分正反转
 * 旋转编码器A接PA6，B接PA7
 */
int main()
{
  OLED_Init(RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_11, GPIOB, GPIO_Pin_10);
  Timer2_Init(7200 - 1, 10000 - 1, NVIC_PriorityGroup_2, 1, 1);
  Encoder_Init_PA6_PA7();
  while (1)
  {
    // 获取值
    // OLED_ShowFixedSignedNumber(0, 0, TIM_GetCounter(TIM3), 6);
    // 获取速度
    OLED_ShowFixedSignedNumber(0, 0, speed, 6);
  }
}

// 获取速度
void TIM2_IRQHandler(void)
{
  // 判断是否为指定中断线进来的中断
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
  {
    // 获取值
    speed = TIM_GetCounter(TIM3);
    // 清空值
    TIM_SetCounter(0);
    // 清除中断标志位
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
  }
}
