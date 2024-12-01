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
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  // 配置规则组通道配置
  // ADC_Channel 通道
  // Rank 次序 1~16
  // ADC_SampleTime 采样时间(ADCLK周期) 越小越快 越大越稳定
  ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
  // 初始化ADC
  ADC_InitTypeDef ADC_InitStructue;
  // 工作模式
  // ADC_Mode_Independent 独立模式
  // 其他 双ADC模式
  ADC_InitStructue.ADC_Mode = ADC_Mode_Independent;
  // 数据对齐
  // ADC_DataAlign_Right 右对齐(左边填充0)
  // ADC_DataAlign_Left 左对齐(右边填充0)
  ADC_InitStructue.ADC_DataAlign = ADC_DataAlign_Right;
  // 扫描模式
  // ENABLE 扫描模式(多通道)
  // DISABLE 非扫描模式(单通道)
  ADC_InitStructue.ADC_ScanConvMode = DISABLE;
  // 转换模式
  // ENABLE 连续模式
  // DISABLE 单次模式
  // ADC_InitStructue.ADC_ContinuousConvMode = DISABLE;
  // 切换为连续模式
  ADC_InitStructue.ADC_ContinuousConvMode = ENABLE;
  // 通道数量 1~16
  ADC_InitStructue.ADC_NbrOfChannel = 1;
  // 外部触发源
  // ADC_ExternalTrigConv_None 不需要(使用软件触发)
  ADC_InitStructue.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_Init(ADC1, &ADC_InitStructue);
  // 开启ADC
  ADC_Cmd(ADC1, ENABLE);
  // 校准ADC
  ADC_ResetCalibration(ADC1);
  while (ADC_GetResetCalibrationStatus(ADC1) == SET)
    ;
  ADC_StartCalibration(ADC1);
  while (ADC_GetCalibrationStatus(ADC1) == SET)
    ;
  // 初始化PA0
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  // 要使用模拟输入
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  // 切换为连续模式
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

/**
 * @brief  获取模数转换ADC1在PA0口(ADC1通道1)的值
 * @retval 值 0~4095
 */
uint16_t AD_Init_ADC1_PA0_GetValue(void)
{
  // 单次转换
  // 开始转换
  // ADC_SoftwareStartConvCmd(ADC1,ENABLE);
  // 获取转换状态 等待转换完成
  // 采样周期55.5 采样周期12.5 共68周期
  // ADCCLK为72MHz的6分频 即12MHz 每次转换约为5.6us
  // ADC_FLAG 转换标志位
  // ADC_FLAG_AWD 模拟看门狗标志位
  // ADC_FLAG_EOC 规则组转换完成标志位
  // ADC_FLAG_JEOC 注入组转换完成标志位
  // ADC_FLAG_JSTRT 注入组开始转换标志位
  // ADC_FLAG_STRT 规则组开始转换标志位
  // while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET)
  //   ;
  // 获取转换值
  // 读取值会自动清除EOC标志位 不需要手动清除
  return ADC_GetConversionValue(ADC1);
}
