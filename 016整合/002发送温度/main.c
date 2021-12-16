#include <REGX52.H>
#include "UART.H"
#include "TIMER0.H"
#include "DS18B20.H"
#include "LCD1602.H"
#include "OneWire.H"

// 接收数据数组长度
#define UART_RECEIVE_SIZE 8
// 接收数据数组
unsigned char UART_RECEIVE_DATA[UART_RECEIVE_SIZE];
// 下一个接收数据存放下标
unsigned char UART_RECEIVE_INDEX = 0;
// 接收状态：0未接收；1接收中；2被定时器中断函数打断；
// 3接收完成(数据要在UART_RECEIVE_SIZE毫秒内发送完成，否则无效)
unsigned char UART_RECEIVE_STATUS = 0;

// 温度转换间隔(秒)(范围：1-65)
unsigned char TEMP_CONVERT_TIME = 1;
// 温度串口发送间隔(秒)(范围：1-65)
unsigned char TEMP_SEND_TIME = 10;
// 温度转换状态：0不可转换；1可转换
unsigned char TEMP_CONVERT_STATUS = 0;
// 温度串口发送状态：0不可发送；1可发送
unsigned char TEMP_SEND_STATUS = 0;
// 温度*10000
long Temp;

void main()
{
  Timer0_Init();
  UartInit();
  LCD_Init();
  LCD_ShowString(1, 1, "Temperature:");
  DS18B20_ConvertT(); //上电先转换一次温度，防止第一次读数据错误
  while (1)
  {
    /* 数据接收完成 */
    if (UART_RECEIVE_STATUS == 3)
    {
      // 再把数据发送给电脑
      UartSendByteArray(UART_RECEIVE_DATA, UART_RECEIVE_INDEX);
      // 重置状态和下标
      UART_RECEIVE_INDEX = 0;
      UART_RECEIVE_STATUS = 0;
    }
    /* 温度转换时间到 */
    if (TEMP_CONVERT_STATUS == 1)
    {
      // 温度转换
      DS18B20_ConvertT();
      Temp = DS18B20_ReadT();
      //LCD去显示
      LCD_ShowSignedNum(2, 1, (int)(Temp / 10000), 3);    //显示温度整数部分
      LCD_ShowChar(2, 5, '.');                            //显示小数点
      LCD_ShowNum(2, 6, (unsigned int)(Temp % 10000), 4); //显示温度小数部分
      TEMP_CONVERT_STATUS = 0;
    }
    /* 温度串口发送时间到 */
    if (TEMP_SEND_STATUS == 1)
    {
      UartSendLong(Temp);
      TEMP_SEND_STATUS = 0;
    }
  }
}

/**
* 串口中断
*/
void UART_Routine() interrupt 4
{
  /* 接收中断 */
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

/**
* 定时器0中断回调函数(每1ms)
*/
void Timer0_Routine() interrupt 1
{
  // 静态，防止被销毁
  static unsigned int UART_Count, Temp_Convert_Count, Temp_Send_Count;
  // 复位
  TH0 = 0xFC;
  TL0 = 0x66;
  /* 串口接收 每隔UART_RECEIVE_SIZE毫秒 */
  if ((++UART_Count) >= UART_RECEIVE_SIZE)
  {
    UART_Count = 0;
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
  /* 温度转换 每隔TEMP_SEND_TIME秒 */
  if ((++Temp_Convert_Count) >= 1000 * TEMP_CONVERT_TIME)
  {
    Temp_Convert_Count = 0;
    TEMP_CONVERT_STATUS = 1;
  }
  /* 温度串口发送 每隔TEMP_SEND_TIME秒 */
  if ((++Temp_Send_Count) >= 1000 * TEMP_SEND_TIME)
  {
    Temp_Send_Count = 0;
    TEMP_SEND_STATUS = 1;
  }
}
