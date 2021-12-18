#include <REGX52.H>
#include "TIMER0.H"
#include "TIMER1.H"

void main()
{
  Timer0_Init();
  Timer1_Init();
  while (1)
  {
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
  // 1s
  if ((++T0Count) >= 1000)
  {
    T0Count = 0;
    // 代码
    P2_0 = ~P2_0;
  }
}

// 定时器1中断回调函数(每50ms)
void Timer1_Routine() interrupt 3
{
  // 静态，防止被销毁
  static unsigned int T1Count;
  // 复位
  TL1 = 0x00;
  TH1 = 0x4C;
  // 1s
  if ((++T1Count) >= 20)
  {
    T1Count = 0;
    // 代码
    P2_1 = ~P2_1;
  }
}