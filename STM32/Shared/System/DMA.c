#include "stm32f10x.h"

uint16_t DMA_DMA_BufferSize;

/**
 * @brief  初始化直接内存访问(Direct Memory Access)DMA1
 * 内存到内存，软件触发(byte)
 * @param DMA_PeripheralBaseAddr 数据源头
 * @param DMA_MemoryBaseAddr 数据目的地
 * @param DMA_BufferSize 数据长度
 */
void DMA_Init_Software(uint32_t DMA_PeripheralBaseAddr, uint32_t DMA_MemoryBaseAddr, uint16_t DMA_BufferSize)
{
  DMA_DMA_BufferSize = DMA_BufferSize;
  // 开启RCC内部时钟
  // 在stm32f10x_dam文件里
  // DMA_DeInit 恢复默认配置
  // DMA_Init 初始化DMA
  // DMA_StructInit 给时DMA结构体默认值
  // DMA_Cmd 使能DMA
  // DMA_ITConfig DMA中断配置
  // DMA_SetCurrDataCounter 设置转运数据个数
  // DMA_GetCurrDataCounter 获取转运数据个数
  // DMA_GetFlagStatus 和 DMA_GetITStatus (中断函数内部使用) 获取标志位是否被置SET
  // DMA_ClearFlag 和 DMA_ClearITPendingBit (中断函数内部使用) 对置SET的标志位进行清除
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
  // 初始化DMA1
  DMA_InitTypeDef DMA_InitStructure;
  // 外设基地址
  DMA_InitStructure.DMA_PeripheralBaseAddr = DMA_PeripheralBaseAddr;
  // 外设数据宽度
  // DMA_PeripheralDataSize_Byte 1比特 8位
  // DMA_PeripheralDataSize_HalfWord 半字节 16位
  // DMA_PeripheralDataSize_Word 1字节 32位
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  // 是否自增
  // DMA_PeripheralInc_Enable 是
  // DMA_PeripheralInc_Disable 否
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
  DMA_InitStructure.DMA_MemoryBaseAddr = DMA_MemoryBaseAddr;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  // 转运方向
  // DMA_DIR_PeripheralDST 外设为目的地
  // DMA_DIR_PeripheralSRC 外设为源头
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  // 转运次数(每转运一次，数字-1)
  DMA_InitStructure.DMA_BufferSize = DMA_BufferSize;
  // 模式
  // DMA_Mode_Circular 循环
  // DMA_Mode_Normal 单次
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  // 内存到内存
  // DMA_M2M_Enable 启用
  // DMA_M2M_Disable 停用
  DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;
  // 优先级
  // DMA_Priority_VeryHigh 非常高
  // DMA_Priority_High 高
  // DMA_Priority_Medium 中等
  // DMA_Priority_Low 低
  DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
  // DMAy_Channelx 使用DMA1通道1
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);
}

/**
 * DMA软件转运
 */
void DMA_Software_Transfer(void)
{
  // 停用
  DMA_Cmd(DMA1_Channel1, DISABLE);
  // 必须先停用，再重新设置转运次数，才能再启用下一次转运
  DMA_SetCurrDataCounter(DMA1_Channel1, DMA_DMA_BufferSize);
  // 启动
  DMA_Cmd(DMA1_Channel1, ENABLE);
  // 等待转运完成
  // 获取标志位
  // DMA1_FLAG_GL1 全局
  // DMA1_FLAG_TC1 全部完成
  // DMA1_FLAG_HT1 完成一半
  // DMA1_FLAG_TE1 错误
  while (DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET)
    ;
  // 清除标志位
  DMA_ClearFlag(DMA1_FLAG_TC1);
}
