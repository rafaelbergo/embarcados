	AREA    |.text|, CODE, READONLY, ALIGN=2
    THUMB
    EXPORT  EightBitHistogram_ASM
		
;uint16_t EightBitHistogram_ASM(uint16_t width, uint16_t height, uint8_t * p_image, uint16_t * p_histogram);
; R0 = width
; R1 = height
; R2 = p_image
; R3 = p_histogram

; R4 = Limite de 64K (65546)
; R5 = image_size
; R6 = Valor 0 para limpeza
; R7 = Valor maximo do contador na limpeza (256), no calculo (image_size)
; R8 = Copia do endereço base (p_histogram) para o loop de limpeza

EightBitHistogram_ASM
	PUSH {R4-R8} ; Salva registradores R4 a R8 usados na funcao
	
	LDR R4, =65536 ; 64K
	MUL R5, R0, R1 ; image_size = width * height;
	
	; Verifica tamanho maximo de 64K
	CMP R5, R4 ; if (image_size > 65536)
	BHI retorna_erro
	
	; Limpa o histograma
	MOV R6, #0 ; Valor 0 para preencher o vetor
    MOV R7, #256 ; Valor maximo do contador
    MOV R8, R3 ; Copia o endereco inicial
	
limpeza
	STRH R6, [R8], #2 ; Salva 0 no endereco e avanca 2 bytes
    SUBS R7, R7, #1 ; Decrementa o contador e atualiza as flags
    BNE limpeza ; Compara a flag Z

	; Verifica o numero de pixels, se 0, retorna 0
	MOV R7, R5 ; R7 = image_size
    CMP R7, #0 ; Verifica o numero de pixels
    BEQ retorna_sucesso

calculo
	LDRB R4, [R2], #1 ; Le 1 byte (1 px) da memoria e aumenta o ponteiro p_image 

    ; Calcula o deslocamento da memoria explicitamente
    ADD R4, R4, R4 ; Multiplica o valor do pixel por 2
    
    LDRH R6, [R3, R4] ; Pega o valor atual do pixel no histograma
    ADDS R6, R6, #1 ; Incrementa em 1
    STRH R6, [R3, R4] ; Salva a quantidade atualizada
    
    SUBS R7, R7, #1 ; Decrementa o contador de pixels restantes
    BNE calculo ; Loop ate acabar a imagem

retorna_sucesso
    MOV R0, R5 ; Retorna o image_size
    POP {R4-R8} ; Restaura registradores
	BX	LR ; Retorna ao main.c
	
retorna_erro
	MOV R0, #0 ; Retorna 0
	POP {R4-R8} ; Restaura registradores
	BX	LR ; Retorna ao main.c

	ALIGN
    END