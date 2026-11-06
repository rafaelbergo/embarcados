#ifndef PROTOCOLO_H
#define PROTOCOLO_H

#include <stdint.h>

#define PROTO_TAMANHO 4
#define PROTO_INICIO_CMD '#'
#define PROTO_INICIO_RSP '@'
#define PROTO_TIPO_RELE 'R'
#define PROTO_TIPO_TODOS 'T'
#define PROTO_NUM_TODOS 'X'
#define PROTO_NUM_STATUS 'S'
#define PROTO_STATUS_REQ 'T'
#define PROTO_ESTADO_ON '1'
#define PROTO_ESTADO_OFF '0'
#define PROTO_RELE_MIN '0'
#define PROTO_RELE_MAX '3'
#define PROTO_STATUS_BASE 0x40

void Protocolo_Init(void);
void Protocolo_Processa(void);

#endif
