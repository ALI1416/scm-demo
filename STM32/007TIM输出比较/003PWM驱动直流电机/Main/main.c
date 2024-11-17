#include "stm32f10x.h"
#include "OLED.h"
#include "Delay.h"
#include "Motor.h"
#include "Key.h"

uint32_t count = 0;

/**
 * PWM驱动直流电机
 * 直流电机驱动模块TB6612FNG
 * VM(电机电源)接STLINK 5V引脚
 * VCC(逻辑电源)接面包板3.3V
 * GND电源负极
 * AO1和AO2电机输出端，接电机两级(BO1和BO2是另一路电机输出端)
 * STBY待机控制，不需要待机，接3.3V
 * AIN1和AIN2方向控制，接PA4和PA5(BIN1和BIN2另一路方向控制)
 * PWMA速度控制，接PA2(PWMB另一路速度控制)
 * 按键接B0
 */
int main()
{
  uint8_t KeyNum = 0;
  int8_t Speed = 0;
  OLED_Init(RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_11, GPIOB, GPIO_Pin_10);
  Motor_Init();
  Key_Init();
  Motor_SetSpeed(Speed);
  OLED_ShowFixedSignedNumber(0, 0, Speed, 4);
  while (1)
  {
    KeyNum = Key_GetNum();
    if (KeyNum == 1)
    {
      Speed += 20;
      if (Speed > 100)
      {
        Speed = -100;
      }
      Motor_SetSpeed(Speed);
      OLED_ShowFixedSignedNumber(0, 0, Speed, 4);
    }
  }
}
