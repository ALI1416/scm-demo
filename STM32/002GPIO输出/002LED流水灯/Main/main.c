#include "stm32f10x.h"
#include "delay.h"

/**
STM32数据类型
类型                关键字    位数  范围
char                int8_t    8   -128~127
unsigned char       uint8_t   8   0~255
short               int16_t   16  -32768~32767
unsigned short      uint16_t  16  0~65535
int                 int32_t   32  -2147483648~2147483647
unsigned int        uint32_t  32  0~4294967295
long                          32  -2147483648~2147483647
unsigned long                 32  0~4294967295
long long           int64_t   64  -2^63~2^63-1
unsigned long long  uint64_t  64  0~2^64-1
float                         32  3.4e-38~3.4e38
double                        64  1.7e-308~1.7e308
*/
/**
 * 使用8个LED 长脚插到正极，短脚插到A0到A7口
 */
int main()
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  // 初始化所有引脚
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  // 灯的位置
  uint8_t index = 0x01;
  while (1)
  {
    for (uint8_t i = 0; i < 8; i++)
    {
      // 亮
      GPIO_Write(GPIOA, ~index);
      // 左移一位
      index = index << 1;
      // 延时500毫秒
      delayMs(500);
    }
    // 复位
    index = 0x01;
  }
}
