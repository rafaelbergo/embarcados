/*##############################################################################
Prof. Paulo Denis Garcez da Luz - 2024/1S
Desenvolvido para a placa EK-TM4C1294XL com SDK TivaWare e FreeRTOS
Programa exemplo de blink usando 1 led e FreeRTOS.
##############################################################################*/

/* TivaWare uC: Usado internamente para identificar o uC em alguns .h da TivaWare */
#define PART_TM4C1294NCPDT 1

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"

/* Bibliotecas FreeRTOS */
#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"

/* Vari?vel Global com o valor do SystemClock: */
uint32_t SystemCoreClock=16000000;

/* Vari?veis para armazenamento dos handles da Tasks */
TaskHandle_t task1Handle = NULL;

/* Prot?tipos das Tasks */
void vTask1(void *pvParameters);

int main(void)
{
  /* cria??o da vari?vel de retorno da cria??o da task */
  BaseType_t xReturned;
  /* Configura o clock para utilizar o xtal interno de 16MHz com PLL para 16MHz */
  SysCtlClockFreqSet(SYSCTL_OSC_INT | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_320, 16000000);
  /* habilitar gpio port N */
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
  /* aguardar o perif?rico ficar pronto para uso */
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)) {/*espera habilitar o port*/}
  /* configura o pin_0 como sa?da */
  GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);
  /* Cria??o das Tasks */
  xReturned = xTaskCreate(vTask1,"Task1",configMINIMAL_STACK_SIZE,NULL,1,&task1Handle);
  if (xReturned == pdFAIL)
     {
      while(1);
     }
	vTaskStartScheduler();
}

/* vTask1 => inverte LED em intervalos de 500 ms */
void vTask1(void *pvParameters)
{
  /* loop infinito na Task1 */
  while (1)
        {
          /* envia o estado ON do led para o pin 0 do port N */
          GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 1);
          /* Delay de 1000ms devolvendo o processador para o Scheduler */        
					vTaskDelay(pdMS_TO_TICKS(1000));
          /* envia o estado OFF do led para o pin 0 do port N */
          GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0);
          /* Delay de 1000ms devolvendo o processador para o Scheduler */        
          vTaskDelay(pdMS_TO_TICKS(1000));
        }
}
