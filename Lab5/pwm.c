#define PART_TM4C1294NCPDT 1

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"
#include "driverlib/sysctl.h"
#include "pwm.h"

// 40 MHz / 40000 = 1 kHz de frequencia de PWM
#define PERIODO_PWM 40000

// Inicializa o PWM0 no pino PF0 (LED4)
void Init_PWM_Brilho(void)
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);

  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)) { }
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM0)) { }

  GPIOPinConfigure(GPIO_PF0_M0PWM0);
  GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_0);

  PWMClockSet(PWM0_BASE, PWM_SYSCLK_DIV_1);
  PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
  PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, PERIODO_PWM);
  PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, 0);
  PWMGenEnable(PWM0_BASE, PWM_GEN_0);

  // Comeca com o LED apagado
  Set_PWM_Brilho(0);
}

// Define o valor do brilho de 00 a 99
void Set_PWM_Brilho(uint8_t brilho)
{
  if (brilho > BRILHO_MAX)
  {
    brilho = BRILHO_MAX;
  }

  if (brilho == 0)
  {
    // Desliga a saida para apagar o LED
    PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, false);
    return;
  }

  PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, (PERIODO_PWM / 100) * brilho);
  PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, true);
}
