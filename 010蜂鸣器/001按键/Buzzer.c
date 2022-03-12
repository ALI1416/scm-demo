#include <REGX52.H>
#include <INTRINS.H>

//蜂鸣器端口
sbit Buzzer = P2 ^ 5;

/**
  * @brief  蜂鸣器私有延时函数，延时500us
  */
void Buzzer_Delay500us()
{
  unsigned char i;
  _nop_();
  i = 227;
  while (--i)
    ;
}

/**
  * @brief  蜂鸣器发声(1000Hz)
  * @param  ms 发声的时长，范围：0~32767
  * @retval 无
  */
void Buzzer_Time(unsigned int ms)
{
  unsigned int i;
  for (i = 0; i < ms * 2; i++)
  {
    Buzzer = !Buzzer;
    Buzzer_Delay500us();
  }
}
