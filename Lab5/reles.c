#define PART_TM4C1294NCPDT 1

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "reles.h"

#define PINO_RELE0 GPIO_PIN_1 //PN1 = LED1
#define PINO_RELE1 GPIO_PIN_0 //PN0 = LED2
#define PINO_RELE2 GPIO_PIN_4 //PF4 = LED3

#define PINOS_PORTN (PINO_RELE0 | PINO_RELE1)
#define PINOS_PORTF (PINO_RELE2)

// Estado reles - bit 3 = rele 0, bit 2 = rele 1, bit 1 = rele 2
static uint8_t estadoReles;

// Atualiza o estado dos reles nos leds
static void Reles_Atualiza(void)
{
  uint8_t portN = 0;
  uint8_t portF = 0;

  // Rele 0 -> LED1 (PN1), Rele 1 -> LED2 (PN0)
  if (estadoReles & 0x08) portN |= PINO_RELE0;
  if (estadoReles & 0x04) portN |= PINO_RELE1;

  // Rele 2 -> LED3 (PF4)
  if (estadoReles & 0x02) portF |= PINO_RELE2;

  GPIOPinWrite(GPIO_PORTN_BASE, PINOS_PORTN, portN);
  GPIOPinWrite(GPIO_PORTF_BASE, PINOS_PORTF, portF);
}

// Inicializa os pinos dos LEDs e desliga todos os reles
void Reles_Init(void)
{
  // Leds comecam desligados
  estadoReles = 0;

  // Habilita os perifericos
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);

  // Aguarda os perifericos
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)) { }
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)) { }

  GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, PINOS_PORTN);
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, PINOS_PORTF);

  Reles_Atualiza();
}

// Liga um rele pelo numero
void Rele_Liga(uint8_t numeroRele)
{
  if (numeroRele < NUM_RELES)
  {
    estadoReles |= (uint8_t)(0x08 >> numeroRele);
    Reles_Atualiza();
  }
}

// Desliga um rele pelo numero
void Rele_Desliga(uint8_t numeroRele)
{
  if (numeroRele < NUM_RELES)
  {
    estadoReles &= (uint8_t)~(0x08 >> numeroRele);
    Reles_Atualiza();
  }
}

// Liga os 3 reles
void Rele_LigaTodos(void)
{
  estadoReles = 0x0E; // 1110
  Reles_Atualiza();
}

// Desliga os 3 reles
void Rele_DesligaTodos(void)
{
  estadoReles = 0x00;
  Reles_Atualiza();
}

// Retorna o estado dos reles
uint8_t Rele_Status(void)
{
  return estadoReles;
}
