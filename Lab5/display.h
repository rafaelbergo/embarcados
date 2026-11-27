#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

void Display_Init(void);

// Reles
void Display0_Estado(uint8_t estadoReles);

// Brilho
void Display7_Brilho(uint8_t brilho);
void Display7_Edicao(uint8_t dezena, uint8_t unidade);
void Display7_Tecla(uint8_t tecla);

#endif
