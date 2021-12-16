#ifndef __UART_H__
#define __UART_H__

void UartInit();
void UartSendByte(unsigned char byte);
void UartSendString(unsigned char *str);
void UartSendByteArray(unsigned char bytes[], unsigned char len);
void UartSendInt(unsigned int i);
void UartSendLong(unsigned long i);

#endif