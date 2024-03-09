#include <REGX52.H>
#include "LCD1602.H"
#include "MatrixKey.h"

/**
S1~S9按键对应数字1-9，S10按键对应数字0，S11按键代表确认，S12按键代表取消
*/
void main()
{
  // 键盘编号
  unsigned char keyNum = 0;
  // 密码，4位
  unsigned int pwd = 0;
  // 已输入位数
  unsigned char count = 0;
  LCD_Init();
  LCD_ShowString(1, 1, "Password:");
  while (1)
  {
    keyNum = MatrixKey();
    if (keyNum)
    {
      // 按下的是S1~S10，输入0~9
      if (keyNum < 11)
      {
        // 输入超过4位继续输入无效
        if (count < 4)
        {
          count++;
          pwd *= 10;          // 向前移一位
          pwd += keyNum % 10; // S10对应数字0
          LCD_ShowNum(2, 1, pwd, 4);
        }
      }
      // S11代表确认
      else if (keyNum == 11)
      {
        // 正确密码是1234，输入正确显示OK，错误显示ERR
        if (pwd == 1234)
        {
          LCD_ShowString(1, 14, "OK ");
        }
        else
        {
          LCD_ShowString(1, 14, "ERR");
        }
        // 密码和已输入位数清零
        count = 0;
        pwd = 0;
        LCD_ShowNum(2, 1, pwd, 4);
      }
      // S12代表取消
      else if (keyNum = 12)
      {
        LCD_ShowString(1, 14, "   ");
        count = 0;
        pwd = 0;
        LCD_ShowNum(2, 1, pwd, 4);
      }
    }
  }
}
