#ifndef PWM_H
#define PWM_H

#include <stdint.h>

#define BRILHO_MAX 99

void Init_PWM_Brilho(void);
void Set_PWM_Brilho(uint8_t brilho);

#endif
