#include <REGX52.H>
#include "DELAY.H"

// 声明数据类型sbit
// 1bit数据(1位)，只能是0或1
// P3^5代表取P3的第5位数据(从0开始)
sbit RCK = P3 ^ 5; // RCLK bit发送到并口
sbit SCK = P3 ^ 6; // SRCLK bit下移
sbit SER = P3 ^ 4; // SER bit传入(高位)

// 使用数据类型sfr
// 1byte数据(8位)，从0x00~0xFF
// 只能使用#define取别名
#define MATRIX_LED P0

/**
74HC595芯片串转并
SER bit传入(高位)
SRCLK bit下移
RCLK bit发送到并口
*/
void _74HC595_WriteByte(unsigned char byte)
{
  unsigned char i;
  for (i = 0; i < 8; i++)
  {
    // byte按位传入，从高位到低位
    SER = byte & (0x80 >> i);
    // bit下移
    SCK = 1;
    SCK = 0;
  }
  // 发送到并口
  RCK = 1;
  RCK = 0;
}

/**
初始化
*/
void MatrixLED_Init()
{
  SCK = 0;
  RCK = 0;
}

/**
* @brief 矩阵LED显示一列数据
* @param col 第几列显示(0~7)
* @param d   显示数据
*/
void MatrixLED_ShowColumn(unsigned char col, unsigned char d)
{
  _74HC595_WriteByte(d);
  MATRIX_LED = ~(0x80 >> col);
  // 防止篡位
  delayMs(1);
  MATRIX_LED = 0xFF;
}
