#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

extern uint32_t SysClock;

void PLL_Init(void);
void SysTick_Init(void);
void SysTick_Wait1ms(uint32_t delay);
void SysTick_Wait1us(uint32_t delay);

#endif
