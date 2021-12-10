#include <REGX52.H>
#include "DELAY.H"

/*
数码管显示数字，分别对应数值0~9
*/
unsigned char nixieTable[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
/*
定义数码管显示位置和数字
*/
void nixie(unsigned char location, unsigned char number)
{
  // 显示数字
  P0 = nixieTable[number];
  // 显示位置
  switch (location)
  {
  case 1:
  {
    P2_4 = 1;
    P2_3 = 1;
    P2_2 = 1;
    break;
  }
  case 2:
  {
    P2_4 = 1;
    P2_3 = 1;
    P2_2 = 0;
    break;
  }
  case 3:
  {
    P2_4 = 1;
    P2_3 = 0;
    P2_2 = 1;
    break;
  }
  case 4:
  {
    P2_4 = 1;
    P2_3 = 0;
    P2_2 = 0;
    break;
  }
  case 5:
  {
    P2_4 = 0;
    P2_3 = 1;
    P2_2 = 1;
    break;
  }
  case 6:
  {
    P2_4 = 0;
    P2_3 = 1;
    P2_2 = 0;
    break;
  }
  case 7:
  {
    P2_4 = 0;
    P2_3 = 0;
    P2_2 = 1;
    break;
  }
  case 8:
  {
    P2_4 = 0;
    P2_3 = 0;
    P2_2 = 0;
    break;
  }
  }
  // 为了避免数码管出现篡位，需要消影，只需要叫他显示一段时间，再清零就可以了
  delayMs(1);
  P0 = 0x00;
}
