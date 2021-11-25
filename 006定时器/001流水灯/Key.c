#include <REGX52.H>
#include "DELAY.H"

/**
*获取独立按键序号
*/
unsigned char key()
{
  unsigned char num = 0;
  if (P3_1 == 0)
  {
    delayMs(20);
    while (P3_1 == 0)
      ;
    delayMs(20);
    num = 1;
  }
  if (P3_0 == 0)
  {
    delayMs(20);
    while (P3_0 == 0)
      ;
    delayMs(20);
    num = 2;
  }
  if (P3_2 == 0)
  {
    delayMs(20);
    while (P3_2 == 0)
      ;
    delayMs(20);
    num = 3;
  }
  if (P3_3 == 0)
  {
    delayMs(20);
    while (P3_3 == 0)
      ;
    delayMs(20);
    num = 4;
  }
  return num;
}
