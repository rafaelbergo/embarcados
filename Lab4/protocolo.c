#include <stdint.h>
#include <stdbool.h>
#include "protocolo.h"
#include "reles.h"
#include "uart.h"

static uint8_t pacote[PROTO_TAMANHO];
static uint32_t indice;

// Zera o indice do pacote, preparacao para receber comando
void Protocolo_Init(void)
{
  indice = 0;
}

// Verificae o byte recebido e valida na posicao
static bool Protocolo_ByteValido(uint32_t posicao, uint8_t byte)
{
  switch (posicao)
  {
    case 0: // Comando comeca com #
      return (byte == PROTO_INICIO_CMD);

    case 1: // Depois de # pode vir R ou T
      return (byte == PROTO_TIPO_RELE) || (byte == PROTO_TIPO_TODOS);

    case 2:
      // Comando de um rele
      if (pacote[1] == PROTO_TIPO_RELE) 
      {
        return (byte >= PROTO_RELE_MIN) && (byte <= PROTO_RELE_MAX);
      }
      // Comando de todos os reles X ou S
      return (byte == PROTO_NUM_TODOS) || (byte == PROTO_NUM_STATUS);

    case 3:
      // Comando de status
      if (pacote[2] == PROTO_NUM_STATUS)
      {
        return (byte == PROTO_STATUS_REQ);
      }
      // Comando de acionamento
      return (byte == PROTO_ESTADO_ON) || (byte == PROTO_ESTADO_OFF);

    default:
      return false;
  }
}

// Executa o comando e envia a resposta
static void Protocolo_Executa(void)
{
  uint8_t resposta[PROTO_TAMANHO];

  // Toda resposta comeca com @ e repete o comando recebido
  resposta[0] = PROTO_INICIO_RSP;
  resposta[1] = pacote[1];
  resposta[2] = pacote[2];
  resposta[3] = pacote[3];

  // Comando de rele indiividual
  if (pacote[1] == PROTO_TIPO_RELE)
  {
    uint8_t numero = (uint8_t)(pacote[2] - PROTO_RELE_MIN);

    if (pacote[3] == PROTO_ESTADO_ON)
    {
      Rele_Liga(numero);
    }
    else
    {
      Rele_Desliga(numero);
    }
  }

  // Comando para todos os reles
  else if (pacote[2] == PROTO_NUM_TODOS)
  {
    if (pacote[3] == PROTO_ESTADO_ON)
    {
      Rele_LigaTodos();
    }
    else
    {
      Rele_DesligaTodos();
    }
  }
  
  // Comando de status
  else
  {
    resposta[3] = (uint8_t)(PROTO_STATUS_BASE + Rele_Status());
  }

  UART0_EnviaPacote(resposta, PROTO_TAMANHO);
}

// Adiciona um byte no pacote, se completo executa o comando
static void Protocolo_RecebeByte(uint8_t byte)
{
  if (Protocolo_ByteValido(indice, byte))
  {
    pacote[indice] = byte;
    indice++;

    // Pacote completo executa o comando e zera o indice para o proximo pacote
    if (indice == PROTO_TAMANHO)
    {
      Protocolo_Executa();
      indice = 0;
    }
    return;
  }

  // Byte fora do protocolo, verifica se e # indicando novo pacote
  if (byte == PROTO_INICIO_CMD)
  {
    pacote[0] = PROTO_INICIO_CMD;
    indice = 1;
  }
  else
  {
    indice = 0;
  }
}

// Le os bytes na serial e processa a resposta, chamado via super lopp
void Protocolo_Processa(void)
{
  int32_t recebido;

  // UART0_RecebeByte retorna -1 se nao houver byte disponivel
  while ((recebido = UART0_RecebeByte()) >= 0)
  {
    Protocolo_RecebeByte((uint8_t)recebido);
  }
}
