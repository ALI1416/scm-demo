#include "stm32f10x.h"

GPIO_TypeDef *InfraredSensor_GPIOx;
uint16_t InfraredSensor_GPIO_Pin;

/**
 * @brief  初始化对射式红外传感器
 * @param RCC_APB2Periph 外设组
 * @param GPIOx 外设名
 * @param GPIO_Pin 外设针脚
 */
void InfraredSensor_Init(uint32_t RCC_APB2Periph, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  InfraredSensor_GPIOx = GPIOx;
  InfraredSensor_GPIO_Pin = GPIO_Pin;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOx, &GPIO_InitStructure);
}
