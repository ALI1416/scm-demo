#include <REGX52.H>
#include "LCD1602.h"
#include "DS18B20.h"
#include "Delay.h"
#include "AT24C02.h"
#include "Key.h"
#include "Timer0.h"

void main()
{
  long T;
  char TShow, TLow, THigh;
  unsigned char KeyNum = 0;
  DS18B20_ConvertT();          //上电先转换一次温度，防止第一次读数据错误
  delayMs(1000);               //等待转换完成
  THigh = AT24C02_ReadByte(0); //读取温度阈值数据
  TLow = AT24C02_ReadByte(1);
  if (THigh > 125 || TLow < -55 || THigh <= TLow)
  {
    THigh = 20; //如果阈值非法，则设为默认值
    TLow = 15;
  }
  LCD_Init();
  LCD_ShowString(1, 1, "T:");
  LCD_ShowString(2, 1, "TH:");
  LCD_ShowString(2, 9, "TL:");
  LCD_ShowSignedNum(2, 4, THigh, 3);
  LCD_ShowSignedNum(2, 12, TLow, 3);
  Timer0_Init();

  while (1)
  {
    KeyNum = Key();

    /*温度读取及显示*/
    DS18B20_ConvertT();                              //转换温度
    T = DS18B20_ReadT();                             //读取温度
    TShow = (int)(T / 10000);                        //显示温度(整数部分)
    LCD_ShowSignedNum(1, 3, (int)(T / 10000), 3);    //显示温度整数部分
    LCD_ShowChar(1, 7, '.');                         //显示小数点
    LCD_ShowNum(1, 8, (unsigned int)(T % 10000), 4); //显示温度小数部分

    /*阈值判断及显示*/
    if (KeyNum)
    {
      if (KeyNum == 1) //K1按键，THigh自增
      {
        if (THigh < 30)
        {
          THigh++;
        }
      }
      if (KeyNum == 2) //K2按键，THigh自减
      {
        if (THigh > TLow + 1)
        {
          THigh--;
        }
      }
      if (KeyNum == 3) //K3按键，TLow自增
      {
        if (TLow < THigh - 1)
        {
          TLow++;
        }
      }
      if (KeyNum == 4) //K4按键，TLow自减
      {
        if (TLow > 10)
        {
          TLow--;
        }
      }
      LCD_ShowSignedNum(2, 4, THigh, 3); //显示阈值数据
      LCD_ShowSignedNum(2, 12, TLow, 3);
      AT24C02_WriteByte(0, THigh); //写入到At24C02中保存
      delayMs(5);
      AT24C02_WriteByte(1, TLow);
      delayMs(5);
    }
    if (TShow >= THigh) //越界判断
    {
      LCD_ShowString(1, 13, "OV:H");
    }
    else if (TShow < TLow)
    {
      LCD_ShowString(1, 13, "OV:L");
    }
    else
    {
      LCD_ShowString(1, 13, "    ");
    }
  }
}

void Timer0_Routine() interrupt 1
{
  static unsigned int T0Count;
  TL0 = 0x66; //设置定时初值
  TH0 = 0xFC; //设置定时初值
  T0Count++;
  if (T0Count >= 20)
  {
    T0Count = 0;
    Key_Loop(); //每20ms调用一次按键驱动函数
  }
}
