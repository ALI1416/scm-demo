#include <REGX52.H>

/*
C51数据类型
类型            位数  范围
int             16    -32768~32767
short           16    -32768~32767
long            32    -2147483648~2147483647
unsigned int    16    0~65535
unsigned short  16    0~65535
unsigned long   16    0~4294967295
float           32    3.4e-38~3.4e38
double          64    1.7e-308~1.7e308
char            8     -128~127
unsigned char   8     0~255
*/

/*
通过STC-ISP延时生成测试
延时1us：单独调用`_nop_();`函数
延时4us：声明空方法`void Delay4us(){}`
延时7us
void Delay7us()
{
  unsigned char i;
  i = 1;
  while (--i);
}
延时8us，多加了个`_nop_();`函数
void Delay8us()
{
  _nop_();
  unsigned char i;
  i = 1;
  while (--i);
}
延时9us，可见i增加1，延时时间增2us
void Delay9us()
{
  unsigned char i;
  i = 2;
  while (--i);
}
延时530us
void Delay530us()
{
  unsigned char i, j;
  i = 2;
  j = 4;
  do
  {
    while (--j)
      ;
  } while (--i);
}
延时532us，可见j增加1，延时时间增2us，i增加1，延时时间增512us
void Delay532us()
{
  unsigned char i, j;
  i = 2;
  j = 5;
  do
  {
    while (--j)
      ;
  } while (--i);
}
*/

// 延时n*10us
void delay10us(unsigned int n)
{
  while (n--)
    ;
}

// 延时n*ms
void delayMs(unsigned int n)
{
  unsigned int i = 0, j = 0;
  for (i = 0; i < n; i++)
    for (j = 0; j < 123; j++)
      ;
}

// 延时n*s
void delayM(unsigned int n)
{
  unsigned int i = 0, j = 0;
  for (i = 0; i < n; i++)
    for (j = 0; j < 21738; j++)
      ;
}

void main()
{
  // LED不断闪烁就是循环给负极高低电平
  while (1)
  {
    P2 = 0xFE;    // 亮 1111 1110
    delayMs(500); // 延迟500毫秒
    P2 = 0xFF;    // 灭
    delayMs(500);
    P2 = 0xFD; // 亮 1111 1101
    delayMs(500);
    P2 = 0xFF;
    delayMs(500);
    P2 = 0xFB; // 亮 1111 1011
    delayMs(500);
    P2 = 0xFF;
    delayMs(500);
    P2 = 0xF7; // 亮 1111 0111
    delayMs(500);
    P2 = 0xFF;
    delayMs(500);
    P2 = 0xEF; // 亮 1110 1111
    delayMs(500);
    P2 = 0xFF;
    delayMs(500);
    P2 = 0xDF; // 亮 1101 1111
    delayMs(500);
    P2 = 0xFF;
    delayMs(500);
    P2 = 0xBF; // 亮 1011 1111
    delayMs(500);
    P2 = 0xFF;
    delayMs(500);
    P2 = 0x7F; // 亮 0111 1111
    delayMs(500);
    P2 = 0xFF;
    delayMs(500);
  }
}
