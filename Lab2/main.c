/*##############################################################################
Prof. Paulo Denis Garcez da Luz - 2023/2S
Desenvolvido para a placa EK-TM4C1294XL utilizando o SDK TivaWare no KEIL
Programa exemplo de blink(1s) usando apenas 1 led e Periférico SysTick.
##############################################################################*/

//TivaWare uC: Usado internamente para identificar o uC em alguns .h da TivaWare
#define PART_TM4C1294NCPDT 1

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"

#define WIDTH0 4
#define HEIGTH0 3
const uint8_t image0[HEIGTH0][WIDTH0] = {
    { 20,  16,  16,  18},
    {255, 255,   0,   0},
    { 32,  32,  32,  32}
};

//Protótipos de funções criadas no programa, código depois do main
uint16_t EightBitHistogram_C(uint16_t width, uint16_t height, uint8_t * p_image, uint16_t * p_histogram);

int main(void)
{
  //Configura o clock para utilizar o xtal interno de 16MHz com PLL para 40MHz
  //SysCtlClockFreqSet(SYSCTL_OSC_INT | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_320, 40000000);
  
	uint16_t meu_histograma[256];
  uint16_t pixels_processados;
	// Nota: Fazemos um cast (uint8_t *) em image0 porque ela é uma matriz 2D e a função espera um ponteiro 1D
	pixels_processados = EightBitHistogram_C(WIDTH0, HEIGTH0, (uint8_t *)image0, meu_histograma);

	printf("Valor do Pixel, Quantidade\n");

    // Varre as 256 posicoes do histograma
    for (int i = 0; i < 256; i++)
    {
        // Imprime no formato CSV: "Indice, Valor"
        printf("%d, %d\n", i, meu_histograma[i]);
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

