#include "stm32f10x.h"
#include "OLED.h"
#include "USART.h"

/**
 * 使用串口中断接收
 * 使用USART1 PA9为Tx(发送) PA10为Rx(接收)
 * USB转串口模块，VCC和3V3接跳线
 * GND接GND RXD接PA9 TXD接PA10
 */
int main()
{
  OLED_Init(RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_11, GPIOB, GPIO_Pin_10);
  USART1_Init();
  OLED_ShowHexNumber(0,0,0x11);
  while (1)
  {
    // 获取收到数据标志位
    // if (Serial_RxFlag_Get() == 1)
    // {
    //   // 读取数据
    //   OLED_ShowHexNumber(0, 0, Serial_RxData_Get());
    // }
  }
}

void USART1_IRQHandler(void)
{
  // 数据接收寄存器非空标志位
  if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
  {
    OLED_ShowHexNumber(0,0,USART_ReceiveData(USART1));
  }
}

