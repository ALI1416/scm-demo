#ifndef __OLED_H
#define __OLED_H

#include "stm32f10x.h"
#include "OLED.Data.h"

/**
 * @brief  初始化OLED(I2C协议)
 * @param RCC_APB2Periph 外设组
 * @param GPIOx_SCL SCL外设名
 * @param GPIO_Pin_SCL SCL外设针脚
 * @param GPIOx_SDA SDA外设名
 * @param GPIO_Pin_SDA SDA外设针脚
 */
void OLED_Init(uint32_t RCC_APB2Periph,
               GPIO_TypeDef *GPIOx_SCL, uint16_t GPIO_Pin_SCL,
               GPIO_TypeDef *GPIOx_SDA, uint16_t GPIO_Pin_SDA);
/**
 * @brief  设置光标坐标
 * @param  Row 行(0~7)
 * @param  Col 列(0~127)
 */
void OLED_SetCursor(uint8_t Row, uint8_t Col);
/**
 * @brief  清屏
 */
void OLED_Clear(void);

#endif
