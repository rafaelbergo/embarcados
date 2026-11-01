// gpio.h
// Desenvolvido para o Shield Tiva EK-TM4C1294XL: LCD (1602B) + TECLADO Matricial (4x4) @DaLuz
// Projeto e Esquematico do Shield: http://www.elf52.daeln.com.br
// Prof. DaLuz
// Prof. Guilherme Peron
// Prof. Marcos P.

#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

void GPIO_Init(void);
uint32_t PortJ_Input(void);
void PortK_Output(uint32_t valor);
uint32_t PortL_Input(void);
void PortM_Output(uint32_t valor);
void PortM_Output2(uint32_t valor);
void PortN_Output(uint32_t valor);

#endif
