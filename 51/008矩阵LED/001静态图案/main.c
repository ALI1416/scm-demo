#include <REGX52.H>
#include "DELAY.H"
#include "MatrixLED.H"

// 注意：要把矩阵LED左侧的插针插到左侧
void main()
{
  MatrixLED_Init();
  while (1)
  {
    MatrixLED_ShowColumn(0, 0x80);
    MatrixLED_ShowColumn(1, 0x40);
    MatrixLED_ShowColumn(2, 0x20);
    MatrixLED_ShowColumn(3, 0x10);
    MatrixLED_ShowColumn(4, 0x08);
    MatrixLED_ShowColumn(5, 0x04);
    MatrixLED_ShowColumn(6, 0x02);
    MatrixLED_ShowColumn(7, 0x01);
  }
}
