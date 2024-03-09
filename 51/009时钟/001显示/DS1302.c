#include <REGX52.H>

// 外部时钟脉冲：写数据1有效，读数据0有效
sbit DS1302_SCLK = P3 ^ 6;
// 读写数据IO
sbit DS1302_IO = P3 ^ 4;
// 读写操作有效
sbit DS1302_CE = P3 ^ 5;

//寄存器写入地址/指令定义
#define DS1302_SECOND 0x80 // 秒
#define DS1302_MINUTE 0x82 // 分
#define DS1302_HOUR 0x84   // 时
#define DS1302_DATE 0x86   // 日
#define DS1302_MONTH 0x88  // 月
#define DS1302_DAY 0x8A    // 星期
#define DS1302_YEAR 0x8C   // 年
#define DS1302_WP 0x8E     // 写保护

// 时间数组，索引0~6分别为年、月、日、时、分、秒、星期
unsigned char DS1302_Time[] = {21, 11, 28, 16, 15, 55, 7};

/**
  * @brief  DS1302初始化
  */
void DS1302_Init()
{
  DS1302_CE = 0;
  DS1302_SCLK = 0;
}

/**
  * @brief  DS1302写一个字节
  * @param  Command 命令字/地址
  * @param  Data    要写入的数据
  */
void DS1302_WriteByte(unsigned char Command, unsigned char Data)
{
  unsigned char i;
  // 开启可读写
  DS1302_CE = 1;
  // 发送命令
  for (i = 0; i < 8; i++)
  {
    // 发送1个bit到IO
    DS1302_IO = Command & (0x01 << i);
    // 高电平时钟脉冲，使DS1302接收命令
    DS1302_SCLK = 1;
    // 低电平时钟脉冲，继续发送数据
    // DS1302在200ns内就可接收数据，单片机执行1条命令要1us，所以不用延迟
    DS1302_SCLK = 0;
  }
  // 发送数据
  for (i = 0; i < 8; i++)
  {
    DS1302_IO = Data & (0x01 << i);
    DS1302_SCLK = 1;
    DS1302_SCLK = 0;
  }
  // 关闭可读写
  DS1302_CE = 0;
}

/**
  * @brief  DS1302读一个字节
  * @param  Command 命令字/地址
  * @retval 读出的数据
  */
unsigned char DS1302_ReadByte(unsigned char Command)
{
  unsigned char i;
  // 读到的数据
  unsigned char Data = 0x00;
  Command |= 0x01; //将指令转换为读指令
  DS1302_CE = 1;
  // 发送命令
  for (i = 0; i < 8; i++)
  {
    DS1302_IO = Command & (0x01 << i);
    DS1302_SCLK = 0;
    DS1302_SCLK = 1;
  }
  // 接收数据
  for (i = 0; i < 8; i++)
  {
    DS1302_SCLK = 1;
    DS1302_SCLK = 0;
    // 拼接数据
    if (DS1302_IO)
    {
      Data |= (0x01 << i);
    }
  }
  DS1302_CE = 0;
  //读取后将IO设置为0，否则读出的数据会出错
  DS1302_IO = 0;
  return Data;
}

/**
 * @brief BCD码转DEC码(2位)
 * @param  BCD BCD
 * @retval DEC
 */
unsigned char BCD2DEC(unsigned char BCD)
{
  return BCD / 16 * 10 + BCD % 16;
}

/**
 * @brief DEC码转BCD码(2位)
 * @param  DEC DEC
 * @retval BCD
 */
unsigned char DEC2BCD(unsigned char DEC)
{
  return DEC / 10 * 16 + DEC % 10;
}

/**
  * @brief  DS1302设置时间，调用之后，DS1302_Time数组的数字会被设置到DS1302中
  */
void DS1302_SetTime()
{
  DS1302_WriteByte(DS1302_WP, 0x00);
  DS1302_WriteByte(DS1302_YEAR, DEC2BCD(DS1302_Time[0]));
  DS1302_WriteByte(DS1302_MONTH, DEC2BCD(DS1302_Time[1]));
  DS1302_WriteByte(DS1302_DATE, DEC2BCD(DS1302_Time[2]));
  DS1302_WriteByte(DS1302_HOUR, DEC2BCD(DS1302_Time[3]));
  DS1302_WriteByte(DS1302_MINUTE, DEC2BCD(DS1302_Time[4]));
  DS1302_WriteByte(DS1302_SECOND, DEC2BCD(DS1302_Time[5]));
  DS1302_WriteByte(DS1302_DAY, DEC2BCD(DS1302_Time[6]));
  DS1302_WriteByte(DS1302_WP, 0x80);
}

/**
  * @brief  DS1302读取时间，调用之后，DS1302中的数据会被读取到DS1302_Time数组中
  */
void DS1302_ReadTime()
{
  DS1302_Time[0] = BCD2DEC(DS1302_ReadByte(DS1302_YEAR));
  DS1302_Time[1] = BCD2DEC(DS1302_ReadByte(DS1302_MONTH));
  DS1302_Time[2] = BCD2DEC(DS1302_ReadByte(DS1302_DATE));
  DS1302_Time[3] = BCD2DEC(DS1302_ReadByte(DS1302_HOUR));
  DS1302_Time[4] = BCD2DEC(DS1302_ReadByte(DS1302_MINUTE));
  DS1302_Time[5] = BCD2DEC(DS1302_ReadByte(DS1302_SECOND));
  DS1302_Time[6] = BCD2DEC(DS1302_ReadByte(DS1302_DAY));
}
