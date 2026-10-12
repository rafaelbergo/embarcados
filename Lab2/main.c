#define PART_TM4C1294NCPDT 1

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"
#include "utils/uartstdio.h"

#define WIDTH0 4
#define HEIGTH0 3
const uint8_t image0[HEIGTH0][WIDTH0] = 
{
    { 20,  16,  16,  18},
    {255, 255,   0,   0},
    { 32,  32,  32,  32}
};

uint16_t meu_histograma[256];

uint16_t EightBitHistogram_C(uint16_t width, uint16_t height, uint8_t * p_image, uint16_t * p_histogram);

int main(void)
{
	  //Configura o clock para utilizar o xtal interno de 16MHz com PLL para 40MHz
		SysCtlClockFreqSet(SYSCTL_OSC_INT | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_320, 40000000);
  
		// Configuração UART0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
	
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_SYSTEM);
    UARTStdioConfig(0, 115200, 40000000);

    uint16_t pixels_processados;

    // Calcula o Histograma
    pixels_processados = EightBitHistogram_C(WIDTH0, HEIGTH0, (uint8_t *)image0, meu_histograma);
    
		UARTprintf("Pixels Processados: %d\n", pixels_processados);
    UARTprintf("X\tY\n");
    for (int i = 0; i < 256; i++)
    {
        UARTprintf("%d\t%d\n", i, meu_histograma[i]);
    }

    while (1) 
		{ 
		
		}
}

uint16_t EightBitHistogram_C(uint16_t width, uint16_t height, uint8_t * p_image, uint16_t * p_histogram)
{
    uint32_t image_size = (uint32_t)width * height;
    
		// Verifica tamanho maximo de 64K
		if (image_size > 65536)
		{
			return 0;
		}
		
		// Limpa o histograma
		for (int i = 0; i < 256; i++)
		{
			p_histogram[i] = 0;
		}
	
		// Calcula o histograma
		for (uint32_t i = 0; i < image_size; i++)
		{
			++p_histogram[p_image[i]];
		}
  
    return (uint16_t)image_size;    
}
