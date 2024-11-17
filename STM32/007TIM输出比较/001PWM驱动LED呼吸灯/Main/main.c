#include "stm32f10x.h"
#include "OLED.h"
#include "Delay.h"
#include "PWM.h"

uint32_t count = 0;

/**
 * PWM驱动LED呼吸灯
 * LED正极PA0，负极GND(高电平点亮，低电平熄灭)
 */
int main()
{
  OLED_Init(RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_11, GPIOB, GPIO_Pin_10);
  PWM_Init_PA0(720 - 1, 100 - 1, 0);
  // PWM_Init_PA15(720 - 1, 100 - 1, 0);
  while (1)
  {
    for (uint8_t i = 0; i < 100; i++)
    {
      TIM_SetCompare1(TIM2, i);
      OLED_ShowFixedNumber(0, 0, i, 3);
      Delay_ms(10);
    }
    for (uint8_t i = 100; i > 0; i--)
    {
      TIM_SetCompare1(TIM2, i);
      OLED_ShowFixedNumber(0, 0, i, 3);
      Delay_ms(10);
    }
  }
}
