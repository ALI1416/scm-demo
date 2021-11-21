#include <REGX52.H>
// <>是查找系统路径，""是查找本地路径
#include "DELAY.H"
#include "NIXIE.H"

void main()
{
  while (1)
  {
    // 显示12345678
    nixie(1, 1);
    nixie(2, 2);
    nixie(3, 3);
    nixie(4, 4);
    nixie(5, 5);
    nixie(6, 6);
    nixie(7, 7);
    nixie(8, 8);
  }
}
