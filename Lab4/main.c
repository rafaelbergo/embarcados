#define PART_TM4C1294NCPDT 1

#include <stdint.h>
#include <stdbool.h>
#include "driverlib/sysctl.h"
#include "reles.h"
#include "uart.h"
#include "protocolo.h"

uint32_t SysClock;

int main(void)
{
  SysClock = SysCtlClockFreqSet(SYSCTL_OSC_INT | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_320, 40000000);
  Reles_Init();
  Protocolo_Init();

  // UART0 em 115200, 8 bits, sem paridade e 1 stop bit
  UART0_Init(SysClock);
 
  while (1)
  {
    Protocolo_Processa();
  }
}
