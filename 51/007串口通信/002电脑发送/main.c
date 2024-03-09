#include <REGX52.H>
#include "UART.H"

void main()
{
  UartInit();
  while (1)
  {
  }
}

/**
串口中断
*/
void UART_Routine() interrupt 4
{
  // 接收中断
  if (RI == 1)
  {
    // 灯亮
    P2 = ~SBUF;
    // 再把数据发送给电脑
    UartSendByte(SBUF);
    // 重置
    RI = 0;
  }
}
