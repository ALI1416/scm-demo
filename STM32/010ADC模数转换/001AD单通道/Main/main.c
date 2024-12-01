#include "stm32f10x.h"
#include "OLED.h"
#include "AD.h"

/**
 * AD单通道
 * 接PA0口
 */
int main()
{
  OLED_Init(RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_11, GPIOB, GPIO_Pin_10);
  AD_Init_ADC1_PA0();
  while (1)
  {
    uint16_t value = AD_Init_ADC1_PA0_GetValue();
    OLED_ShowFixedNumber(0, 0, value, 5);
    // 数值波动过大，去除后4位
    OLED_ShowFixedNumber(1, 0, value >> 4, 5);
    // 电压3.3v，转换为mV
    OLED_ShowFixedNumber(2, 0, value * 3300 / 4095, 5);
  }
}
