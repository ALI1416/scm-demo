#include "stm32f10x.h"

/**
 * LED长脚(小头)正极、短脚(大头)负极 使用低电平点亮方式
 * 接线：长脚正极、短脚A0
 */
int main()
{
  // 1.使用RCC开启GPIO时钟外设
  // 在stm32f10x_rcc文件里，最经常使用的是
  // RCC_AHBPeriphClockCmd、RCC_APB2PeriphClockCmd、RCC_APB1PeriphClockCmd
  // 由于点亮的是PA0口，他属于GPIOA外设，搜索，位于RCC_APB2PeriphClockCmd里
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  // 2.使用GPIO_Init初始化GPIO
  // 位于stm32f10x_gpio文件里，最经常使用的是(1个初始化4读4写)
  // GPIO_Init、GPIO_ReadInputDataBit、GPIO_ReadInputData、
  // GPIO_ReadOutputDataBit、GPIO_ReadOutputData
  // GPIO_SetBits、GPIO_ResetBits、GPIO_WriteBit、GPIO_Write
  // 定义结构体
  GPIO_InitTypeDef GPIO_InitStructure;
  // 输出模式 GPIOMode_TypeDef 推挽输出
  // 8种工作模式
  // GPIO_Mode_AIN analog in 模拟输入
  // GPIO_Mode_IN_FLOATING in floating 浮空输入
  // GPIO_Mode_IPD in pull down 下拉输入
  // GPIO_Mode_IPU in pull up 上拉输入
  // GPIO_Mode_Out_OD out open drain 开漏输出
  // GPIO_Mode_Out_PP out push pull 推挽输出
  // GPIO_Mode_AF_OD atl open drain 复用开漏
  // GPIO_Mode_AF_PP atl push pull 复用推挽
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  // 引脚 GPIO_pins_define 0号
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  // 速度 GPIOSpeed_TypeDef 50MHz
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  // 初始化
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  // 3.控制GPIO口
  // 设置0口为低电平 PA0亮
  // GPIO_ResetBits(GPIOA, GPIO_Pin_0);
  // 设置0口为高电平 PA0灭
  // GPIO_SetBits(GPIOA, GPIO_Pin_0);
  // 函数指定高低电平 Bit_RESET 低电平 Bit_SET 高电平
  GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);
  // GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);
  while (1)
  {
  }
}
