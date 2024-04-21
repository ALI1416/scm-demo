#include "stm32f10x.h"

/**
 * @brief  初始化光敏传感器 B13
 */
void LightSensor_Init(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  // 上拉输入
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/**
 * @brief  获取值
 * @retval
 * 1 光线暗
 * 0 光线亮
 */
uint8_t LightSensor_Get(void)
{
  return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13);
}
