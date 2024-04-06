#include "stm32f10x.h"

/**
 * @brief  延时n*1us
 * @param  n 延时1us的倍数，范围：0~233015
 */
void Delay_us(uint32_t n)
{
  // 设置定时器重装值
  SysTick->LOAD = 72 * n;
  // 清空当前计数值
  SysTick->VAL = 0x00;
  // 设置时钟源为HCLK，启动定时器
  SysTick->CTRL = 0x00000005;
  // 等待计数器到0
  while (!(SysTick->CTRL & 0x00010000))
    ;
  // 关闭定时器
  SysTick->CTRL = 0x00000004;
}

/**
 * @brief  延时n*1ms
 * @param  n 延时1ms的倍数，范围：0~4294967295
 */
void Delay_ms(uint32_t n)
{
  while (n--)
  {
    Delay_us(1000);
  }
}

/**
 * @brief  延时n*1s
 * @param  n 延时1s的倍数，范围：0~4294967295
 */
void Delay_s(uint32_t n)
{
  while (n--)
  {
    Delay_ms(1000);
  }
}
