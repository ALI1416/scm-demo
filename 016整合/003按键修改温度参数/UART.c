#include <REGX52.H>

/**
UART串口通信初始化
STC-ISP，小工具找到`波频率计算器`
系统频率选择`11.0592MHz`
UART选择`串口1`
波特率选择`4800`
UART数据位选择`8位数据`
波特率加倍(SMOD)`不勾选`
波特率发生器选择`定时器1(8位自动重载)`
定时器时钟选择`12T(FOSC/12)`
删除掉代码中的AUXR
*/
void UartInit() //4800bps@11.0592MHz
{
  PCON &= 0x7F; //波特率不倍速
  SCON = 0x50;  //8位数据,可变波特率,可以接收
  TMOD &= 0x0F; //设置定时器模式
  TMOD |= 0x20; //设置定时器模式
  TL1 = 0xFA;   //设置定时初始值
  TH1 = 0xFA;   //设置定时重载值
  ET1 = 0;      //禁止定时器1中断
  TR1 = 1;      //定时器1开始计时
  EA = 1;       //启用所有中断
  ES = 1;       //启用串口中断
}

/**
* 发送1个字符
*/
void UartSendByte(unsigned char byte)
{
  // 把byte放到缓存里面
  SBUF = byte;
  // 等待把数据取走
  while (TI == 0)
    ;
  // 复位
  TI = 0;
}

/**
* 发送1个字符串(字符串结尾会自动加\0)
* 0x00(即\0)作为字符串结束符，如果需要发送0x00，那么发送2个0x00
*/
void UartSendString(unsigned char *str)
{
  unsigned char i = 0;
  while (1)
  {
    if (str[i] == 0)
    {
      if (str[++i] == 0)
      {
        i++;
        UartSendByte(0);
      }
      else
      {
        break;
      }
    }
    else
    {
      UartSendByte(str[i++]);
    }
  }
}

/**
* 发送字符数组，并指定只发送前几位
*/
void UartSendByteArray(unsigned char bytes[], unsigned char len)
{
  unsigned char i;
  for (i = 0; i < len; i++)
  {
    UartSendByte(bytes[i]);
  }
}

/**
 * 发送int，高位在前
 */
void UartSendInt(unsigned int i)
{
  UartSendByte(i >> 8);
  UartSendByte(i & 0x00FF);
}

/**
 * 发送long，高位在前
 */
void UartSendLong(unsigned long i)
{
  UartSendByte(i >> 24);
  UartSendByte((i & 0x00FF0000) >> 16);
  UartSendByte((i & 0x0000FF00) >> 8);
  UartSendByte(i & 0x000000FF);
}

// /**
// 串口中断
// */
// void UART_Routine() interrupt 4
// {
//   // 接收中断
//   if (RI == 1)
//   {
//     // 代码
//     RI = 0;
//   }
// }
