// main.c
// Desenvolvido para a placa EK-TM4C1294XL + Shield LCD(1602b) + Teclado (4x4)
// Exemplo: Verifica o estado das chavse USRs SW1 e SW2 e acende os LEDs 1 e 2 caso esteja pressionada, inicializa o LCD, escreve tecla pessionada no Teclado (4x4) no LCD.
// Projeto e Esquematico do Shield: http://www.elf52.daeln.com.br
// Prof. DaLuz
// Prof. Guilherme Peron
// Prof. Marcos P.

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "gpio.h"
#include "lcd2.h"
#include "teclado.h"


int main(void)
{
	uint8_t Tecla;
	unsigned int i;
	char lcd_buffer[16];
	PLL_Init();
	SysTick_Init();
	GPIO_Init();
	LCD_Init();
	LCD_EspecialChar();
	sprintf(lcd_buffer,"ELF52-DaLuz:");
	LCD_Escreve_Inst(0x80);
	for (i=0;i<strlen(lcd_buffer);i++) LCD_Escreve_Dado(lcd_buffer[i]);
	LCD_Escreve_Dado(0x00); //Caracter Especial
	LCD_Escreve_Dado(0x02); //Caracter Especial
	LCD_Escreve_Dado(0x04); //Caracter Especial
	LCD_Escreve_Dado(0x06);	//Caracter Especial
	while (1)
	{
		Tecla=VarreTeclado();
	  
		if (Tecla=='A'||Tecla=='B'||Tecla=='C'||Tecla=='D') PortN_Output(0x1);
		if (Tecla=='#'||Tecla=='1'||Tecla=='4'||Tecla=='7') PortN_Output(0x2);
		if (Tecla=='0'||Tecla=='2'||Tecla=='5'||Tecla=='8') PortN_Output(0x3);
		if (Tecla=='*'||Tecla=='3'||Tecla=='6'||Tecla=='9') PortN_Output(0x3);

	  	if (Tecla==0) Tecla='?'; 
		
		LCD_Escreve_Inst(0xC0);
		sprintf(lcd_buffer,"Key: [%X]-[%c]", Tecla,Tecla);
	  	for (i=0;i<strlen(lcd_buffer);i++) LCD_Escreve_Dado(lcd_buffer[i]);
    
		//Se a USR_SW2 estiver pressionada
		if (PortJ_Input() == 0x1)
			PortN_Output(0x1);
   		//Se a USR_SW1 estiver pressionada
		else if (PortJ_Input() == 0x2)
			PortN_Output(0x2);
   		//Se ambas estiverem pressionadas
		else if (PortJ_Input() == 0x0)
			PortN_Output(0x3);
    	//Se nenhuma estiver pressionada
		else if (PortJ_Input() == 0x3)
			PortN_Output(0x0);        
	}
}
