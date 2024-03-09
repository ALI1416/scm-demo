#include <REGX52.H>
#include "Key.h"
#include "Nixie.h"
#include "Motor.h"
#include "IR.h"

unsigned char Command, Speed;

void main()
{
  Motor_Init();
  IR_Init();
  while (1)
  {
    if (IR_GetDataFlag()) //如果收到数据帧
    {
      Command = IR_GetCommand(); //获取遥控器命令码

      if (Command == IR_0)
      {
        Speed = 0;
      } //根据遥控器命令码设置速度
      if (Command == IR_1)
      {
        Speed = 1;
      }
      if (Command == IR_2)
      {
        Speed = 2;
      }
      if (Command == IR_3)
      {
        Speed = 3;
      }
      if (Command == IR_4)
      {
        Speed = 4;
      }

      if (Speed == 0)
      {
        Motor_SetSpeed(0);
      } //速度输出
      if (Speed == 1)
      {
        Motor_SetSpeed(40);
      }
      if (Speed == 2)
      {
        Motor_SetSpeed(60);
      }
      if (Speed == 3)
      {
        Motor_SetSpeed(80);
      }
      if (Speed == 4)
      {
        Motor_SetSpeed(100);
      }
    }
    nixie(1, Speed); //数码管显示速度
  }
}
