#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "OLED.Font.h"

GPIO_TypeDef *OLED_GPIO_SCL;
uint16_t OLED_GPIO_Pin_SCL;
GPIO_TypeDef *OLED_GPIOx_SDA;
uint16_t OLED_GPIO_Pin_SDA;

void OLED_SCL(uint8_t BitVal);
void OLED_SDA(uint8_t BitVal);
void OLED_I2C_Start(void);
void OLED_I2C_Stop(void);
void OLED_I2C_SendByte(uint8_t Byte);
void OLED_WriteCommand(uint8_t *Command);
void OLED_WriteData(uint8_t *Data);
void OLED_WriteByteArray(uint8_t Control, uint8_t *ByteArray);

/**
 * OLED初始化命令
 */
uint8_t OLED_Init_Command[] = {
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
uint8_t OLED_ROW_EMPTY[128];

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
  OLED_GPIO_SCL = GPIOx_SCL;
  OLED_GPIO_Pin_SCL = GPIO_Pin_SCL;
  OLED_GPIOx_SDA = GPIOx_SDA;
  OLED_GPIO_Pin_SDA = GPIO_Pin_SDA;
  // 延时1秒 等待OLED供电稳定
  Delay_s(1);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_SCL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOx_SCL, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_SDA;
  GPIO_Init(GPIOx_SDA, &GPIO_InitStructure);
  OLED_SCL(1);
  OLED_SDA(1);
  OLED_WriteCommand(OLED_Init_Command);
  OLED_Clear();
}

/**
 * @brief  I2C写SCL
 * @param BitVal
 * 0 Bit_RESET
 * 1 Bit_SET
 */
void OLED_SCL(uint8_t BitVal)
{
  GPIO_WriteBit(OLED_GPIO_SCL, OLED_GPIO_Pin_SCL, (BitAction)BitVal);
}

/**
 * @brief  I2C写SDA
 * @param BitVal
 * 0 Bit_RESET
 * 1 Bit_SET
 */
void OLED_SDA(uint8_t BitVal)
{
  GPIO_WriteBit(OLED_GPIOx_SDA, OLED_GPIO_Pin_SDA, (BitAction)BitVal);
}

/**
 * @brief  I2C开始
 */
void OLED_I2C_Start(void)
{
  OLED_SDA(1);
  OLED_SCL(1);
  OLED_SDA(0);
  OLED_SCL(0);
}

/**
 * @brief  I2C停止
 */
void OLED_I2C_Stop(void)
{
  OLED_SDA(0);
  OLED_SCL(1);
  OLED_SDA(1);
}

/**
 * @brief  I2C发送一个字节
 * @param  Byte 字节
 */
void OLED_I2C_SendByte(uint8_t Byte)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    // !!作用：把非0的数字转为1
    OLED_SDA(!!(Byte & (0x80 >> i)));
    OLED_SCL(1);
    OLED_SCL(0);
  }
  // 额外的一个时钟，不处理应答信号
  OLED_SCL(1);
  OLED_SCL(0);
}

/**
 * @brief  写命令
 * @param  Command 命令
 */
void OLED_WriteCommand(uint8_t *Command)
{
  OLED_WriteByteArray(0x00, Command);
}

/**
 * @brief  写数据
 * @param  Data 数据
 */
void OLED_WriteData(uint8_t *Data)
{
  OLED_WriteByteArray(0x78, Data);
}

/**
 * @brief  写字节数组
 * @param  Control 控制字节
 * @param  ByteArray 字节数组
 */
void OLED_WriteByteArray(uint8_t Control, uint8_t *ByteArray)
{
  OLED_I2C_Start();
  // 从机地址
  OLED_I2C_SendByte(0x78);
  OLED_I2C_SendByte(Control);
  uint8_t Length = sizeof(ByteArray) / sizeof(uint8_t);
  for (uint8_t i = 0; i < Length; i++)
  {
    OLED_I2C_SendByte(ByteArray[i]);
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
  uint8_t command[] = {
      // 行
      0xB0 | Row,
      // 列的高4位
      0x10 | ((Col & 0xF0) >> 4),
      // 列的低4位
      0x00 | (Col & 0x0F)};
  OLED_WriteCommand(command);
}

/**
 * @brief  清屏
 */
void OLED_Clear(void)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    OLED_SetCursor(i, 0);
    OLED_WriteData(OLED_ROW_EMPTY);
  }
}
