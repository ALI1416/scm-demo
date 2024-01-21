#include <REGX52.H>
#include "UART.H"
#include "TIMER0.H"
#include "DS18B20.H"
#include "OneWire.H"
#include "DELAY.H"
#include "AT24C02.h"

// 接收数据数组长度
#define UART_RECEIVE_SIZE 8
// 接收数据数组
unsigned char UART_RECEIVE_DATA[UART_RECEIVE_SIZE];
// 下一个接收数据存放下标
unsigned char UART_RECEIVE_INDEX = 0;
// 接收状态：0未接收；1接收中；2被定时器中断函数打断；
// 3接收完成(数据要在UART_RECEIVE_SIZE毫秒内发送完成，否则无效)
unsigned char UART_RECEIVE_STATUS = 0;

// 温度最大值(实际为125)
char TEMP_MAX = 99;
// 温度最小值(实际为-55)
char TEMP_MIN = -55;
// 温度转换间隔最大值(秒)
unsigned char TEMP_CONVERT_MAX = 60;
// 温度转换间隔最小值(秒)
unsigned char TEMP_CONVERT_MIN = 1;
// 温度转换间隔(秒)
unsigned char TEMP_CONVERT_TIME = 1;
// 温度串口发送最大值(秒)
unsigned char TEMP_SEND_MAX = 60;
// 温度串口发送最小值(秒)
unsigned char TEMP_SEND_MIN = 1;
// 温度串口发送间隔(秒)
unsigned char TEMP_SEND_TIME = 10;
// 温度转换状态：0不可转换；1可转换
unsigned char TEMP_CONVERT_STATUS = 1;
// 温度串口发送状态：0不可发送；1可发送
unsigned char TEMP_SEND_STATUS = 0;
// 温度*10000
long Temp;
// 温度整数部分(char)(Temp / 10000)
char TempInt;
// 高温报警
char TEMP_HIGH = 30;
// 低温报警
char TEMP_LOW = 20;
// 温度报警状态：0正常；bit0(0x01)温度过高；bit1(0x02)温度过低
unsigned char TEMP_ALARM_STATUS;
// 显示的温度设置(未保存)
char THighShow, TLowShow, TSendShow, TConvertShow;

// 温度设置刷新状态：0不可刷新；1可刷新
unsigned char TEMP_SET_REFRESH_STATUS = 0;

void main()
{
  // 存储器里面的温度设置
  char THigh, TLow, TSend, TConvert;
  Timer0_Init();
  UartInit();
  // 读取存储器里面的温度设置
  THigh = AT24C02_ReadByte(0);
  TLow = AT24C02_ReadByte(1);
  TSend = AT24C02_ReadByte(2);
  TConvert = AT24C02_ReadByte(3);
  // 存储器里的数据正确，才保存
  if (THigh <= TEMP_MAX && TLow >= TEMP_MIN && THigh > TLow                 //
      && TSend > TEMP_SEND_MIN - 1 && TSend < TEMP_SEND_MAX + 1             //
      && TConvert > TEMP_CONVERT_MIN - 1 && TConvert < TEMP_CONVERT_MAX + 1 //
      && TSend >= TConvert)
  {
    TEMP_HIGH = THigh;
    TEMP_LOW = TLow;
    TEMP_SEND_TIME = TSend;
    TEMP_CONVERT_TIME = TConvert;
  }
  THighShow = TEMP_HIGH;
  TLowShow = TEMP_LOW;
  TSendShow = TEMP_SEND_TIME;
  TConvertShow = TEMP_CONVERT_TIME;
  // 上电先转换一次温度，防止第一次读数据错误
  DS18B20_ConvertT();
  // 等待转换完成
  delayMs(500);
  while (1)
  {
    // 数据交互格式：
    // 事件(单片机 --> 网关)：0x00 - 0x3F
    //   温度事件：0x00
    //     温度x10000(32bit)
    // 故障(单片机 --> 网关)：0x40 - 0x7F
    //   温度报警：0x40
    //     温度报警状态(8bit)
    // 互动请求(网关 --> 单片机)：0x80 - 0xBF
    //   设置温度参数：0x80
    //     F温度读取时间间隔 C串口发送时间间隔 H高温报警 L低温报警(32bit)
    //   读取温度参数：0x81
    // 互动响应(单片机 --> 网关)：0xC0 - 0xFF
    //   设置温度参数：0xC0
    //     设置状态(8bit) 0x00成功 0x01失败
    //   读取温度参数：0xC1
    //     F温度读取时间间隔 C串口发送时间间隔 H高温报警 L低温报警(32bit)
    /* 数据接收完成 */
    if (UART_RECEIVE_STATUS == 3)
    {
      unsigned char FLAG = UART_RECEIVE_DATA[0];
      // 设置温度参数请求：0x80
      if (FLAG == 0x80)
      {
        // F温度读取时间间隔
        TConvert = UART_RECEIVE_DATA[1];
        // C串口发送时间间隔
        TSend = UART_RECEIVE_DATA[2];
        // H高温报警
        THigh = UART_RECEIVE_DATA[3];
        // L低温报警
        TLow = UART_RECEIVE_DATA[4];
        // 数据正确
        if (THigh <= TEMP_MAX && TLow >= TEMP_MIN && THigh > TLow                 //
            && TSend > TEMP_SEND_MIN - 1 && TSend < TEMP_SEND_MAX + 1             //
            && TConvert > TEMP_CONVERT_MIN - 1 && TConvert < TEMP_CONVERT_MAX + 1 //
            && TSend >= TConvert)
        {
          TEMP_HIGH = THigh;
          TEMP_LOW = TLow;
          TEMP_SEND_TIME = TSend;
          TEMP_CONVERT_TIME = TConvert;
          THighShow = TEMP_HIGH;
          TLowShow = TEMP_LOW;
          TSendShow = TEMP_SEND_TIME;
          TConvertShow = TEMP_CONVERT_TIME;
          // 写入数据到存储器
          AT24C02_WriteByte(0, TEMP_HIGH);
          delayMs(5);
          AT24C02_WriteByte(1, TEMP_LOW);
          delayMs(5);
          AT24C02_WriteByte(2, TEMP_SEND_TIME);
          delayMs(5);
          AT24C02_WriteByte(3, TEMP_CONVERT_TIME);
          // 设置温度参数响应：0xC0
          UartSendByte(0xC0);
          // 0x00 成功
          UartSendByte(0x00);
        }
        // 数据错误
        else
        {
          // 设置温度参数响应：0xC0
          UartSendByte(0xC0);
          // 0x01 失败
          UartSendByte(0x01);
        }
      }
      // 读取温度参数请求：0x81
      if (FLAG == 0x81)
      {
        // 读取温度参数响应：0xC1
        UartSendByte(0xC1);
        // F温度读取时间间隔
        UartSendByte(TEMP_CONVERT_TIME);
        // C串口发送时间间隔
        UartSendByte(TEMP_SEND_TIME);
        // H高温报警
        UartSendByte(TEMP_HIGH);
        // L低温报警
        UartSendByte(TEMP_LOW);
      }
      // 重置状态和下标
      UART_RECEIVE_INDEX = 0;
      UART_RECEIVE_STATUS = 0;
    }
    /* 温度串口发送时间到 */
    if (TEMP_SEND_STATUS == 1)
    {
      unsigned char t0 = Temp >> 24;
      unsigned char t1 = (Temp & 0x00FF0000) >> 16;
      unsigned char t2 = (Temp & 0x0000FF00) >> 8;
      unsigned char t3 = Temp & 0x000000FF;
      // 温度事件：0x00
      UartSendByte(0x00);
      // 温度x10000
      UartSendByte(t0);
      UartSendByte(t1);
      UartSendByte(t2);
      UartSendByte(t3);
      if (TEMP_ALARM_STATUS != 0)
      {
        delayMs(10);
        // 温度报警：0x40
        UartSendByte(0x40);
        // 温度报警状态
        UartSendByte(TEMP_ALARM_STATUS);
      }
      TEMP_SEND_STATUS = 0;
    }
    /* 温度转换时间到 */
    if (TEMP_CONVERT_STATUS == 1)
    {
      // 温度转换
      DS18B20_ConvertT();
      Temp = DS18B20_ReadT();
      // 显示温度
      TempInt = (char)(Temp / 10000);
      // 显示高温还是低温
      if (TempInt >= TEMP_HIGH)
      {
        // 温度过高
        TEMP_ALARM_STATUS = 0x01;
      }
      else if (TempInt < TEMP_LOW)
      {
        // 温度过低
        TEMP_ALARM_STATUS = 0x02;
      }
      else
      {
        // 正常
        TEMP_ALARM_STATUS = 0;
      }
      TEMP_CONVERT_STATUS = 0;
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
  static unsigned int UART_Count, Key_Count, //
      Temp_Convert_Count, Temp_Send_Count,   //
      Temp_Set_Refresh_Count, Temp_Set_Flash_Count;
  // 复位
  TL0 = 0x66;
  TH0 = 0xFC;
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
