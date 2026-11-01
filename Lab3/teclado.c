// teclado.c
// Desenvolvido para a placa EK-TM4C1294XL + Shield LCD(1602b) + Teclado (4x4)
// Portabilidade para C TivaWare do teclado.c original, que lia e escrevia
// diretamente nos registradores das portas (tm4c1294ncpdt.h) atraves do gpio.c
// Controla o teclado matricial 4 linhas x 4 colunas
// Projeto e Esquematico do Shield: http://www.elf52.daeln.com.br
// Prof. DaLuz
// Prof. Guilherme Peron
// Prof. Marcos P.
// 16/07/2023

#include <stdint.h>
#include "teclado.h"
#include "gpio.h"

// -------------------------------------------------------------------------------
// Funcao AtivaColuna
// Habilita a coluna respectiva
// Parametro de entrada: Numero da Coluna de 1 a 4 a ser habilitada
// Parametro de saida: nao tem
void AtivaColuna(uint8_t coluna)
{
    switch(coluna)
	{
		case 1:
			PortM_Output2(0xE0);    //Zerar PM4
			break;
		case 2:
			PortM_Output2(0xD0);    //Zerar PM5
			break;
		case 3:
			PortM_Output2(0xB0);    //Zerar PM6
			break;
		case 4:
			PortM_Output2(0x70);    //Zerar PM7
			break;
		default:
			PortM_Output2(0xF0);
			break;
	}
}

// -------------------------------------------------------------------------------
// Funcao LeLinha
// Retorna qual linha foi pressionada
// Parametro de entrada: nao tem
// Parametro de saida: retorna a linha que esta ativa
uint8_t LeLinha(void)
{
	uint32_t portL_input;
	portL_input = PortL_Input();
	switch(portL_input)
	{
		case 0x0E:  //Port L0
			return 1;
		case 0x0D:  //Port L1
			return 2;
		case 0x0B:  //Port L2
			return 3;
		case 0x07:  //Port L3
			return 4;
		default:
			return 0;
	}
}

// -------------------------------------------------------------------------------
// Funcao VarreTeclado
// Varre o teclado habilitando cada coluna para verificar qual linha esta pressionada
// Parametro de entrada: nao tem
// Parametro de saida: retorna o caracter correspondente a tecla pressionada
uint8_t VarreTeclado(void)
{
	uint8_t linha, caracter = 0;

	//Varre a primeira coluna
	AtivaColuna(1);
	linha = LeLinha();
	if (linha)
	{
		switch (linha)
		{
			case 1:
				caracter = '7';
				break;
			case 2:
				caracter = '4';
				break;
			case 3:
				caracter = '1';
				break;
			case 4:
				caracter = '#';
				break;
		}
	}

	//Varre a segunda coluna
	AtivaColuna(2);
	linha = LeLinha();
	if (linha && caracter == 0)
	{
		switch (linha)
		{
			case 1:
				caracter = '8';
				break;
			case 2:
				caracter = '5';
				break;
			case 3:
				caracter = '2';
				break;
			case 4:
				caracter = '0';
				break;
		}
	}

	//Varre a terceira coluna
	AtivaColuna(3);
	linha = LeLinha();
	if (linha && caracter == 0)
	{
		switch (linha)
		{
			case 1:
				caracter = '9';
				break;
			case 2:
				caracter = '6';
				break;
			case 3:
				caracter = '3';
				break;
			case 4:
				caracter = '*';
				break;
		}
	}

	//Varre a quarta coluna
	AtivaColuna(4);
	linha = LeLinha();
	if (linha && caracter == 0)
	{
		switch (linha)
		{
			case 1:
				caracter = 'A';
				break;
			case 2:
				caracter = 'B';
				break;
			case 3:
				caracter = 'C';
				break;
			case 4:
				caracter = 'D';
				break;
		}
	}
	return(caracter);
}
