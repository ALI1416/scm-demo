#ifndef __USART_H
#define __USART_H

/**
 * @brief  初始化USART1发送
 */
void USART1_Tx_Init(void);
/**
 * @brief  USART1发送byte
 * @param  Byte byte
 */
void USART1_SendByte(uint8_t Byte);
/**
 * @brief  USART1发送byte数组
 * @param  Bytes byte数组
 * @param  Length 数组长度
 */
void USART1_SendBytes(uint8_t *Bytes, uint32_t Length);
/**
 * @brief  USART1发送字符串
 * @param  String 字符串
 */
void USART1_SendString(char *String);
/**
 * @brief  初始化USART1
 */
void USART1_Init(void);
/**
 * @brief  获取收到数据标志位(获取后自动清除)
 * @retval
 * 0 没有标记
 * 1 有标记
 */
uint8_t Serial_RxFlag_Get(void);
/**
 * @brief  获取收到数据
 * @retval 收到数据
 */
uint8_t Serial_RxData_Get(void);


#endif
