#define PART_TM4C1294NCPDT 1

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "i2c.h"
#include "ssd1306.h"
#include "reles.h"
#include "display.h"

extern unsigned char SSD1306_Buffer[SSD1306_LCDWIDTH * SSD1306_LCDHEIGHT / 8];
extern const uint8_t ASCII_font5x8[][5];

// Desenha um caractere na posicao (x,y) com a cor (1=ligado, 0=desligado)
static void Display0_Caractere(uint8_t x, uint8_t y, char c, uint8_t cor)
{
  uint8_t coluna;
  uint8_t linha;
  uint8_t bits;

  // Verifica se o caractere existe no ASCII
  if (c < 0x20 || c > 0x7E)
  {
    c = '?';
  }

  for (coluna = 0; coluna < 5; coluna++)
  {
    bits = ASCII_font5x8[c - 0x20][coluna];

    for (linha = 0; linha < 8; linha++)
    {
      if (bits & (1 << linha))
      {
        SSD1306_I2C0_DrawPixel(x + coluna, y + linha, cor);
      }
    }
  }
}

// Desenha um texto na posicao (x,y) com a cor (1=ligado, 0=desligado)
static void Display0_Texto(uint8_t x, uint8_t y, const char *texto, uint8_t cor)
{
  while (*texto)
  {
    Display0_Caractere(x, y, *texto, cor);
    x += 6; // 5 pixels do caractere + 1 pixel de espaco
    texto++;
  }
}

// Desenha uma caixa na posicao (x,y)
static void Display0_Caixa(uint8_t x, uint8_t y, uint8_t largura, uint8_t altura, uint8_t preenchida)
{
  uint8_t i;
  uint8_t j;

  if (preenchida)
  {
    for (i = 0; i < altura; i++)
    {
      for (j = 0; j < largura; j++)
      {
        SSD1306_I2C0_DrawPixel(x + j, y + i, 1);
      }
    }
  }
  else
  {
    for (i = 0; i < largura; i++)
    {
      SSD1306_I2C0_DrawPixel(x + i, y, 1);
      SSD1306_I2C0_DrawPixel(x + i, y + altura - 1, 1);
    }

    for (i = 0; i < altura; i++)
    {
      SSD1306_I2C0_DrawPixel(x, y + i, 1);
      SSD1306_I2C0_DrawPixel(x + largura - 1, y + i, 1);
    }
  }
}

// Inicializa os displays, grafico (I2C0), texto (I2C7)
void Display_Init(void)
{
  I2C0_Init();
  OLED0_Init();
  SSD1306_I2C0_cls();

  I2C7_Init();
  OLED7_Init();
  OLED7_clearDisplay();

  // Textos fixos no display de texto
  OLED7_sendStrXYI("LED4/PF0 PWM", 0, 0);
  OLED7_sendStrXYI("ELF74 - LAB 5", 1, 0);
  OLED7_sendStrXYI("Tecla:  ?", 2, 0);
  OLED7_sendStrXYI("Brilho: 00%", 3, 0);
}

// Redesenha a caixa de acordo com o estado do rele
void Display0_Estado(uint8_t estadoReles)
{
  uint8_t i;

  SSD1306_I2C0_cls();
  Display0_Texto(16, 2, "ESTADO DOS RELES", 1);

  for (i = 0; i < NUM_RELES; i++)
  {
    uint8_t ligado = (estadoReles >> (3 - i)) & 0x01;
    uint8_t x = 4 + i * 42;
    char numero[3];

    numero[0] = 'R';
    numero[1] = (char)('0' + i);
    numero[2] = '\0';

    Display0_Caixa(x, 16, 36, 38, ligado);
    Display0_Texto(x + 13, 24, numero, ligado ? 0 : 1);
    if (ligado) // Deixa a cor como 0
    {
      // 12 = largura do texto (24) / 2
      // 38 = altura da caixa (38) - 8 (altura do texto) / 2
      Display0_Texto(x + 12, 38, "ON", 0);
    } 
      
    else 
    {
      // 9 = largura do texto (18) / 2
      // 38 = altura da caixa (38) - 8 (altura do texto) / 2
      Display0_Texto(x + 9, 38, "OFF", 1);      
    }       
  }

  SSD1306_I2C0_UpdateScreen();
}

// Exibe o valor do brilho de 00 a 99 no display
void Display7_Brilho(uint8_t brilho)
{
  OLED7_sendCharXYI((unsigned char)('0' + (brilho / 10) % 10), 3, 8);
  OLED7_sendCharXYI((unsigned char)('0' + (brilho % 10)), 3, 9);
}

// Exibe no display de texto os digitos que estao sendo digitados, ou _ se nao digitado ainda
void Display7_Edicao(uint8_t dezena, uint8_t unidade)
{
  OLED7_sendCharXYI((dezena <= 9) ? (unsigned char)('0' + dezena) : (unsigned char)'_', 3, 8);
  OLED7_sendCharXYI((unidade <= 9) ? (unsigned char)('0' + unidade) : (unsigned char)'_', 3, 9);
}

// Mostra a ultima tecla pressionada, ou ? se nenhuma pressionada
void Display7_Tecla(uint8_t tecla)
{
  OLED7_sendCharXYI((tecla == 0) ? (unsigned char)'?' : tecla, 2, 8);
}
