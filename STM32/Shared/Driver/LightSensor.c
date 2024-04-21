#include "stm32f10x.h"

GPIO_TypeDef *LightSensor_GPIOx;
uint16_t LightSensor_GPIO_Pin;

/**
 * @brief  初始化光敏传感器
 * @param RCC_APB2Periph 外设组
 * @param GPIOx 外设名
 * @param GPIO_Pin 外设针脚
 */
void LightSensor_Init(uint32_t RCC_APB2Periph, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  // 上拉输入
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOx, &GPIO_InitStructure);
  LightSensor_GPIOx = GPIOx;
  LightSensor_GPIO_Pin = GPIO_Pin;
}

/**
 * @brief  获取值
 * @retval
 * 1 光线暗
 * 0 光线亮
 */
uint8_t LightSensor_Get(void)
{
  return GPIO_ReadInputDataBit(LightSensor_GPIOx, LightSensor_GPIO_Pin);
}
