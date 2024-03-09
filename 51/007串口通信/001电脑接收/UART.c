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
  SCON = 0x40;  //8位数据,可变波特率,不可接收
  TMOD &= 0x0F; //设置定时器模式
  TMOD |= 0x20; //设置定时器模式
  TL1 = 0xFA;   //设置定时初始值
  TH1 = 0xFA;   //设置定时重载值
  ET1 = 0;      //禁止定时器1中断
  TR1 = 1;      //定时器1开始计时
}

/**
发送1个字符
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
