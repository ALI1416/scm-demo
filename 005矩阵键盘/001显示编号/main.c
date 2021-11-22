#include <REGX52.H>
#include "LCD1602.H"
#include "MatrixKey.h"

/**
矩阵键盘是4x4的按键，由P10~P17寄存器储存数值
其中P17~P14控制1~4行，P13~P10控制1~4列
需要逐行或逐列扫描才能获取按下的键，由于采用逐行扫描蜂鸣器会一直响，所以采用逐列扫描
*/
void main()
{
  // 键盘编号
  unsigned char keyNum = 0;
  LCD_Init();
  LCD_ShowString(1, 1, "MatrixKey:");
  while (1)
  {
    // 读取当前按下的键
    keyNum = MatrixKey();
    if (keyNum)
    {
      LCD_ShowNum(2, 1, keyNum, 2);
    }
  }
}
