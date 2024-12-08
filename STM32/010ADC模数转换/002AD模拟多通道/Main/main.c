#include "stm32f10x.h"
#include "OLED.h"
#include "Delay.h"

void AD_Init_ADC1(void);
uint16_t AD_GetValue(uint8_t ADC_Channel);

/**
 * AD模拟多通道
 * 接PA0 PA1 PA2 PA3口
 */
int main()
{
  OLED_Init(RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_11, GPIOB, GPIO_Pin_10);
  AD_Init_ADC1();
  while (1)
  {
    // 手动切换通道
    OLED_ShowFixedNumber(0, 0, AD_GetValue(ADC_Channel_0), 4);
    OLED_ShowFixedNumber(1, 0, AD_GetValue(ADC_Channel_1), 4);
    OLED_ShowFixedNumber(2, 0, AD_GetValue(ADC_Channel_2), 4);
    OLED_ShowFixedNumber(3, 0, AD_GetValue(ADC_Channel_3), 4);
    Delay_ms(100);
  }
}

/**
 * @brief  初始化模数转换ADC1
 */
void AD_Init_ADC1(void)
{
  RCC_ADCCLKConfig(RCC_PCLK2_Div6);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  ADC_InitTypeDef ADC_InitStructue;
  ADC_InitStructue.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructue.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructue.ADC_ScanConvMode = DISABLE;
  ADC_InitStructue.ADC_ContinuousConvMode = DISABLE;
  ADC_InitStructue.ADC_NbrOfChannel = 1;
  ADC_InitStructue.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_Init(ADC1, &ADC_InitStructue);
  ADC_Cmd(ADC1, ENABLE);
  ADC_ResetCalibration(ADC1);
  while (ADC_GetResetCalibrationStatus(ADC1) == SET)
    ;
  ADC_StartCalibration(ADC1);
  while (ADC_GetCalibrationStatus(ADC1) == SET)
    ;
  // 初始化PA0 PA1 PA2 PA3
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  // 要使用模拟输入
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**
 * @brief  获取模数转换ADC1的值
 * @param ADC_Channel 通道
 * @retval 值 0~4095
 */
uint16_t AD_GetValue(uint8_t ADC_Channel)
{
  // 规则配置
  ADC_RegularChannelConfig(ADC1, ADC_Channel, 1, ADC_SampleTime_55Cycles5);
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
  while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET)
    ;
  return ADC_GetConversionValue(ADC1);
}
