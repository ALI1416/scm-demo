#include <REGX52.H>
#include "DELAY.H"
#include "UART.H"

/**
电脑接收数据：
STC-ISP小工具选择`串口助手`
串口选择`正确的串口`
波特率选择`4800`
校验位选择`无校验`
停止位选择`1位`
然后点击`打开串口`
*/
void main()
{
  unsigned char num = 0;
  UartInit();
  while (1)
  {
    UartSendByte(num++);
    delayMs(1000);
  }
}
