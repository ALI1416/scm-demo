#ifndef __OLED_PRO_H
#define __OLED_PRO_H

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
 * @brief  更新
 */
void OLED_Update(void);
/**
 * @brief  更新指定区域
 * @param  X X坐标(0~127)
 * @param  Y Y坐标(0~63)
 * @param  Width 宽(0~128)
 * @param  Height 高(0~64)
 */
void OLED_UpdateArea(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height);
/**
 * @brief  清屏
 */
void OLED_Clear(void);
/**
 * @brief  清屏指定区域
 * @param  X X坐标(0~127)
 * @param  Y Y坐标(0~63)
 * @param  Width 宽(0~128)
 * @param  Height 高(0~64)
 */
void OLED_ClearArea(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height);
/**
 * 反转
 */
void OLED_Reverse(void);
/**
 * @brief  反转指定区域
 * @param  X X坐标(0~127)
 * @param  Y Y坐标(0~63)
 * @param  Width 宽(0~128)
 * @param  Height 高(0~64)
 */
void OLED_ReverseArea(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height);
/**
 * @brief  显示图像
 * @param  X X坐标(0~127)
 * @param  Y Y坐标(0~63)
 * @param  Width 宽(0~128)
 * @param  Height 高(0~64)
 * @param  Image 图像
 */
void OLED_ShowImage(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height, const uint8_t *Image);
/**
 * @brief  显示字符
 * @param  X X坐标(0~127)
 * @param  Y Y坐标(0~63)
 * @param  Char 字符
 */
void OLED_ShowChar(uint8_t X, uint8_t Y, char Char);
/**
 * @brief  显示字符串
 * @param  X X坐标(0~127)
 * @param  Y Y坐标(0~63)
 * @param  String 字符串
 */
void OLED_ShowString(uint8_t X, uint8_t Y, char *String);
/**
 * @brief  显示数字
 * @param  X X坐标(0~127)
 * @param  Y Y坐标(0~63)
 * @param  Number 数字(0~4294967295)
 */
void OLED_ShowNumber(uint8_t X, uint8_t Y, uint32_t Number);
/**
 * @brief  显示有符号数字(始终显示+-符号)
 * @param  X X坐标(0~127)
 * @param  Y Y坐标(0~63)
 * @param  Number 有符号数字(-2147483648~2147483647)
 */
void OLED_ShowSignedNumber(uint8_t X, uint8_t Y, int32_t Number);
/**
 * @brief  显示十六进制数字(固定8位长度)
 * @param  X X坐标(0~127)
 * @param  Y Y坐标(0~63)
 * @param  Number 数字(0x0000 0000~0xFFFF FFFF)
 */
void OLED_ShowHexNumber(uint8_t X, uint8_t Y, uint32_t Number);
/**
 * @brief  显示二六进制数字(固定16位长度)
 * @param  X X坐标(0~127)
 * @param  Y Y坐标(0~63)
 * @param  Number 数字(0b0000 0000 0000 0000~0b1111 1111 1111 1111)
 */
void OLED_ShowBinNumber(uint8_t X, uint8_t Y, uint16_t Number);

#endif
