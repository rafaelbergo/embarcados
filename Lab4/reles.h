#ifndef RELES_H
#define RELES_H

#include <stdint.h>

#define NUM_RELES 4

void Reles_Init(void);
void Rele_Liga(uint8_t ui8Numero);
void Rele_Desliga(uint8_t ui8Numero);
void Rele_LigaTodos(void);
void Rele_DesligaTodos(void);
uint8_t Rele_Estado(uint8_t ui8Numero);
uint8_t Rele_Status(void);

#endif
