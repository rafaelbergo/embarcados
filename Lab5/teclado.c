#define PART_TM4C1294NCPDT 1

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "teclado.h"

// Colunas C0 a C3 = PM4 a PM7 (saidas)
// Linhas L0 a L3 = PL0 a PL3 (entradas com pull-up)
#define PINOS_COLUNAS (GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7)
#define PINOS_LINHAS  (GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3)

// Inicializa as colunas como saida e as linhas como entrada com pull-up
void Teclado_Init(void)
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);

  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOL)) { }
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOM)) { }

  GPIOPinTypeGPIOOutput(GPIO_PORTM_BASE, PINOS_COLUNAS);
  GPIOPinTypeGPIOInput(GPIO_PORTL_BASE, PINOS_LINHAS);
  GPIOPadConfigSet(GPIO_PORTL_BASE, PINOS_LINHAS, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
  GPIOPinWrite(GPIO_PORTM_BASE, PINOS_COLUNAS, PINOS_COLUNAS);
}

// Ativa uma coluna (1 a 4) colocando-a em nivel baixo
static void AtivaColuna(uint8_t coluna)
{
  switch (coluna)
  {
    case 1: GPIOPinWrite(GPIO_PORTM_BASE, PINOS_COLUNAS, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7); break;
    case 2: GPIOPinWrite(GPIO_PORTM_BASE, PINOS_COLUNAS, GPIO_PIN_4 | GPIO_PIN_6 | GPIO_PIN_7); break;
    case 3: GPIOPinWrite(GPIO_PORTM_BASE, PINOS_COLUNAS, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_7); break;
    case 4: GPIOPinWrite(GPIO_PORTM_BASE, PINOS_COLUNAS, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6); break;
    default: GPIOPinWrite(GPIO_PORTM_BASE, PINOS_COLUNAS, PINOS_COLUNAS); break;
  }
}

// Retorna qual linha foi acionada (1 a 4) ou 0 se nenhuma
static uint8_t LeLinha(void)
{
  uint32_t portL = GPIOPinRead(GPIO_PORTL_BASE, PINOS_LINHAS);

  switch (portL)
  {
    case 0x0E: return 1;
    case 0x0D: return 2;
    case 0x0B: return 3;
    case 0x07: return 4;
    default:   return 0;
  }
}

// Varre o teclado e devolve a tecla pressionada, ou 0 se nenhuma
uint8_t Teclado_Le(void)
{
  static const char mapa[4][4] =
  {
    // coluna 1, 2, 3, 4
    { '7', '8', '9', 'A' }, // linha 1
    { '4', '5', '6', 'B' }, // linha 2
    { '1', '2', '3', 'C' }, // linha 3
    { '#', '0', '*', 'D' }  // linha 4
  };

  uint8_t coluna;
  uint8_t linha;

  for (coluna = 1; coluna <= 4; coluna++)
  {
    AtivaColuna(coluna);
    linha = LeLinha();

    if (linha)
    {
      // Deixa as colunas em nivel alto antes de retornar
      AtivaColuna(0);
      return (uint8_t)mapa[linha - 1][coluna - 1];
    }
  }

  AtivaColuna(0);
  return 0;
}
