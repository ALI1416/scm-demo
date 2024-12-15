#include "stm32f10x.h"
#include "OLED.h"
#include "USART.h"

/**
 * 使用轮询方法接收
 * 使用USART1 PA9为Tx(发送) PA10为Rx(接收)
 * USB转串口模块，VCC和3V3接跳线
 * GND接GND RXD接PA9 TXD接PA10
 */
int main()
{
  OLED_Init(RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_11, GPIOB, GPIO_Pin_10);
  USART1_Init();
  while (1)
  {
    // 数据接收寄存器非空标志位
    if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)
    {
      // 读取数据
      OLED_ShowHexNumber(0, 0, USART_ReceiveData(USART1));
      // 读取数据自动清除标志位
    }
  }
}
