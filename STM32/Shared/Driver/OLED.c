#include "stm32f10x.h"
#include "OLED.h"
#include "OLED.Data.h"

void OLED_I2C_SCL(uint8_t BitVal);
void OLED_I2C_SDA(uint8_t BitVal);
void OLED_I2C_Start(void);
void OLED_I2C_Stop(void);
void OLED_I2C_SendByte(uint8_t Byte);
void OLED_WriteCommand(const uint8_t *Command, uint8_t Length);
void OLED_WriteData(const uint8_t *Data, uint8_t Length);
void OLED_WriteByte(uint8_t Type, const uint8_t *Byte, uint8_t Length);

GPIO_TypeDef *OLED_GPIOx_SCL;
uint16_t OLED_GPIO_Pin_SCL;
GPIO_TypeDef *OLED_GPIOx_SDA;
uint16_t OLED_GPIO_Pin_SDA;

/**
 * @brief  初始化OLED(I2C协议)
 * @param RCC_APB2Periph 外设组
 * @param GPIOx_SCL SCL外设名
 * @param GPIO_Pin_SCL SCL外设针脚
 * @param GPIOx_SDA SDA外设名
 * @param GPIO_Pin_SDA SDA外设针脚
 */
void OLED_Init(uint32_t RCC_APB2Periph,
               GPIO_TypeDef *GPIOx_SCL, uint16_t GPIO_Pin_SCL,
               GPIO_TypeDef *GPIOx_SDA, uint16_t GPIO_Pin_SDA)
{
  OLED_GPIOx_SCL = GPIOx_SCL;
  OLED_GPIO_Pin_SCL = GPIO_Pin_SCL;
  OLED_GPIOx_SDA = GPIOx_SDA;
  OLED_GPIO_Pin_SDA = GPIO_Pin_SDA;
  // 延时 等待OLED供电稳定
  for (uint16_t i = 0; i < 65535; i++)
    ;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_SCL;
  GPIO_Init(GPIOx_SCL, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_SDA;
  GPIO_Init(GPIOx_SDA, &GPIO_InitStructure);
  OLED_I2C_SCL(1);
  OLED_I2C_SDA(1);
  OLED_WriteCommand(OLED_INIT_COMMAND, OLED_INIT_COMMAND_LENGTH);
  OLED_Clear();
}

/**
 * @brief  I2C写SCL
 * @param BitVal
 * 0 Bit_RESET
 * 1 Bit_SET
 */
void OLED_I2C_SCL(uint8_t BitVal)
{
  GPIO_WriteBit(OLED_GPIOx_SCL, OLED_GPIO_Pin_SCL, (BitAction)BitVal);
}

/**
 * @brief  I2C写SDA
 * @param BitVal
 * 0 Bit_RESET
 * 1 Bit_SET
 */
void OLED_I2C_SDA(uint8_t BitVal)
{
  GPIO_WriteBit(OLED_GPIOx_SDA, OLED_GPIO_Pin_SDA, (BitAction)BitVal);
}

/**
 * @brief  I2C开始
 */
void OLED_I2C_Start(void)
{
  OLED_I2C_SDA(1);
  OLED_I2C_SCL(1);
  OLED_I2C_SDA(0);
  OLED_I2C_SCL(0);
}

/**
 * @brief  I2C停止
 */
void OLED_I2C_Stop(void)
{
  OLED_I2C_SDA(0);
  OLED_I2C_SCL(1);
  OLED_I2C_SDA(1);
}

/**
 * @brief  I2C发送一个字节
 * @param  Byte 字节
 */
void OLED_I2C_SendByte(uint8_t Byte)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    OLED_I2C_SDA(Byte & (0x80 >> i));
    OLED_I2C_SCL(1);
    OLED_I2C_SCL(0);
  }
  // 额外的一个时钟，不处理应答信号
  OLED_I2C_SCL(1);
  OLED_I2C_SCL(0);
}

/**
 * @brief  写命令
 * @param  Command 命令
 * @param Length 命令长度
 */
void OLED_WriteCommand(const uint8_t *Command, uint8_t Length)
{
  OLED_WriteByte(0x00, Command, Length);
}

/**
 * @brief  写数据
 * @param  Data 数据
 * @param Length 数据长度
 */
void OLED_WriteData(const uint8_t *Data, uint8_t Length)
{
  OLED_WriteByte(0x40, Data, Length);
}

/**
 * @brief  写比特
 * @param  Type 类型
 * @param  Data 比特
 * @param Length 比特长度
 */
void OLED_WriteByte(uint8_t Type, const uint8_t *Byte, uint8_t Length)
{
  OLED_I2C_Start();
  // 从机地址
  OLED_I2C_SendByte(0x78);
  OLED_I2C_SendByte(Type);
  for (uint8_t i = 0; i < Length; i++)
  {
    OLED_I2C_SendByte(Byte[i]);
  }
  OLED_I2C_Stop();
}

/**
 * @brief  设置光标坐标
 * @param  Row 行(0~7)
 * @param  Col 列(0~127)
 */
void OLED_SetCursor(uint8_t Row, uint8_t Col)
{
  const uint8_t command[] = {
      // 行
      0xB0 | Row,
      // 列的高4位
      0x10 | ((Col & 0xF0) >> 4),
      // 列的低4位
      0x00 | (Col & 0x0F)};
  // OLED_WriteCommand(command, sizeof(command) / sizeof(uint8_t));
  OLED_WriteCommand(command, 3);
}

/**
 * @brief  清屏
 */
void OLED_Clear(void)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    OLED_SetCursor(i, 0);
    OLED_WriteData(OLED_ROW_EMPTY, OLED_ROW_EMPTY_LENGTH);
  }
}
