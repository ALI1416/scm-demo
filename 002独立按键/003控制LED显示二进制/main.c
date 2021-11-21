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
  // 定义灯显示的二进制数字
  unsigned char ledNum = 0;
  while (1)
  {
    if (P3_1 == 0)
    {
      delayMs(20);
      while (P3_1 == 0)
        ;
      delayMs(20);
      ledNum++;     // 每按一次，二进制+1
      P2 = ~ledNum; // 取反
    }
  }
}
