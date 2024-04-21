#include "stm32f10x.h"
#include "Buzzer.h"
#include "LightSensor.h"

/**
 * 光敏触发时蜂鸣器响
 * 蜂鸣器接B12
 * 光敏接B13
 */
int main()
{
  Buzzer_Init();
  LightSensor_Init();
  while (1)
  {
    // 光线暗 响
    if (LightSensor_Get() == 1)
    {
      Buzzer_ON();
    }
    // 光线亮 停
    else
    {
      Buzzer_OFF();
    }
  }
}
