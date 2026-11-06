#ifndef UART_H
#define UART_H

#include <stdint.h>

#define UART_BAUD_RATE 115200

void UART0_Init(uint32_t ui32Clock);
int32_t UART0_RecebeByte(void);
void UART0_EnviaPacote(const uint8_t *pui8Pacote, uint32_t ui32Tamanho);

#endif
