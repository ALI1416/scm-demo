#ifndef __OLED_H
#define __OLED_H

#include "stm32f10x.h"

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
/**
 * @brief  显示字符
 * @param  Row 行(0~3)
 * @param  Col 列(0~15)
 * @param  Char 字符
 */
void OLED_ShowChar(uint8_t Row, uint8_t Col, char Char);
/**
 * @brief  显示字符串
 * @param  Row 行(0~3)
 * @param  Col 列(0~15)
 * @param  String 字符串
 */
void OLED_ShowString(uint8_t Row, uint8_t Col, char *String);
/**
 * @brief  显示数字
 * @param  Row 行(0~3)
 * @param  Col 列(0~15)
 * @param  Number 数字(0~4294967295)
 */
void OLED_ShowNumber(uint8_t Row, uint8_t Col, uint32_t Number);
/**
 * @brief  显示有符号数字
 * @param  Row 行(0~3)
 * @param  Col 列(0~15)
 * @param  Number 有符号数字(-2147483648~2147483647)
 */
void OLED_ShowSignedNumber(uint8_t Row, uint8_t Col, int32_t Number);
/**
 * @brief  显示十六进制数字(固定8位长度)
 * @param  Row 行(0~3)
 * @param  Col 列(0~15)
 * @param  Number 数字(0x0000 0000~0xFFFF FFFF)
 */
void OLED_ShowHexNumber(uint8_t Row, uint8_t Col, uint32_t Number);
/**
 * @brief  显示二六进制数字(固定16位长度)
 * @param  Row 行(0~3)
 * @param  Col 列(0~15)
 * @param  Number 数字(0b0000 0000 0000 0000~0b1111 1111 1111 1111)
 */
void OLED_ShowBinNumber(uint8_t Row, uint8_t Col, uint16_t Number);

#endif
