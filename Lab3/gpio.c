// gpio.c
// Desenvolvido para a placa EK-TM4C1294XL + Shield LCD(1602b) + Teclado (4x4)
// Inicializa as portas ...
// Projeto e Esquematico do Shield: http://www.elf52.daeln.com.br
// Prof. DaLuz
// Prof. Guilherme Peron
// Prof. Marcos P.

#define PART_TM4C1294NCPDT 1

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "gpio.h"

#define PINOS_LCD_CONTROLE (GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2) //PM2..PM0
#define PINOS_LCD_DADOS (GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7) //PK7..PK0
#define PINOS_TECLADO_COLUNA (GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7) //PM7..PM4
#define PINOS_TECLADO_LINHA (GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3) //PL3..PL0
#define PINOS_LEDS (GPIO_PIN_0 | GPIO_PIN_1) //PN1..PN0
#define PINOS_CHAVES (GPIO_PIN_0 | GPIO_PIN_1) //PJ1..PJ0

// -------------------------------------------------------------------------------
// Funcao GPIO_Init
// Inicializa os ports 
// Parametro de entrada: Nao tem
// Parametro de saida: Nao tem
void GPIO_Init(void)
{
  //1a. Ativar o clock para a porta setando o bit correspondente no registrador RCGCGPIO
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);  
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);

  //1b. apos isso verificar no PRGPIO se a porta esta pronta para uso.
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC)) { }
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ)) { }
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOK)) { }
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOL)) { }
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOM)) { }
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)) { }

  //2 a 6. 
  //J1 e J0 entrada (chaves USR_SW2 e USR_SW1)
  GPIOPinTypeGPIOInput(GPIO_PORTJ_AHB_BASE, PINOS_CHAVES);
  //K7-K0 saida (LCD dados)
  GPIOPinTypeGPIOOutput(GPIO_PORTK_BASE, PINOS_LCD_DADOS);
  //L3-L0 entrada (linhas teclado)
  GPIOPinTypeGPIOInput(GPIO_PORTL_BASE, PINOS_TECLADO_LINHA);
  //M2-M0 e M7-M4 saida (colunas teclado)
  GPIOPinTypeGPIOOutput(GPIO_PORTM_BASE, PINOS_LCD_CONTROLE | PINOS_TECLADO_COLUNA);
  //N1 e N0 saida (LEDs 1 e 2)
  GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, PINOS_LEDS);

  // 7. Habilitar resistor de pull-up interno, setar PUR para 1
  GPIOPadConfigSet(GPIO_PORTJ_AHB_BASE, PINOS_CHAVES, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
  GPIOPadConfigSet(GPIO_PORTL_BASE, PINOS_TECLADO_LINHA, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
}

// -------------------------------------------------------------------------------
// Funcao PortJ_Input
// Le os valores de entrada do port J
// Parametro de entrada: Nao tem
// Parametro de saida: o valor da leitura do port
uint32_t PortJ_Input(void)
{
  return GPIOPinRead(GPIO_PORTJ_AHB_BASE, PINOS_CHAVES);
}

// -------------------------------------------------------------------------------
// Funcao PortK_Output
// Escreve os valores no port K
// Parametro de entrada: Valor a ser escrito
// Parametro de saida: nao tem
void PortK_Output(uint32_t valor)
{
  GPIOPinWrite(GPIO_PORTK_BASE, PINOS_LCD_DADOS, valor);
}

// -------------------------------------------------------------------------------
// Funcao PortL_Input
// Le os valores de entrada do port L
// Parametro de entrada: Nao tem
// Parametro de saida: o valor da leitura do port
uint32_t PortL_Input(void)
{
  return GPIOPinRead(GPIO_PORTL_BASE, PINOS_TECLADO_LINHA); //Somente os L3-L0
}

// -------------------------------------------------------------------------------
// Funcao PortM_Output
// Escreve os valores no port M
// Parametro de entrada: Valor a ser escrito
// Parametro de saida: nao tem
void PortM_Output(uint32_t valor)
{
  GPIOPinWrite(GPIO_PORTM_BASE, PINOS_LCD_CONTROLE, (uint8_t)valor);
}

// -------------------------------------------------------------------------------
// Funcao PortM_Output2
// Escreve os valores no port M Pinos 4 a 7
// Parametro de entrada: Valor a ser escrito
// Parametro de saida: nao tem
void PortM_Output2(uint32_t valor)
{
  GPIOPinWrite(GPIO_PORTM_BASE, PINOS_TECLADO_COLUNA, (uint8_t)valor);
}

// -------------------------------------------------------------------------------
// Funcao PortN_Output
// Escreve os valores no port N
// Parametro de entrada: Valor a ser escrito
// Parametro de saida: nao tem
void PortN_Output(uint32_t valor)
{
  GPIOPinWrite(GPIO_PORTN_BASE, PINOS_LEDS, valor);
}
