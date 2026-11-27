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

// Usa um buffer circular para evitar perda de bytes
#define TAM_BUFFER_RX 64

static uint8_t bufferRx[TAM_BUFFER_RX];
static uint32_t posEscrita;
static uint32_t posLeitura;

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

  // Habilita a FIFO para evitar perda de bytes
  UARTFIFOEnable(UART0_BASE);

  posEscrita = 0;
  posLeitura = 0;
}

// Copia para o buffer circular tudo o que chegou na FIFO da UART
void UART0_Drena(void)
{
  uint32_t proxima;

  while (UARTCharsAvail(UART0_BASE))
  {
    proxima = (posEscrita + 1) % TAM_BUFFER_RX;

    // Buffer cheio para de drenar para nao sobrescrever dado nao lido
    if (proxima == posLeitura)
    {
      return;
    }

    bufferRx[posEscrita] = (uint8_t)UARTCharGetNonBlocking(UART0_BASE);
    posEscrita = proxima;
  }
}

// Le um byte do UART0, se nao existir retorna -1
int32_t UART0_RecebeByte(void)
{
  uint8_t dado;

  if (posLeitura == posEscrita)
  {
    return -1;
  }

  dado = bufferRx[posLeitura];
  posLeitura = (posLeitura + 1) % TAM_BUFFER_RX;

  return (int32_t)dado;
}

// Envia um pacote de bytes
void UART0_EnviaPacote(const uint8_t *pacote, uint32_t tamanho)
{
  uint32_t indice;

  for (indice = 0; indice < tamanho; indice++)
  {
    // Drena antes de enviar cada byte
    UART0_Drena();
    UARTCharPut(UART0_BASE, pacote[indice]);
  }
}
