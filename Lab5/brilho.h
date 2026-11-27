#ifndef BRILHO_H
#define BRILHO_H

#include <stdint.h>

#define BRILHO_DIGITO_VAZIO 0xFF

void Set_Brilho_Inicial(uint8_t valorInicial);
uint8_t Get_Brilho(void);
uint8_t Get_Brilho_Digito1(void);
uint8_t Get_Brilho_Digito2(void);
uint8_t Editando_Brilho(void);
uint8_t Brilho_Tecla(uint8_t tecla);

#endif
