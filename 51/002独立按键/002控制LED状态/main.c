#include <REGX52.H>

/**
延时n*ms
*/
void delayMs(unsigned int n)
{
  unsigned int i = 0, j = 0;
  for (i = 0; i < n; i++)
    for (j = 0; j < 111; j++)
      ;
}

void main()
{
  while (1)
  {
    // 当按钮被按下时
    if (P3_1 == 0)
    {
      delayMs(20);      // 过滤掉按下时电流抖动5-10ms
      while (P3_1 == 0) // 当按钮还未松开时，不操作，松开后才执行下面操作
        ;
      delayMs(20);  // 过滤掉松开时电流抖动5-10ms
      P2_0 = ~P2_0; // 电平取反
    }
  }
}
