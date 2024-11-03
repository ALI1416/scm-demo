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
void OLED_SetCursor(uint8_t Page, uint8_t Col);
uint8_t OLED_GetNumberLength(uint32_t Number);
uint8_t OLED_GetNumberIndexNumber(uint32_t Number, uint8_t Index);
uint8_t OLED_GetHexNumberIndexNumber(uint32_t Number, uint8_t Index);
uint8_t OLED_GetBinNumberIndexNumber(uint16_t Number, uint8_t Index);

GPIO_TypeDef *OLED_GPIOx_SCL;
uint16_t OLED_GPIO_Pin_SCL;
GPIO_TypeDef *OLED_GPIOx_SDA;
uint16_t OLED_GPIO_Pin_SDA;

/**
 * OLED页长度
 */
#define OLED_PAGE_LENGTH 8
/**
 * OLED列长度
 */
#define OLED_COL_LENGTH 128

/**
 * OLED空行
 */
const uint8_t OLED_ROW_EMPTY[OLED_COL_LENGTH];

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
 * @brief  写字节
 * @param  Type 类型
 * @param  Data 字节
 * @param Length 字节长度
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
 * @param  Page 页(0~7)
 * @param  Col 列(0~127)
 */
void OLED_SetCursor(uint8_t Page, uint8_t Col)
{
  const uint8_t command[] = {
      // 页
      0xB0 | Page,
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
  for (uint8_t i = 0; i < OLED_PAGE_LENGTH; i++)
  {
    OLED_SetCursor(i, 0);
    OLED_WriteData(OLED_ROW_EMPTY, OLED_COL_LENGTH);
  }
}

/**
 * @brief  显示字符
 * @param  Row 行(0~3)
 * @param  Col 列(0~15)
 * @param  Char 字符
 */
void OLED_ShowChar(uint8_t Row, uint8_t Col, char Char)
{
  // 上半部分
  OLED_SetCursor(Row * 2, Col * 8);
  OLED_WriteData(OLED_FONT[Char][0], 8);
  // 下半部分
  OLED_SetCursor(Row * 2 + 1, Col * 8);
  OLED_WriteData(OLED_FONT[Char][1], 8);
}

/**
 * @brief  显示字符串
 * @param  Row 行(0~3)
 * @param  Col 列(0~15)
 * @param  String 字符串
 */
void OLED_ShowString(uint8_t Row, uint8_t Col, char *String)
{
  for (uint8_t i = 0; String[i] != '\0'; i++)
  {
    OLED_ShowChar(Row, Col + i, String[i]);
  }
}

/**
 * @brief  获取数字长度
 * @param  Number 数字(0~4294967295)
 * @retval 数字长度
 */
uint8_t OLED_GetNumberLength(uint32_t Number)
{
  if (Number < 10)
  {
    return 1;
  }
  else if (Number < 100)
  {
    return 2;
  }
  else if (Number < 1000)
  {
    return 3;
  }
  else if (Number < 10000)
  {
    return 4;
  }
  else if (Number < 100000)
  {
    return 5;
  }
  else if (Number < 1000000)
  {
    return 6;
  }
  else if (Number < 10000000)
  {
    return 7;
  }
  else if (Number < 100000000)
  {
    return 8;
  }
  else if (Number < 1000000000)
  {
    return 9;
  }
  else
  {
    return 10;
  }
}

/**
 * @brief  获取数字索引位置的数字
 * @param  Number 数字(0~4294967295)
 * @param  Index 索引位置(0~9)(低位在前)
 * @retval 索引位置的数字
 */
uint8_t OLED_GetNumberIndexNumber(uint32_t Number, uint8_t Index)
{
  if (Index == 0)
  {
    return Number % 10;
  }
  else if (Index == 1)
  {
    return Number / 10 % 10;
  }
  else if (Index == 2)
  {
    return Number / 100 % 10;
  }
  else if (Index == 3)
  {
    return Number / 1000 % 10;
  }
  else if (Index == 4)
  {
    return Number / 10000 % 10;
  }
  else if (Index == 5)
  {
    return Number / 100000 % 10;
  }
  else if (Index == 6)
  {
    return Number / 1000000 % 10;
  }
  else if (Index == 7)
  {
    return Number / 10000000 % 10;
  }
  else if (Index == 8)
  {
    return Number / 100000000 % 10;
  }
  else
  {
    return Number / 1000000000 % 10;
  }
}

/**
 * @brief  显示数字
 * @param  Row 行(0~3)
 * @param  Col 列(0~15)
 * @param  Number 数字(0~4294967295)
 */
void OLED_ShowNumber(uint8_t Row, uint8_t Col, uint32_t Number)
{
  uint8_t length = OLED_GetNumberLength(Number);
  for (uint8_t i = 0; i < length; i++)
  {
    OLED_ShowChar(Row, Col + i, OLED_GetNumberIndexNumber(Number, length - 1 - i) + '0');
  }
}

/**
 * @brief  显示固定长度数字(长度过大前面补0、长度过小头部截断)
 * @param  Row 行(0~3)
 * @param  Col 列(0~15)
 * @param  Number 数字(0~4294967295)
 * @param  Length 长度(1-16)
 */
void OLED_ShowFixedNumber(uint8_t Row, uint8_t Col, uint32_t Number, uint8_t Length)
{
  if (Length == 0)
  {
    return;
  }
  uint8_t length = OLED_GetNumberLength(Number);
  uint8_t i = 0;
  for (; i < Length - length; i++)
  {
    OLED_ShowChar(Row, Col + i, '0');
  }
  for (; i < Length; i++)
  {
    OLED_ShowChar(Row, Col + i, OLED_GetNumberIndexNumber(Number, Length - 1 - i) + '0');
  }
}

/**
 * @brief  显示有符号数字(始终显示+-号、数字0显示+号)
 * @param  Row 行(0~3)
 * @param  Col 列(0~15)
 * @param  Number 有符号数字(-2147483648~2147483647)
 */
void OLED_ShowSignedNumber(uint8_t Row, uint8_t Col, int32_t Number)
{
  uint32_t temp;
  if (Number < 0)
  {
    temp = -Number;
    OLED_ShowChar(Row, Col, '-');
  }
  else
  {
    temp = Number;
    OLED_ShowChar(Row, Col, '+');
  }
  OLED_ShowNumber(Row, Col + 1, temp);
}

/**
 * @brief  显示固定长度有符号数字(始终显示+-号、数字0显示+号、长度含符号、长度过大前面补0、长度过小头部截断、长度为1只显示+-号)
 * @param  Row 行(0~3)
 * @param  Col 列(0~15)
 * @param  Number 有符号数字(-2147483648~2147483647)
 * @param  Length 长度(1-16)
 */
void OLED_ShowFixedSignedNumber(uint8_t Row, uint8_t Col, int32_t Number, uint8_t Length)
{
  uint32_t temp;
  if (Number < 0)
  {
    temp = -Number;
    OLED_ShowChar(Row, Col, '-');
  }
  else
  {
    temp = Number;
    OLED_ShowChar(Row, Col, '+');
  }
  OLED_ShowFixedNumber(Row, Col + 1, temp, Length - 1);
}

/**
 * @brief  获取十六进制数字索引位置的数字
 * @param  Number 数字(0x0000 0000~0xFFFF FFFF)
 * @param  Index 索引位置(0~7)(低位在前)
 * @retval 索引位置的数字
 */
uint8_t OLED_GetHexNumberIndexNumber(uint32_t Number, uint8_t Index)
{
  if (Index == 0)
  {
    return Number % 16;
  }
  else if (Index == 1)
  {
    return Number / 0x10 % 16;
  }
  else if (Index == 2)
  {
    return Number / 0x100 % 16;
  }
  else if (Index == 3)
  {
    return Number / 0x1000 % 16;
  }
  else if (Index == 4)
  {
    return Number / 0x10000 % 16;
  }
  else if (Index == 5)
  {
    return Number / 0x100000 % 16;
  }
  else if (Index == 6)
  {
    return Number / 0x1000000 % 16;
  }
  else
  {
    return Number / 0x10000000 % 16;
  }
}

/**
 * @brief  显示十六进制数字(固定8位长度)
 * @param  Row 行(0~3)
 * @param  Col 列(0~15)
 * @param  Number 数字(0x0000 0000~0xFFFF FFFF)
 */
void OLED_ShowHexNumber(uint8_t Row, uint8_t Col, uint32_t Number)
{
  uint8_t hexNumber;
  uint8_t hexChar;
  for (uint8_t i = 0; i < 8; i++)
  {
    hexNumber = OLED_GetHexNumberIndexNumber(Number, 7 - i);
    if (hexNumber < 10)
    {
      hexChar = hexNumber + '0';
    }
    else
    {
      hexChar = hexNumber - 10 + 'A';
    }
    OLED_ShowChar(Row, Col + i, hexChar);
  }
}

/**
 * @brief  获取二进制数字索引位置的数字
 * @param  Number 数字(0b0000 0000 0000 0000~0b1111 1111 1111 1111)
 * @param  Index 索引位置(0~15)(低位在前)
 * @retval 索引位置的数字
 */
uint8_t OLED_GetBinNumberIndexNumber(uint16_t Number, uint8_t Index)
{
  if (Index == 0)
  {
    return Number % 2;
  }
  else if (Index == 1)
  {
    return Number / 2 % 2;
  }
  else if (Index == 2)
  {
    return Number / 4 % 2;
  }
  else if (Index == 3)
  {
    return Number / 8 % 2;
  }
  else if (Index == 4)
  {
    return Number / 16 % 2;
  }
  else if (Index == 5)
  {
    return Number / 32 % 2;
  }
  else if (Index == 6)
  {
    return Number / 64 % 2;
  }
  else if (Index == 7)
  {
    return Number / 128 % 2;
  }
  else if (Index == 8)
  {
    return Number / 256 % 2;
  }
  else if (Index == 9)
  {
    return Number / 512 % 2;
  }
  else if (Index == 10)
  {
    return Number / 1024 % 2;
  }
  else if (Index == 11)
  {
    return Number / 2048 % 2;
  }
  else if (Index == 12)
  {
    return Number / 4096 % 2;
  }
  else if (Index == 13)
  {
    return Number / 8192 % 2;
  }
  else if (Index == 14)
  {
    return Number / 16384 % 2;
  }
  else
  {
    return Number / 32768 % 2;
  }
}

/**
 * @brief  显示二六进制数字(固定16位长度)
 * @param  Row 行(0~3)
 * @param  Col 列(0~15)
 * @param  Number 数字(0b0000 0000 0000 0000~0b1111 1111 1111 1111)
 */
void OLED_ShowBinNumber(uint8_t Row, uint8_t Col, uint16_t Number)
{
  for (uint8_t i = 0; i < 16; i++)
  {
    OLED_ShowChar(Row, Col + i, OLED_GetBinNumberIndexNumber(Number, 15 - i) + '0');
  }
}
