#ifndef __DELAY_H
#define __DELAY_H

/**
 * @brief  延时n*1us
 * @param  n 延时1us的倍数，范围：0~65535
 */
void delayUs(uint32_t n);
/**
 * @brief  延时n*1ms
 * @param  n 延时1ms的倍数，范围：0~65535
 */
void delayMs(uint32_t n);
/**
 * @brief  延时n*1s
 * @param  n 延时1s的倍数，范围：0~65535
 */
void delayS(uint32_t n);

#endif
