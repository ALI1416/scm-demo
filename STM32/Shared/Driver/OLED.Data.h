#ifndef __OLED_DATA_H
#define __OLED_DATA_H

#include "stm32f10x.h"

#define OLED_INIT_COMMAND_LENGTH 23
#define OLED_ROW_EMPTY_LENGTH 128

/**
 * OLED初始化命令
 */
extern const uint8_t OLED_INIT_COMMAND[];

/**
 * 行空
 */
extern const uint8_t OLED_ROW_EMPTY[];

#endif
