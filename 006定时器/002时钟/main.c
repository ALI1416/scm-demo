#include <REGX52.H>
#include "DELAY.H"
#include "LCD1602.h"
#include "TIMER0.H"
#include <INTRINS.H>

// 定义时分秒
unsigned char sec, min, hour;

void main()
{
  Timer0Init();
  LCD_Init();
  LCD_ShowString(1, 1, "Clock:");
  LCD_ShowString(2, 1, "  :  :");
  while (1)
  {
    LCD_ShowNum(2, 1, hour, 2);
    LCD_ShowNum(2, 4, min, 2);
    LCD_ShowNum(2, 7, sec, 2);
  }
}

void Timer0_Routine() interrupt 1
{
  static unsigned int T0Count;
  TH0 = 0xFC;
  TL0 = 0x66;
  if ((++T0Count) >= 1000)
  {
    T0Count = 0;
    // 由于显示LCD需要消费较多的时间
    // 但中断里面不能消耗时间太长，所以显示LCD放到主函数里面执行
    if (++sec == 60)
    {
      sec = 0;
      if (++min == 60)
      {
        min = 0;
        if (++hour == 24)
        {
          hour = 0;
        }
      }
    }
  }
}
