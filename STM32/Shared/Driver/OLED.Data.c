#include "stm32f10x.h"
#include "OLED.Data.h"

/**
 * OLED初始化命令
 */
const uint8_t OLED_INIT_COMMAND[] = {
    // 关闭显示
    0xAE,
    // 设置显示时钟分频比/振荡器频率
    0xD5,
    0x80,
    // 设置多路复用率
    0xA8,
    0x3F,
    // 设置显示偏移
    0xD3,
    0x00,
    // 设置显示开始行
    0x40,
    // 设置左右方向 0xA1正常 0xA0左右反置
    0xA1,
    // 设置上下方向 0xC8正常 0xC0上下反置
    0xC8,
    // 设置COM引脚硬件配置
    0xDA,
    0x12,
    // 设置对比度控制
    0x81,
    0xCF,
    // 设置预充电周期
    0xD9,
    0xF1,
    // 设置VCOMH取消选择级别
    0xDB,
    0x30,
    // 设置整个显示打开/关闭
    0xA4,
    // 设置正常/倒转显示
    0xA6,
    // 设置充电泵
    0x8D,
    0x14,
    // 开启显示
    0xAF};

/**
 * 行空
 */
const uint8_t OLED_ROW_EMPTY[128];
