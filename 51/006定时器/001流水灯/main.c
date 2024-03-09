#include <REGX52.H>
#include "DELAY.H"
#include "Key.h"
#include "TIMER0.H"
#include <INTRINS.H>

// 流水灯状态：循环右移
unsigned char status = 1;

void main()
{
  // 独立按键键码
  unsigned char keyNum = 0;
  // 流水灯初始状态，1号亮
  P2 = 0xFE;
  Timer0Init();
  while (1)
  {
    keyNum = key();
    if (keyNum)
    {
      // 按1号键，左
      if (keyNum == 1)
      {
        status = 0;
      }
      // 按2号键，右
      if (keyNum == 2)
      {
        status = 1;
      }
    }
  }
}

// 定时器0中断回调函数(每1ms)
void Timer0_Routine() interrupt 1
{
  // 静态，防止被销毁
  static unsigned int T0Count;
  // 复位
  TH0 = 0xFC;
  TL0 = 0x66;
  // 0.5s
  if ((++T0Count) >= 500)
  {
    T0Count = 0;
    if (status == 1)
    {
      // 循环左移一位，灯向右移
      P2 = _crol_(P2, 1);
    }
    else
    {
      // 循环右移一位，灯向左移
      P2 = _cror_(P2, 1);
    }
  }
}
