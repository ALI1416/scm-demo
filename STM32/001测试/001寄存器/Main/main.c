#include "stm32f10x.h"

int main()
{
  RCC->APB2ENR = 0x00000010;
  GPIOC->CRH = 0x00300000;
  // PC13亮
  GPIOC->ODR = 0x00000000;
  // PC13灭
  // GPIOC->ODR = 0x00002000;
  while (1)
  {
  }
}
