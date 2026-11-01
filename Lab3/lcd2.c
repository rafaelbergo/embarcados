/*
// Desenvolvido para o Shield Tiva EK-TM4C1294XL: LCD (1602B) + TECLADO Matricial (4x4) @DaLuz
// Projeto e Esquematico do Shield: http://www.elf52.daeln.com.br
// Prof. DaLuz
// Prof. Guilherme Peron
// Prof. Marcos P.
// Controle do LCD:
// RS  = PM0
// R/W = PM1
// EN  = PM2
// Barramento do LCD: PORT K (8bits)
*/

#include <stdint.h>
#include "lcd2.h"
#include "gpio.h"
#include "utils.h"

void LCD_Init(void)
{
  LCD_Command(0);
  SysTick_Wait1ms(16);
  LCD_Escreve_Inst(56);
  LCD_Escreve_Inst(12);
  LCD_Escreve_Inst(1);
  LCD_Escreve_Inst(6);
  SysTick_Wait1us(1600);
}

void LCD_Command(uint32_t data)
{
  PortM_Output(data);
}

void LCD_Data(uint32_t data)
{
  PortK_Output(data);
}

void LCD_Escreve_Inst(uint32_t dado)
{
  LCD_Data(dado);
  LCD_Command(0);

  SysTick_Wait1us(6);
  LCD_Command(4);

  SysTick_Wait1us(6);
  LCD_Command(0);
  SysTick_Wait1us(40);
}

void LCD_Escreve_Dado(uint32_t dado)
{
  LCD_Data(dado);
  LCD_Command(1);
  SysTick_Wait1us(6);

  LCD_Command(5);
  SysTick_Wait1us(6);

  LCD_Command(1);
  SysTick_Wait1us(40);
  SysTick_Wait1us(1600);
}

void LCD_EspecialChar(void)
{
LCD_Escreve_Inst(0x40);
LCD_Escreve_Dado(0x0E);
LCD_Escreve_Dado(0x1B);
LCD_Escreve_Dado(0x11);
LCD_Escreve_Dado(0x11);
LCD_Escreve_Dado(0x11);
LCD_Escreve_Dado(0x11);
LCD_Escreve_Dado(0x11);
LCD_Escreve_Dado(0x1F);

LCD_Escreve_Inst(0x48);
LCD_Escreve_Dado(0x0E);
LCD_Escreve_Dado(0x1B);
LCD_Escreve_Dado(0x11);
LCD_Escreve_Dado(0x11);
LCD_Escreve_Dado(0x11);
LCD_Escreve_Dado(0x11);
LCD_Escreve_Dado(0x1F);
LCD_Escreve_Dado(0x1F);

LCD_Escreve_Inst(0x50);
LCD_Escreve_Dado(0x0E);
LCD_Escreve_Dado(0x1B);
LCD_Escreve_Dado(0x11);
LCD_Escreve_Dado(0x11);
LCD_Escreve_Dado(0x11);
LCD_Escreve_Dado(0x1F);
LCD_Escreve_Dado(0x1F);
LCD_Escreve_Dado(0x1F);

LCD_Escreve_Inst(0x58);
LCD_Escreve_Dado(0x0E);
LCD_Escreve_Dado(0x1B);
LCD_Escreve_Dado(0x11);
LCD_Escreve_Dado(0x11);
LCD_Escreve_Dado(0x1F);
LCD_Escreve_Dado(0x1F);
LCD_Escreve_Dado(0x1F);
LCD_Escreve_Dado(0x1F);

LCD_Escreve_Inst(0x60);
LCD_Escreve_Dado(0x0E);
LCD_Escreve_Dado(0x1B);
LCD_Escreve_Dado(0x11);
LCD_Escreve_Dado(0x1F);
LCD_Escreve_Dado(0x1F);
LCD_Escreve_Dado(0x1F);
LCD_Escreve_Dado(0x1F);
LCD_Escreve_Dado(0x1F);

LCD_Escreve_Inst(0x68);
LCD_Escreve_Dado(0x0E);
LCD_Escreve_Dado(0x1B);
LCD_Escreve_Dado(0x1F);
LCD_Escreve_Dado(0x1F);
LCD_Escreve_Dado(0x1F);
LCD_Escreve_Dado(0x1F);
LCD_Escreve_Dado(0x1F);
LCD_Escreve_Dado(0x1F);

LCD_Escreve_Inst(0x70);
LCD_Escreve_Dado(0x0E);
LCD_Escreve_Dado(0x1F);
LCD_Escreve_Dado(0x1F);
LCD_Escreve_Dado(0x1F);
LCD_Escreve_Dado(0x1F);
LCD_Escreve_Dado(0x1F);
LCD_Escreve_Dado(0x1F);
LCD_Escreve_Dado(0x1F);

LCD_Escreve_Inst(0x78);
LCD_Escreve_Dado(0x04);
LCD_Escreve_Dado(0x0E);
LCD_Escreve_Dado(0x0E);
LCD_Escreve_Dado(0x0E);
LCD_Escreve_Dado(0x0E);
LCD_Escreve_Dado(0x1F);
LCD_Escreve_Dado(0x00);
LCD_Escreve_Dado(0x04);
}
