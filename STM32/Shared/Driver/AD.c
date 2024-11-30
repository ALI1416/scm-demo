#include "stm32f10x.h"

/**
 * @brief  初始化模数转换ADC1在PA0口(ADC1通道1)
 */
void AD_Init_ADC1_PA0(void)
{
  // 配置ADCCLK分频器 可以对APB2的72MHz时钟选择2,4,6,8分频 输入到ADCCLK
  // RCC_PCLK2_Div6 使用6分频 变成12MHz
  RCC_ADCCLKConfig(RCC_PCLK2_Div6);
  // 配置ADC
  // 在stm32f10x_adc文件里
  // ADC_DeInit 恢复默认配置
  // ADC_Init 初始化ADC
  // ADC_StructInit 给ADC结构体默认值
  // ADC_Cmd 使能ADC
  // ADC_DMACmd 使能ADC的DMA数据转运
  // ADC_ITConfig 配置中断输出
  // ADC_ResetCalibration 复位校准
  // ADC_GetResetCalibrationStatus 获取复位校准状态
  // ADC_StartCalibration 开始校准
  // ADC_GetCalibrationStatus 获取开始校准状态
  // ADC_SoftwareStartConvCmd 软件触发转换
  // ADC_GetSoftwareStartConvStatus 获取软件开始转换状态(只能获取是否已经开始转换，不能获取转换是否结束)
  // ADC_DiscModeChannelCountConfig 配置间断模式
  // ADC_DiscModeCmd 使能间断模式
  // ADC_RegularChannelConfig 规则组通道配置
  // ADC_ExternalTrigConvCmd 使能外部触发转换
  // ADC_GetConversionValue 获取转换值
  // ADC_GetDualModeConversionValue 获取双模转换值
  // Injected 注入组
  // Watchdog 看门狗
  // ADC_TempSensorVrefintCmd 使能温度传感器和内部参考电压转换
  // ADC_GetFlagStatus 和 ADC_GetITStatus (中断函数内部使用) 获取标志位是否被置SET
  // ADC_ClearFlag 和 ADC_ClearITPendingBit (中断函数内部使用) 对置SET的标志位进行清除
  RCC_APB2PeriphClockCmd(RCC_APB1Periph_ADC1, ENABLE);
  // 配置规则组通道配置 使用通道0 
  ADC_RegularChannelConfig(ADC1,ADC_Channel_0);
  // 初始化PA0
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  // 要使用模拟输入
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}
