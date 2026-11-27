#define PART_TM4C1294NCPDT 1

#include <stdint.h>
#include <stdbool.h>
#include "pwm.h"
#include "brilho.h"

static uint8_t brilhoAtual;
static uint8_t digito1;
static uint8_t digito2;

void Set_Brilho_Inicial(uint8_t valorInicial)
{
  brilhoAtual = valorInicial;
  digito1 = BRILHO_DIGITO_VAZIO;
  digito2 = BRILHO_DIGITO_VAZIO;

  Set_PWM_Brilho(brilhoAtual);
}

uint8_t Get_Brilho(void)
{
  return brilhoAtual;
}

uint8_t Get_Brilho_Digito1(void)
{
  return digito1;
}

uint8_t Get_Brilho_Digito2(void)
{
  return digito2;
}

// Retorna 1 enquanto tem um digito preenchido
uint8_t Editando_Brilho(void)
{
  if (digito1 != BRILHO_DIGITO_VAZIO)
  {
    return 1;
  }

  return 0;
}

uint8_t Brilho_Tecla(uint8_t tecla)
{
  if ((tecla >= '0') && (tecla <= '9'))
  {
    if (digito1 == BRILHO_DIGITO_VAZIO)
    {
      // Converte o char para numero
      digito1 = (uint8_t)(tecla - '0');
    }

    else if (digito2 == BRILHO_DIGITO_VAZIO)
    {
      digito2 = (uint8_t)(tecla - '0');
    }

    else
    {
      return 0;
    }

    return 1;
  }

  // # confirma se 2 digitos preenchidos
  if (tecla == '#')
  {
    if ((digito1 == BRILHO_DIGITO_VAZIO) || (digito2 == BRILHO_DIGITO_VAZIO))
    {
      return 0;
    }

    // brilho atual = dezena * 10 + unidade 
    brilhoAtual = (uint8_t)(digito1 * 10 + digito2);

    digito1 = BRILHO_DIGITO_VAZIO;
    digito2 = BRILHO_DIGITO_VAZIO;

    Set_PWM_Brilho(brilhoAtual);

    return 1;
  }

  // * apaga o valor digitado
  if (tecla == '*')
  {
    if (digito1 == BRILHO_DIGITO_VAZIO)
    {
      return 0;
    }

    digito1 = BRILHO_DIGITO_VAZIO;
    digito2 = BRILHO_DIGITO_VAZIO;

    return 1;
  }

  return 0;
}
