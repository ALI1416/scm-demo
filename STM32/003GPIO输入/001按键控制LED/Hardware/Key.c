#include "stm32f10x.h"
#include "Delay.h"

/**
 * @brief  初始化Key B0、B1和B11
 */
void Key_Init(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  // 上拉输入：按下低电平、抬起高电平
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_11;
  // 输出速度：对输入无效
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/**
 * @brief  获取键码值
 * @retval 键码值
 * 0 没有按下
 * 1 B0
 * 2 B1
 * 3 B11
 */
uint8_t Key_GetNum(void)
{
  // 常用4个读取
  // GPIO_ReadInputDataBit 输入端bit
  // GPIO_ReadInputData 输入端数据
  // GPIO_ReadOutputDataBit 输出端bit
  // GPIO_ReadOutputData 输出端数据
  // 读取输入端1个bit时为0
  if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0)
  {
    /* 1 B0 */
    // 按下时防抖
    Delay_ms(20);
    // 等待抬起
    while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 1)
      ;
    // 抬起时防抖
    Delay_ms(20);
    return 1;
  }
  if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)
  {
    /* 2 B1 */
    Delay_ms(20);
    while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 1)
      ;
    Delay_ms(20);
    return 2;
  }
  if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0)
  {
    /* 3 B11 */
    Delay_ms(20);
    while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 1)
      ;
    Delay_ms(20);
    return 3;
  }
  return 0;
}
