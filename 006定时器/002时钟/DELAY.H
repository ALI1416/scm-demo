// 如果不存在__EDLAY_H__这个名字，才执行他和#endif之间的语句
#ifndef __EDLAY_H__
// 定义__EDLAY_H__这个名字，防止重复编译
#define __DELAY_H__

// 声明函数定义
void delayMs(unsigned int n);

#endif
