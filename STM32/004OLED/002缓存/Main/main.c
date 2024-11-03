#include "stm32f10x.h"
#include "OLED.Pro.h"
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
    OLED_ShowString(8, 0, " `~!@#$%^&*()_=");
    OLED_ShowNumber(0, 16, 12345);
    OLED_ShowSignedNumber(40, 16, -67890);
    OLED_ShowSignedNumber(88, 16, 1234);
    OLED_ShowHexNumber(0, 32, 0x12345678);
    OLED_ShowHexNumber(64, 32, 0x90ABCDEF);
    OLED_ShowBinNumber(0, 48, 0x1234);
    OLED_Update();
    Delay_s(5);
    OLED_Clear();
    OLED_Update();
    Delay_s(1);
    /* 2 */
    OLED_ShowString(0, 0, "0123456789ABCDEF");
    OLED_ShowString(0, 16, "GHIJKLMNOPQRSTUV");
    OLED_ShowString(0, 32, "WXYZabcdefghijkl");
    OLED_ShowString(0, 48, "mnopqrstuvwxyz`~");
    OLED_UpdateArea(0, 0, 64, 8);
    Delay_s(1);
    OLED_UpdateArea(0, 8, 64, 8);
    Delay_s(1);
    OLED_UpdateArea(64, 0, 64, 16);
    Delay_s(1);
    OLED_UpdateArea(0, 16, 128, 16);
    Delay_s(1);
    OLED_UpdateArea(0, 32, 128, 32);
    Delay_s(1);
    OLED_ClearArea(0, 0, 64, 16);
    OLED_UpdateArea(0, 0, 64, 16);
    Delay_s(1);
    OLED_ClearArea(64, 0, 64, 16);
    OLED_UpdateArea(64, 0, 64, 16);
    Delay_s(1);
    OLED_ClearArea(0, 16, 128, 48);
    OLED_UpdateArea(0, 16, 128, 48);
    Delay_s(1);
    /* 3 */
    OLED_ShowString(0, 0, "!@#$%^&*()_+-=[]");
    OLED_ShowString(0, 16, " {}\\|;:'\"<>,.?/ ");
    OLED_Update();
    Delay_s(1);
    OLED_ShowFixedNumber(0, 32, 12345, 8);
    OLED_ShowFixedNumber(72, 32, 12345, 4);
    OLED_ShowFixedSignedNumber(0, 48, 1234, 8);
    OLED_ShowFixedSignedNumber(72, 48, -1234, 5);
    OLED_Update();
    Delay_s(1);
    OLED_ReverseArea(0, 0, 128, 32);
    OLED_UpdateArea(0, 0, 128, 32);
    Delay_s(1);
    OLED_Reverse();
    OLED_Update();
    Delay_s(1);
    OLED_Clear();
    OLED_Update();
    Delay_s(1);
  }
}
