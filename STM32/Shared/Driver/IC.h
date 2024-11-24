#ifndef __IC_H
#define __IC_H

/**
 * @brief 初始化输入捕获(测量周期法，最大测量频率1MHz)在PA6口(定时器3通道1)
 */
void IC_Init_PA6(void);

/**
 * @brief 初始化输入捕获PWMI模式(测量周期法，最大测量频率1MHz，最大分辨率1%)在PA6口(定时器3通道1和通道2)
 */
void IC_PWMI_Init_PA6(void);

#endif
