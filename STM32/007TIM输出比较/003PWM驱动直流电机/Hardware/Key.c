#include "stm32f10x.h"
#include "Delay.h"

/**
 * @brief  初始化Key(低电平触发) B0
 */
void Key_Init(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/**
 * @brief  获取键码值
 * @retval 键码值
 * 0 没有按下
 * 1 B0
 */
uint8_t Key_GetNum(void)
{
  if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0)
  {
    Delay_ms(20);
    while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0)
      ;
    Delay_ms(20);
    return 1;
  }
  return 0;
}
