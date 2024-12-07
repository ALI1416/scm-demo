#ifndef __DELAY_H
#define __DELAY_H

/**
 * @brief  延时n*1us
 * @param  n 延时1us的倍数，范围：0~233015
 */
void Delay_us(uint32_t n);
/**
 * @brief  延时n*1ms
 * @param  n 延时1ms的倍数，范围：0~4294967295
 */
void Delay_ms(uint32_t n);
/**
 * @brief  延时n*1s
 * @param  n 延时1ms的倍数，范围：0~4294967295
 */
void Delay_s(uint32_t n);

#endif
