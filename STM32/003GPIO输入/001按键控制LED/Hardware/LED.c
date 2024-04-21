#include "stm32f10x.h"

/**
 * @brief  初始化LED(低电平点亮) A0和A1
 */
void LED_Init(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  // 默认：灭
  GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1);
}

/**
 * @brief  点亮LED A0
 */
void LED_ON_0(void)
{
  GPIO_ResetBits(GPIOA, GPIO_Pin_0);
}

/**
 * @brief  熄灭LED A0
 */
void LED_OFF_0(void)
{
  GPIO_SetBits(GPIOA, GPIO_Pin_0);
}

/**
 * @brief  切换LED A0状态
 */
void LED_Toggle_0(void)
{
  // 获取当前状态：0亮1灭
  uint8_t status = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0);
  // 切换
  GPIO_WriteBit(GPIOA, GPIO_Pin_0, status == 0 ? Bit_SET : Bit_RESET);
}

/**
 * @brief  点亮LED A1
 */
void LED_ON_1(void)
{
  GPIO_ResetBits(GPIOA, GPIO_Pin_1);
}

/**
 * @brief  熄灭LED A1
 */
void LED_OFF_1(void)
{
  GPIO_SetBits(GPIOA, GPIO_Pin_1);
}

/**
 * @brief  切换LED A1状态
 */
void LED_Toggle_1(void)
{
  GPIO_WriteBit(GPIOA, GPIO_Pin_1, GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1) == 0 ? Bit_SET : Bit_RESET);
}
