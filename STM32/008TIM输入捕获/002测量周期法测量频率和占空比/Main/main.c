#include "stm32f10x.h"
#include "OLED.h"
#include "PWM.h"
#include "IC.h"

uint16_t Get_IC_Freq_PA6(void);
uint16_t Get_IC_Duty_PA6(void);

/**
 * 使用TIM3的通道1 PA6接口，去测量TIM2通道1 PA0接口的频率(PA0接PA6)
 */
int main()
{
  OLED_Init(RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_11, GPIOB, GPIO_Pin_10);
  // 1kHz 60%占空比
  PWM_Init_PA0(720 - 1, 100 - 1, 60);
  IC_PWMI_Init_PA6();
  // 配置预分频配置
  // TIM_PSCReloadMode 预分频器重装模式
  // TIM_PSCReloadMode_Update 更新事件重装(下一个波形生效)
  // TIM_PSCReloadMode_Immediate 立即重装(可能会切断波形)
  // 修改为10kHz 50%占空比
  // TIM_PrescalerConfig(TIM2, 72 - 1, TIM_PSCReloadMode_Immediate);
  // TIM_SetCompare1(TIM2, 50);
  while (1)
  {
    OLED_ShowFixedNumber(0, 0, Get_IC_Freq_PA6(), 7);
    OLED_ShowFixedNumber(1, 0, Get_IC_Duty_PA6(), 5);
  }
}

/**
 * @brief 获取PA6测量到的频率
 * @retval 频率(Hz)
 */
uint16_t Get_IC_Freq_PA6(void)
{
  uint16_t ccr = TIM_GetCapture1(TIM3);
  if (ccr == 0)
  {
    return ccr;
  }
  return 1000000 / (ccr + 1);
}

/**
 * @brief 获取PA6测量到的占空比
 * @retval 占空比(0.01%)
 */
uint16_t Get_IC_Duty_PA6(void)
{
  uint16_t ccr1 = TIM_GetCapture1(TIM3);
  uint16_t ccr2 = TIM_GetCapture2(TIM3);
  if (ccr2 == 0)
  {
    return 0;
  }
  return (ccr2 + 1) * 10000 / (ccr1 + 1);
}
