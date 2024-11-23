#include "stm32f10x.h"
#include "OLED.h"
#include "IC.h"

/**
 * 使用TIM3的通道1 PA6接口，去测量TIM2通道1 PA0接口的频率和占空比(PA0接PA6)
 */
int main()
{
  OLED_Init(RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_11, GPIOB, GPIO_Pin_10);
  IC_Init_PA6();
  // 配置预分频配置
  // TIM_PSCReloadMode 预分频器重装模式
  // TIM_PSCReloadMode_Update更新事件重装(下一个波形生效)
  // TIM_PSCReloadMode_Immediate立即重装(可能会切断波形)
  TIM_PrescalerConfig(TIM2, 720 - 1, TIM_PSCReloadMode_Immediate);
  TIM_SetCompare1(TIM2, 50);
  while (1)
  {
    OLED_ShowFixedNumber(0, 0, Get_IC_Freq_PA6(), 7);
  }
}

/**
 * @brief 获取PA6测量到的频率
 * @retval 频率(Hz)
 */
int Get_IC_Freq_PA6()
{
  // TIM_GetCapture1从0开始计算，要+1
  return 1000000 / (TIM_GetCapture1(TIM3) + 1);
}
