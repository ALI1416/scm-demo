#include "stm32f10x.h"
#include "Delay.h"
#include "LED.h"
#include "Key.h"

/**
 * 使用2个LED和3个按键
 * 当按键B0按下时切换LED A0亮、B1 A0灭
 * B11切换A1亮和灭
 * LED使用推挽输出，接A0和A1口
 * 按键使用上拉输入，接B0、B1和B11口
 */
int main()
{
  // 定义按键值
  uint8_t KeyNum = 0;
  LED_Init();
  Key_Init();
  while (1)
  {
    KeyNum = Key_GetNum();
    if (KeyNum == 1)
    {
      LED_ON_0();
    }
    if (KeyNum == 2)
    {
      LED_OFF_0();
    }
    if (KeyNum == 3)
    {
      LED_Toggle_1();
    }
  }
}
