#ifndef RELES_H
#define RELES_H

#include <stdint.h>

#define NUM_RELES 3

void Reles_Init(void);
void Rele_Liga(uint8_t numeroRele);
void Rele_Desliga(uint8_t numeroRele);
void Rele_LigaTodos(void);
void Rele_DesligaTodos(void);
uint8_t Rele_Status(void);

#endif
