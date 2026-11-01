#define PART_TM4C1294NCPDT 1

#include <stdint.h>
#include <stdbool.h>
#include "driverlib/sysctl.h"
#include "utils.h"

uint32_t SysClock;

// -------------------------------------------------------------------------------
// Funcao PLL_Init
// Configura o sistema para utilizar o clock do PLL
// Parametro de entrada: Nao tem
// Parametro de sada: Nao tem
void PLL_Init(void)
{
  SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_240), 80000000);
}

// -------------------------------------------------------------------------------
// Funcao SysTick_Init
// Parametro de entrada: Nao tem
// Parametro de sada: Nao tem
void SysTick_Init(void)
{

}

// -------------------------------------------------------------------------------
// Funcao SysTick_Wait1ms
// Atraso de tempo utilizando processador ocupado
// Parametro de entrada: Numero de vezes para contar 1ms
// Parametro de saida: Nao tem
void SysTick_Wait1ms(uint32_t delay)
{
  SysCtlDelay((uint32_t)(((uint64_t)SysClock * (uint64_t)delay) / 3000));
}

// -------------------------------------------------------------------------------
// Funcao SysTick_Wait1us
// Atraso de tempo utilizando processador ocupado
// Parametro de entrada: Numero de vezes para contar 1us.
// Parametro de saida: Nao tem
void SysTick_Wait1us(uint32_t delay)
{
  SysCtlDelay((uint32_t)(((uint64_t)SysClock * (uint64_t)delay) / 3000000));
}
