#include "stm32f10x.h"

/**
 * @brief  初始化蜂鸣器(低电平触发) B12
 */
void Buzzer_Init(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/**
 * @brief  蜂鸣器响
 */
void Buzzer_ON(void)
{
  GPIO_ResetBits(GPIOB, GPIO_Pin_12);
}

/**
 * @brief  蜂鸣器停
 */
void Buzzer_OFF(void)
{
  GPIO_SetBits(GPIOB, GPIO_Pin_12);
}
