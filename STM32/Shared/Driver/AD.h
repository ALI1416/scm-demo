#ifndef __AD_H
#define __AD_H

/**
 * @brief  初始化模数转换ADC1在PA0口(ADC1通道1)
 */
void AD_Init_ADC1_PA0(void);
/**
 * @brief  获取模数转换ADC1在PA0口(ADC1通道1)的值
 * @retval 值
 */
uint16_t AD_ADC1_PA0_GetValue(void);
/**
 * @brief  初始化模数转换ADC1在PA0口(ADC1通道1)[连续模式]
 */
void AD_Init_Cycle_ADC1_PA0(void);
/**
 * @brief  获取模数转换ADC1在PA0口(ADC1通道1)的值[连续模式]
 * @retval 值
 */
uint16_t AD_Cycle_ADC1_PA0_GetValue(void);

#endif
