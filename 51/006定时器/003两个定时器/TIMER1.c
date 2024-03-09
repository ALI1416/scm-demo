#include <REGX52.H>

// 注意：定时器1不能和UART同时使用
void Timer1_Init()
{
  TMOD &= 0x0F; //设置定时器模式
  TMOD |= 0x10; //设置定时器模式
  TL1 = 0x00;   //设置定时初值
  TH1 = 0x4C;   //设置定时初值
  TF1 = 0;      //清除TF1标志
  TR1 = 1;      //定时器1开始计时
  ET1 = 1;
  EA = 1;
  PT1 = 0;
}

// 定时器1中断回调函数(每50ms)
// void Timer1_Routine() interrupt 3
// {
//   // 静态，防止被销毁
//   static unsigned int T0Count;
//   // 复位
//   TL1 = 0x00;
//   TH1 = 0x4C;
//   // 1s
//   if ((++T0Count) >= 20)
//   {
//     T0Count = 0;
//     // 代码
//   }
// }
