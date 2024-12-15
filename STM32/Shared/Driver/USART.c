#include "stm32f10x.h"

/**
 * @brief  初始化USART1发送
 */
void USART1_Tx_Init(void)
{
  // 在stm32f10x_usart文件里
  // USART_DeInit 恢复默认配置
  // USART_Init 初始化USART
  // USART_StructInit 给USART结构体默认值
  // USART_ClockInit 、 USART_ClockStructInit 时钟同步输出
  // USART_Cmd 使能计数器
  // USART_ITConfig 使能中断输出信号
  // USART_DMACmd 开启USART到DMA的通道
  // USART_SendData 发送数据
  // USART_ReceiveData 接收数据
  // USART_GetFlagStatus 和 USART_GetITStatus (中断函数内部使用) 获取标志位是否被置SET
  // USART_ClearFlag 和 USART_ClearITPendingBit (中断函数内部使用) 对置SET的标志位进行清除
  // 初始化USART1
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  USART_InitTypeDef USART_InitStructure;
  // 波特率
  USART_InitStructure.USART_BaudRate = 9600;
  // 数据长度
  // USART_WordLength_8b 8位
  // USART_WordLength_9b 9位
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  // 停止位
  // USART_StopBits_1 1位
  // USART_StopBits_0_5 0.5位
  // USART_StopBits_2 2位
  // USART_StopBits_1_5 1.5位
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  // 校验位
  // USART_Parity_No 无
  // USART_Parity_Even 偶校验
  // USART_Parity_Odd 奇校验
  USART_InitStructure.USART_Parity = USART_Parity_No;
  // 模式
  // USART_Mode_Rx 接收
  // USART_Mode_Tx 发送
  USART_InitStructure.USART_Mode = USART_Mode_Tx;
  // 流控
  // USART_HardwareFlowControl_None 不使用
  // USART_HardwareFlowControl_RTS 只用RTS
  // USART_HardwareFlowControl_CTS 只用CTS
  // USART_HardwareFlowControl_RTS_CTS RTS和CTS都用
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_Init(USART1, &USART_InitStructure);
  USART_Cmd(USART1, ENABLE);
  // 初始化PA9(发送)引脚
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  // 要使用复用推挽输出模式
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**
 * @brief  USART1发送byte
 * @param  Byte byte
 */
void USART1_SendByte(uint8_t Byte)
{
  USART_SendData(USART1, Byte);
  // 等待发送完成
  // USART_FLAG_TXE 发送数据寄存器空标志位
  while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
    ;
  // 不需要手动清除标志位，在 USART_SendData 时自动清除
}

/**
 * @brief  USART1发送byte数组
 * @param  Bytes byte数组
 * @param  Length 数组长度
 */
void USART1_SendBytes(uint8_t *Bytes, uint32_t Length)
{
  for (uint32_t i; i < Length; i++)
  {
    USART1_SendByte(Bytes[i]);
  }
}

/**
 * @brief  USART1发送字符串
 * @param  String 字符串
 */
void USART1_SendString(char *String)
{
  for (uint32_t i = 0; String[i] != '\0'; i++)
  {
    USART1_SendByte(String[i]);
  }
}

/**
 * @brief  初始化USART1
 */
void USART1_Init(void)
{
  // 初始化USART1
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  USART_InitTypeDef USART_InitStructure;
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  // 同时启用接收和发送
  USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_Init(USART1, &USART_InitStructure);
  USART_Cmd(USART1, ENABLE);
  // 初始化PA9(发送)和PA10(接收)引脚
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  // 要使用复用推挽输出模式
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  // 要使用上拉输入模式
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
}

/**
 * @brief  初始化USART1(启用中断)
 */
void USART1_IT_Init(void)
{
  // 初始化USART1
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  USART_InitTypeDef USART_InitStructure;
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_Init(USART1, &USART_InitStructure);
  // 开启中断 数据接收寄存器非空中断标志位
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
  // 配置NVIC分组
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  // 初始化NVIC的USART1通道
  NVIC_InitTypeDef NVIC_InitStructure;
  // 要使用 USART1_IRQn
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_Init(&NVIC_InitStructure);
  USART_Cmd(USART1, ENABLE);
  // 初始化PA9(发送)和PA10(接收)引脚
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
}

/**
 * 接收到的数据
 */
uint8_t Serial_RxData;
/**
 * 接收到数据标志位
 */
uint8_t Serial_RxFlag;

// 执行中断程序
// 在startup_stm32f10x_md文件中存在 USART1_IRQHandler 中断函数
// void USART1_IRQHandler(void)
// {
//   // 数据接收寄存器非空标志位
//   if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
//   {
//     Serial_RxData = USART_ReceiveData(USART1);
//     Serial_RxFlag = 1;
//   }
// }

/**
 * @brief  获取收到数据标志位(获取后自动清除)
 * @retval
 * 0 没有标记
 * 1 有标记
 */
uint8_t Serial_RxFlag_Get(void)
{
  if (Serial_RxFlag == 1)
  {
    Serial_RxFlag = 0;
    return 1;
  }
  return 0;
}

/**
 * @brief  获取收到数据
 * @retval 收到数据
 */
uint8_t Serial_RxData_Get(void)
{
  return Serial_RxData;
}
