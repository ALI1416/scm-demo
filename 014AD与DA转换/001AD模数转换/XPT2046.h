#ifndef __XPT2046_H__
#define __XPT2046_H__

// 8位
#define XPT2046_XP_8 0x9C //0xBC
#define XPT2046_YP_8 0xDC
#define XPT2046_VBAT_8 0xAC
#define XPT2046_AUX_8 0xEC

// 12位
#define XPT2046_XP_12 0x94 //0x84
#define XPT2046_YP_12 0xD4
#define XPT2046_VBAT_12 0xA4
#define XPT2046_AUX_12 0xE4

unsigned int XPT2046_ReadAD(unsigned char Command);

#endif
