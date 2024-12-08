#include "stm32f10x.h"
#include "OLED.h"
#include "Delay.h"
#include "DMA.h"

uint8_t DataA[] = {1, 2, 3, 4};
uint8_t DataB[] = {0, 0, 0, 0};

/**
 * DMA内存到内存
 */
int main()
{
  OLED_Init(RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_11, GPIOB, GPIO_Pin_10);
  DMA_Init_Software((uint32_t)DataA, (uint32_t)DataB, 4);
  while (1)
  {
    OLED_ShowFixedNumber(0, 0, DataA[0], 2);
    OLED_ShowFixedNumber(1, 0, DataA[1], 2);
    OLED_ShowFixedNumber(2, 0, DataA[2], 2);
    OLED_ShowFixedNumber(3, 0, DataA[3], 2);
    OLED_ShowFixedNumber(0, 3, DataB[0], 2);
    OLED_ShowFixedNumber(1, 3, DataB[1], 2);
    OLED_ShowFixedNumber(2, 3, DataB[2], 2);
    OLED_ShowFixedNumber(3, 3, DataB[3], 2);
    DataA[0]++;
    DataA[1]++;
    DataA[2]++;
    DataA[3]++;
    DMA_Software_Transfer();
    Delay_s(1);
  }
}
