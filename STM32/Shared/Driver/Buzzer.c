#include "stm32f10x.h"

GPIO_TypeDef *Buzzer_GPIOx;
uint16_t Buzzer_GPIO_Pin;

/**
 * @brief  初始化蜂鸣器(低电平触发)
 * @param RCC_APB2Periph 外设组
 * @param GPIOx 外设名
 * @param GPIO_Pin 外设针脚
 */
void Buzzer_Init(uint32_t RCC_APB2Periph, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  Buzzer_GPIOx = GPIOx;
  Buzzer_GPIO_Pin = GPIO_Pin;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOx, &GPIO_InitStructure);
}

/**
 * @brief  蜂鸣器响
 */
void Buzzer_ON(void)
{
  GPIO_ResetBits(Buzzer_GPIOx, Buzzer_GPIO_Pin);
}

/**
 * @brief  蜂鸣器停
 */
void Buzzer_OFF(void)
{
  GPIO_SetBits(Buzzer_GPIOx, Buzzer_GPIO_Pin);
}
