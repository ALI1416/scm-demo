#include "stm32f10x.h"
#include "delay.h"

/**
 * GND接负极，IO接B12，VCC接正极
 */
int main()
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  while (1)
  {
    // 响
    GPIO_ResetBits(GPIOB, GPIO_Pin_12);
    // 延时500毫秒
    delayMs(500);
    // 停
    GPIO_SetBits(GPIOB, GPIO_Pin_12);
    // 延时500毫秒
    delayMs(500);
  }
}
