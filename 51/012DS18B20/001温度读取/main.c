#include <REGX52.H>
#include "LCD1602.H"
#include "DS18B20.h"
#include "DELAY.H"

void main()
{
  long T;
  DS18B20_ConvertT(); //上电先转换一次温度，防止第一次读数据错误
  delayMs(1000);      //等待转换完成
  LCD_Init();
  LCD_ShowString(1, 1, "Temperature:");
  while (1)
  {
    DS18B20_ConvertT();                              //转换温度
    T = DS18B20_ReadT();                             //读取温度
    LCD_ShowSignedNum(2, 1, (int)(T / 10000), 3);    //显示温度整数部分
    LCD_ShowChar(2, 5, '.');                         //显示小数点
    LCD_ShowNum(2, 6, (unsigned int)(T % 10000), 4); //显示温度小数部分
  }
}
