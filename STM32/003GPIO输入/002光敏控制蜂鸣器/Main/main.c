#include "stm32f10x.h"
#include "Buzzer.h"
#include "LightSensor.h"

/**
 * 光敏/热敏触发时蜂鸣器响
 * 蜂鸣器接B12
 * 光敏/热敏接B13[DO(数字信号)]
 */
int main()
{
  Buzzer_Init(RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_12);
  LightSensor_Init(RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_13);
  while (1)
  {
    // 光线暗/温度低 响
    if (LightSensor_Get() == 1)
    {
      Buzzer_ON();
    }
    // 光线亮/温度高 停
    else
    {
      Buzzer_OFF();
    }
  }
}
