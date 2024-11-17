#include "stm32f10x.h"
#include "PWM.h"

/**
 * @brief  初始化直流电机(PWMA引脚接PA2，AIN1和AIN2接PA4和PA5)
 */
void Motor_Init(void)
{
  // 初始化方向控制PA4和PA5
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  // 人耳可听到的声音频率位20~20kHz，需要将频率调高
  // 频率20kHz 占空比1%
  // 72M/(PSC+1)/(ARR+1)=20000 --> PSC+1=36
  // CCR/(ARR+1)=1% --> CCR=1
  PWM_Init_PA2(36 - 1, 100 - 1, 0);
}

/**
 * @brief  设置直流电机转速
 * @param Speed 转速(-100~100)
 */
void Motor_SetSpeed(int8_t Speed)
{
  if (Speed >= 0)
  {
    GPIO_SetBits(GPIOA, GPIO_Pin_4);
    GPIO_ResetBits(GPIOA, GPIO_Pin_5);
    TIM_SetCompare3(TIM2, Speed);
  }
  else
  {
    GPIO_SetBits(GPIOA, GPIO_Pin_5);
    GPIO_ResetBits(GPIOA, GPIO_Pin_4);
    TIM_SetCompare3(TIM2, -Speed);
  }
}
