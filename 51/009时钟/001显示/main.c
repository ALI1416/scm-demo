#include <REGX52.H>
#include "LCD1602.H"
#include "DS1302.H"

// DS1302是一个时钟芯片
void main()
{
  LCD_Init();
  DS1302_Init();
  LCD_ShowString(1, 1, "  -  -   DAY");
  LCD_ShowString(2, 1, "  :  :");
  DS1302_SetTime();
  while (1)
  {
    DS1302_ReadTime();
    LCD_ShowNum(1, 1, DS1302_Time[0], 2);
    LCD_ShowNum(1, 4, DS1302_Time[1], 2);
    LCD_ShowNum(1, 7, DS1302_Time[2], 2);
    LCD_ShowNum(1, 14, DS1302_Time[6], 1);
    LCD_ShowNum(2, 1, DS1302_Time[3], 2);
    LCD_ShowNum(2, 4, DS1302_Time[4], 2);
    LCD_ShowNum(2, 7, DS1302_Time[5], 2);
  }
}
