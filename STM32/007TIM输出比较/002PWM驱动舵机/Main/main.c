#include "stm32f10x.h"
#include "OLED.h"
#include "Delay.h"
#include "Servo.h"
#include "Key.h"

uint32_t count = 0;

/**
 * PWM驱动舵机
 * 舵机棕色接GND 红色接STLINK 5V引脚 黄色PWM控制接PA1
 * SG90舵机PWM信号要求：周期20ms旋转角度从-90度到90度，对应高电平宽度0.5ms到2.5ms
 * 频率20ms=50Hz 为了方便计算，ARR+1=20000，CCR为500~2500
 * 72M/(PSC+1)/(ARR+1)=50 --> PSC+1=72
 * 按键接B0
 */
int main()
{
  uint8_t KeyNum = 0;
  uint8_t Angle = 0;
  OLED_Init(RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_11, GPIOB, GPIO_Pin_10);
  Servo_Init();
  Key_Init();
  Servo_SetAngle(Angle);
  OLED_ShowFixedNumber(0, 0, Angle, 3);
  while (1)
  {
    KeyNum = Key_GetNum();
    if (KeyNum == 1)
    {
      Angle += 30;
      if (Angle > 180)
      {
        Angle = 0;
      }
      Servo_SetAngle(Angle);
      OLED_ShowFixedNumber(0, 0, Angle, 3);
    }
  }
}
