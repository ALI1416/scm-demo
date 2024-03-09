#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "XPT2046.h"

unsigned int ADValue;

void main(void)
{
  LCD_Init();
  LCD_ShowString(1, 1, "KTDZ  RMDZ  GMDZ");
  while (1)
  {
    ADValue = XPT2046_ReadAD(XPT2046_XP_12);   //读取AIN0，可调电阻
    LCD_ShowNum(2, 1, ADValue, 4);             //显示AIN0
    ADValue = XPT2046_ReadAD(XPT2046_YP_12);   //读取AIN1，热敏电阻
    LCD_ShowNum(2, 7, ADValue, 4);             //显示AIN1
    ADValue = XPT2046_ReadAD(XPT2046_VBAT_12); //读取AIN2，光敏电阻
    LCD_ShowNum(2, 13, ADValue, 4);            //显示AIN2
    delayMs(100);
  }
}
