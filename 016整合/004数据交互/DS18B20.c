#include <REGX52.H>
#include "OneWire.h"

//DS18B20指令
#define DS18B20_SKIP_ROM 0xCC
#define DS18B20_CONVERT_T 0x44
#define DS18B20_READ_SCRATCHPAD 0xBE

/**
  * @brief  DS18B20开始温度变换
  */
void DS18B20_ConvertT()
{
  OneWire_Init();
  OneWire_SendByte(DS18B20_SKIP_ROM);
  OneWire_SendByte(DS18B20_CONVERT_T);
}

/**
  * @brief  DS18B20读取温度
  * @retval 温度数值*10000
  */
long DS18B20_ReadT()
{
  unsigned char TLSB, TMSB;
  long Temp;
  OneWire_Init();
  OneWire_SendByte(DS18B20_SKIP_ROM);
  OneWire_SendByte(DS18B20_READ_SCRATCHPAD);
  TLSB = OneWire_ReceiveByte();
  TMSB = OneWire_ReceiveByte();
  Temp = (TMSB << 8) | TLSB;
  Temp = Temp * 10000 / 16;
  return Temp;
}
