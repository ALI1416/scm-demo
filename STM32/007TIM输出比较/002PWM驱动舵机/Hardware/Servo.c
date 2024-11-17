#include "stm32f10x.h"
#include "PWM.h"

/**
 * @brief  初始化舵机(PWM引脚接PA1)
 */
void Servo_Init(void)
{
  // SG90舵机PWM信号要求：周期20ms旋转角度从-90度到90度，对应高电平宽度0.5ms到2.5ms
  // 频率20ms=50Hz 为了方便计算，ARR+1=20000，CCR为500~2500
  // 72M/(PSC+1)/(ARR+1)=50 --> PSC+1=72
  PWM_Init_PA1(72 - 1, 20000 - 1, 0);
}

/**
 * @brief  设置舵机角度
 * @param Angle 角度(0~180)
 */
void Servo_SetAngle(uint8_t Angle)
{
  // 角度0~180度对应CCR的值500~2500
  // 应该为angle/180*2000+500
  TIM_SetCompare2(TIM2, Angle * 100 / 9 + 500);
}
