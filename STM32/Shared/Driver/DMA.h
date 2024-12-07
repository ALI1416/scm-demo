#ifndef __DMA_H
#define __DMA_H

/**
 * @brief  初始化直接内存访问(Direct Memory Access)DMA1
 * 内存到内存，软件触发(byte)
 * @param DMA_PeripheralBaseAddr 数据源头
 * @param DMA_MemoryBaseAddr 数据目的地
 * @param DMA_BufferSize 数据长度
 */
void DMA_Init_Software(uint32_t DMA_PeripheralBaseAddr, uint32_t DMA_MemoryBaseAddr, uint32_t DMA_BufferSize);

/**
 * DMA软件转运
 */
void DMA_Software_Transfer(void);

#endif
