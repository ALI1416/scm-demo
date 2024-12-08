#include "stm32f10x.h"
#include "OLED.h"
#include "Delay.h"

void AD_DMA_Init(void);
void AD_GetValue(void);
void AD_DMA_Cycle_Init(void);

uint16_t AD_Value[4];

/**
 * AD多通道使用DMA
 * 接PA0 PA1 PA2 PA3口
 */
int main()
{
  OLED_Init(RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_11, GPIOB, GPIO_Pin_10);
  // AD_DMA_Init();
  AD_DMA_Cycle_Init();
  while (1)
  {
    // AD_GetValue();
    OLED_ShowFixedNumber(0, 0, AD_Value[0], 5);
    OLED_ShowFixedNumber(1, 0, AD_Value[1], 5);
    OLED_ShowFixedNumber(2, 0, AD_Value[2], 5);
    OLED_ShowFixedNumber(3, 0, AD_Value[3], 5);
    Delay_ms(100);
  }
}

/**
 * @brief  初始化模数转换ADC1和直接内存访问DMA1
 */
void AD_DMA_Init(void)
{
  // 初始化ADC1
  RCC_ADCCLKConfig(RCC_PCLK2_Div6);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  // 配置规则组4个通道
  ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_55Cycles5);
  ADC_InitTypeDef ADC_InitStructue;
  ADC_InitStructue.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructue.ADC_DataAlign = ADC_DataAlign_Right;
  // 扫描模式(多通道)
  ADC_InitStructue.ADC_ScanConvMode = ENABLE;
  // 单次模式
  ADC_InitStructue.ADC_ContinuousConvMode = DISABLE;
  // 4个通道
  ADC_InitStructue.ADC_NbrOfChannel = 4;
  // 软件触发
  ADC_InitStructue.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_Init(ADC1, &ADC_InitStructue);
  // 开启ADC到DMA通道
  ADC_DMACmd(ADC1, ENABLE);
  ADC_Cmd(ADC1, ENABLE);
  ADC_ResetCalibration(ADC1);
  while (ADC_GetResetCalibrationStatus(ADC1) == SET)
    ;
  ADC_StartCalibration(ADC1);
  while (ADC_GetCalibrationStatus(ADC1) == SET)
    ;
  // 初始化DMA1
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
  DMA_InitTypeDef DMA_InitStructure;
  // ADC1的DR寄存器
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
  // DR寄存器16位
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  // ADC1只有1个DR寄存器，不用自增
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  // 目的地
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)AD_Value;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  // 4个通道
  DMA_InitStructure.DMA_BufferSize = 4;
  // 单次转运
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  // 非软件触发(硬件外设触发)
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
  // 使用DMA1通道1(ADC1使用DMA1通道1)
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);
  // 启动DMA
  DMA_Cmd(DMA1_Channel1, ENABLE);
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
 */
void AD_GetValue(void)
{
  DMA_Cmd(DMA1_Channel1, DISABLE);
  DMA_SetCurrDataCounter(DMA1_Channel1, 4);
  DMA_Cmd(DMA1_Channel1, ENABLE);
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
  while (DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET)
    ;
  DMA_ClearFlag(DMA1_FLAG_TC1);
}

/**
 * @brief  初始化模数转换ADC1和直接内存访问DMA1[连续模式]
 */
void AD_DMA_Cycle_Init(void)
{
  // 初始化ADC1
  RCC_ADCCLKConfig(RCC_PCLK2_Div6);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_55Cycles5);
  ADC_InitTypeDef ADC_InitStructue;
  ADC_InitStructue.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructue.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructue.ADC_ScanConvMode = ENABLE;
  // 连续模式
  ADC_InitStructue.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructue.ADC_NbrOfChannel = 4;
  ADC_InitStructue.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_Init(ADC1, &ADC_InitStructue);
  ADC_DMACmd(ADC1, ENABLE);
  ADC_Cmd(ADC1, ENABLE);
  ADC_ResetCalibration(ADC1);
  while (ADC_GetResetCalibrationStatus(ADC1) == SET)
    ;
  ADC_StartCalibration(ADC1);
  while (ADC_GetCalibrationStatus(ADC1) == SET)
    ;
  // 初始化DMA1
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
  DMA_InitTypeDef DMA_InitStructure;
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)AD_Value;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = 4;
  // 连续转运
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);
  DMA_Cmd(DMA1_Channel1, ENABLE);
  // 初始化PA0 PA1 PA2 PA3
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  // 只手动触发一次即可连续转换
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}
