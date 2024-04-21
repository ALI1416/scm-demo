#include "stm32f10x.h"
#include "OLED.h"

/**
 * OLED
 */
int main()
{
  OLED_Init(RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_11, GPIOB, GPIO_Pin_10);
  while (1)
  {
  }
}
