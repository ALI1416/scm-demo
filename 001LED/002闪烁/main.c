#include <REGX52.H>
#include <INTRINS.H>

/*
延迟500毫秒
打开STC-ISP软件，右侧窗口，点击向后，找到`软件延时计算器`
选择系统频率`12.000MHz`，定时长度`500毫秒`，8051指令集`STC-Y1`
`_nop_();`方法需要导入头部`#include <INTRINS.H>`
*/
void Delay500ms() //@12.000MHz
{
  unsigned char i, j, k;

  _nop_();
  i = 4;
  j = 205;
  k = 187;
  do
  {
    do
    {
      while (--k)
        ;
    } while (--j);
  } while (--i);
}

void main()
{
  // LED不断闪烁就是循环给负极高低电平
  while (1)
  {
    P2 = 0xFE;    // 亮
    Delay500ms(); // 延迟500毫秒
    P2 = 0xFF;    // 灭
    Delay500ms(); // 延迟500毫秒
  }
}
