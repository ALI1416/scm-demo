#include "stm32f10x.h"
#include "OLED.h"
#include "Delay.h"

/**
 * OLED
 */
int main()
{
  OLED_Init(RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_11, GPIOB, GPIO_Pin_10);
  while (1)
  {
    /* 1 */
    OLED_ShowChar(0, 0, 'A');
    OLED_ShowString(0, 1, " `~!@#$%^&*()_=");
    OLED_ShowNumber(1, 0, 12345);
    OLED_ShowSignedNumber(1, 5, -67890);
    OLED_ShowSignedNumber(1, 11, 1234);
    OLED_ShowHexNumber(2, 0, 0x12345678);
    OLED_ShowHexNumber(2, 8, 0x90ABCDEF);
    OLED_ShowBinNumber(3, 0, 0x1234);
    Delay_s(5);
    /* 2 */
    OLED_ShowString(0, 0, "0123456789ABCDEF");
    OLED_ShowString(1, 0, "GHIJKLMNOPQRSTUV");
    OLED_ShowString(2, 0, "WXYZabcdefghijkl");
    OLED_ShowString(3, 0, "mnopqrstuvwxyz`~");
    Delay_s(5);
    /* 3 */
    OLED_ShowString(0, 0, "!@#$%^&*()_+-=[]");
    OLED_ShowString(1, 0, " {}\\|;:'\"<>,.?/ ");
    OLED_ShowString(3, 0, "                ");
    OLED_ShowString(4, 0, "                ");
    Delay_s(5);
  }
}
