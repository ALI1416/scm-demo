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
  // 移位个数
  unsigned char ledNum = 0;
  // 默认亮1号
  P2 = ~0x01;
  while (1)
  {
    // 按K1按钮
    if (P3_1 == 0)
    {
      delayMs(20);
      while (P3_1 == 0)
        ;
      delayMs(20);
      if (ledNum++ == 7) // 每按一次，移位+1
      {
        ledNum = 0; // 当大于8时归零
      }
      P2 = ~(0x01 << ledNum); // 取反
    }
    // 按K2按钮
    if (P3_0 == 0)
    {
      delayMs(20);
      while (P3_0 == 0)
        ;
      delayMs(20);
      if (ledNum-- == 0) // 每按一次，移位-1
      {
        ledNum = 7; // 当小于0时取最大
      }
      P2 = ~(0x01 << ledNum); // 取反
    }
  }
}
