#include <REGX52.H>
#include "UART.H"
#include "TIMER0.H"

// 接收数据数组长度
#define UART_RECEIVE_SIZE 8
// 接收数据数组
unsigned char UART_RECEIVE_DATA[UART_RECEIVE_SIZE];
// 下一个接收数据存放下标
unsigned char UART_RECEIVE_INDEX = 0;
// 接收状态：0未接收；1接收中；2被定时器中断函数打断；
// 3接收完成(数据要在UART_RECEIVE_SIZEms内发送完成，否则无效)
unsigned char UART_RECEIVE_STATUS = 0;

void main()
{
  Timer0_Init();
  UartInit();
  while (1)
  {
    // 数据接收完成
    if (UART_RECEIVE_STATUS == 3)
    {
      // 再把数据发送给电脑
      UartSendByteArray(UART_RECEIVE_DATA, UART_RECEIVE_INDEX);
      // 重置状态和下标
      UART_RECEIVE_INDEX = 0;
      UART_RECEIVE_STATUS = 0;
    }
  }
}

/**
* 串口中断
*/
void UART_Routine() interrupt 4
{
  // 接收中断
  if (RI == 1)
  {
    // 放满了，重头开始
    if (UART_RECEIVE_INDEX == UART_RECEIVE_SIZE)
    {
      // 重置状态和下标
      UART_RECEIVE_INDEX = 0;
      UART_RECEIVE_STATUS = 0;
    }
    // 放入数据
    UART_RECEIVE_DATA[UART_RECEIVE_INDEX++] = SBUF;
    // 接收中
    UART_RECEIVE_STATUS = 1;
    // 重置
    RI = 0;
  }
}

// 定时器0中断回调函数(每1ms)
void Timer0_Routine() interrupt 1
{
  // 静态，防止被销毁
  static unsigned int T0Count;
  // 复位
  TH0 = 0xFC;
  TL0 = 0x66;
  if ((++T0Count) >= UART_RECEIVE_SIZE)
  {
    T0Count = 0;
    // UART_RECEIVE被定时器中断函数打断
    if (UART_RECEIVE_STATUS == 1)
    {
      // 接收中，置为打断
      UART_RECEIVE_STATUS = 2;
    }
    else if (UART_RECEIVE_STATUS == 2)
    {
      // 打断，置为接收完成
      UART_RECEIVE_STATUS = 3;
    }
  }
  // 1s
  // if ((++T0Count) >= 1000)
  // {
  //   T0Count = 0;
  //   // 代码
  // }
}
