#include <REGX52.H>
#include "UART.H"
#include "TIMER0.H"
#include "DS18B20.H"
#include "LCD1602.H"
#include "OneWire.H"
#include "DELAY.H"
#include "Key.H"

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
// 温度整数部分(int)(Temp / 10000)
int TempInt;
// 高温报警
char TEMP_HIGH = 27;
// 低温报警
char TEMP_LOW = 26;

// LCD第二行刷新状态：0不可刷新；1可刷新
unsigned char LCD_ROW2_REFRESH_STATUS = 0;

// 调节按键序号：0切换调节；1数值+1；2数值-1；3退出调节
unsigned char KeyNum;

void main()
{
  Timer0_Init();
  UartInit();
  LCD_Init();
  // Temp:+123.4567℃
  //\xDF是℃左上角圆圈，\x43代表字母C
  LCD_ShowString(1, 1, "Temp:    .    \xDF\x43");
  // H+12L-34E10R01 H
  // H高温报警 L低温报警 T串口发送时间间隔 I温度读取时间间隔
  // 最后一个H代表温度过高，L代表温度过低，不显示代表温度正常
  LCD_ShowString(2, 1, "H   L   E  R");
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
      TempInt = (int)(Temp / 10000);
      LCD_ShowSignedNum(1, 6, TempInt, 3);                 //显示温度整数部分
      LCD_ShowNum(1, 11, (unsigned int)(Temp % 10000), 4); //显示温度小数部分
      // 显示高温还是低温
      if (TempInt >= TEMP_HIGH)
      {
        LCD_ShowChar(2, 16, 'H');
      }
      else if (TempInt < TEMP_LOW)
      {
        LCD_ShowChar(2, 16, 'L');
      }
      else
      {
        LCD_ShowChar(2, 16, ' ');
      }
      TEMP_CONVERT_STATUS = 0;
    }
    /* 温度串口发送时间到 */
    if (TEMP_SEND_STATUS == 1)
    {
      UartSendLong(Temp);
      TEMP_SEND_STATUS = 0;
    }
    /* LCD第二行刷新时间到 */
    if (LCD_ROW2_REFRESH_STATUS == 1)
    {
      // H+12L-34T10I01 H
      LCD_ShowSignedNum(2, 2, TEMP_HIGH, 2);
      LCD_ShowSignedNum(2, 6, TEMP_LOW, 2);
      LCD_ShowNum(2, 10, TEMP_SEND_TIME, 2);
      LCD_ShowNum(2, 13, TEMP_CONVERT_TIME, 2);
      LCD_ROW2_REFRESH_STATUS = 0;
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
  static unsigned int UART_Count, Temp_Convert_Count, Temp_Send_Count, //
      LCD_Row2_Refresh_Count, Key_Count;
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
  /* LCD显示器第二行刷新 每隔100毫秒 */
  if ((++LCD_Row2_Refresh_Count) >= 100)
  {
    LCD_Row2_Refresh_Count = 0;
    LCD_ROW2_REFRESH_STATUS = 1;
  }
  /* 按键驱动 每隔20毫秒 */
  if ((++Key_Count) >= 20)
  {
    Key_Loop();
  }
}
