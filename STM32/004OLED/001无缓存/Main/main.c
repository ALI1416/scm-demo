#include "stm32f10x.h"
#include "OLED.h"

/**
 * OLED
 */
int main()
{
  OLED_Init(RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_11, GPIOB, GPIO_Pin_10);
  OLED_ShowChar(0, 0, 'A');
  OLED_ShowString(0, 1, " `~!@#$%^&*()_=");
  OLED_ShowNumber(1, 0, 12345);
  OLED_ShowSignedNumber(1, 5, -89012);
  OLED_ShowSignedNumber(1, 11, 3456);
  OLED_ShowHexNumber(2, 0, 0x12345678);
  OLED_ShowHexNumber(2, 8, 0x90ABCDEF);
  OLED_ShowBinNumber(3, 0, 0x1234);
  while (1)
  {
  }
}
