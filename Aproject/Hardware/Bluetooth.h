#ifndef __BLUETOOTH_H
#define __BLUETOOTH_H
#include "stdint.h"

void Bluetooth_Init(void);
void USART1_IRQHandler(void);
uint8_t GetRxFlag(void);
uint8_t GetRxData(void);
void SendByte(uint16_t Byte);
#endif