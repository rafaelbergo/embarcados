#define PART_TM4C1294NCPDT 1

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "uart.h"

// Configura a UART0 para 115200, 8 bits, sem paridade e 1 stop bit
void UART0_Init(uint32_t clock)
{
  // Habilita os perifericos
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

  // Aguarda os perifericos
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA)) {}
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0)) {}

  // Configura os pinos
  GPIOPinConfigure(GPIO_PA0_U0RX);
  GPIOPinConfigure(GPIO_PA1_U0TX);
  GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
  
  UARTClockSourceSet(UART0_BASE, UART_CLOCK_SYSTEM);
  UARTStdioConfig(0, UART_BAUD_RATE, clock);
}

// Le um byte do UART0, se nao existir retorna -1
int32_t UART0_RecebeByte(void)
{
  // Verifica se tem byte disponivel
  if (!UARTCharsAvail(UART0_BASE))
  {
    return -1;
  }

  // Verifica se houve erros no UART
  if (UARTRxErrorGet(UART0_BASE))
  {
    UARTRxErrorClear(UART0_BASE);
  }

  return UARTCharGetNonBlocking(UART0_BASE);
}

// Envia um pacote de bytes
void UART0_EnviaPacote(const uint8_t *pacote, uint32_t tamanho)
{
  uint32_t indice;

  for (indice = 0; indice < tamanho; indice++)
  {
    UARTCharPut(UART0_BASE, pacote[indice]);
  }
}
