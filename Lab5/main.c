#define PART_TM4C1294NCPDT 1

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "uart.h"
#include "reles.h"
#include "pwm.h"
#include "brilho.h"
#include "teclado.h"
#include "display.h"
#include "protocolo.h"

#define PERIODO_TECLADO 20 // Usado para debounce do teclado, le a cada 20 ms
#define BRILHO_INICIAL 50

uint32_t SysClock;
static volatile uint32_t SysTicks1ms;

void SetupSystick(void);
void SysTickIntHandler(void);

int main(void)
{
  uint8_t tecla;
  uint8_t teclaAnterior = 0;
  uint8_t estadoRele;
  uint32_t proximaTecla;

  // Configura o clock para utilizar o xtal interno de 16MHz com PLL para 40MHz
  SysClock = SysCtlClockFreqSet(SYSCTL_OSC_INT | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_320, 40000000);
  SetupSystick();

  UART0_Init(SysClock);
  Reles_Init();
  Init_PWM_Brilho();
  Teclado_Init();
  Protocolo_Init();
  Display_Init();

  // Define o brilho inicial e mostra no display
  Set_Brilho_Inicial(BRILHO_INICIAL);
  Display7_Brilho(BRILHO_INICIAL);

  // Desenha o estado inicial dos reles no display
  estadoRele = Rele_Status();
  Display0_Estado(estadoRele);

  proximaTecla = SysTicks1ms + PERIODO_TECLADO;

  while (1)
  {
    // Limpa a UART
    UART0_Drena();
    Protocolo_Processa();

    // Se rele mudou de estado desenha novamente
    if (Rele_Status() != estadoRele)
    {
      estadoRele = Rele_Status();
      Display0_Estado(estadoRele);
    }

    // Le o teclado a cada 20ms
    if ((int32_t)(SysTicks1ms - proximaTecla) >= 0)
    {
      proximaTecla = SysTicks1ms + PERIODO_TECLADO;
      tecla = Teclado_Le();

      if (tecla != teclaAnterior)
      {
        teclaAnterior = tecla;

        if (tecla)
        {
          Display7_Tecla(tecla);

          // Atualiza o display do brilho so quando algo mudou
          if (Brilho_Tecla(tecla))
          {
            if (Editando_Brilho())
            {
              Display7_Edicao(Get_Brilho_Digito1(), Get_Brilho_Digito2());
            }
            else
            {
              Display7_Brilho(Get_Brilho());
            }
          }
        }
      }
    }
  }
}

void SysTickIntHandler(void)
{
  SysTicks1ms++;
}

void SetupSystick(void)
{
  SysTicks1ms = 0;

  SysTickDisable();

  // SysClock / 1000 contagens = 1 ms, descontando a troca de contexto
  SysTickPeriodSet(SysClock / 1000 - 1 - 12 - 6);
  SysTickIntRegister(SysTickIntHandler);
  SysTickIntEnable();
  SysTickEnable();
}
