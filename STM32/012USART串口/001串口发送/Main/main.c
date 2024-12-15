#include "stm32f10x.h"
#include "OLED.h"
#include "Delay.h"
#include "USART.h"

/**
 * 串口发送
 * 使用USART1 PA9为Tx(发送) PA10为Rx(接收)
 * USB转串口模块，VCC和3V3接跳线
 * GND接GND RXD接PA9 TXD接PA10
 */
int main()
{
  OLED_Init(RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_11, GPIOB, GPIO_Pin_10);
  USART1_Tx_Init();
  while (1)
  {
    USART1_Send_Byte(0x41);
    Delay_s(1);
    USART1_Send_Bytes({0x42, 0x43, 0x44});
    Delay_s(1);
    USART1_Send_String("EFDH");
    Delay_s(1);
  }
}
