    AREA    |.text|, CODE, READONLY, ALIGN=2
    THUMB
    EXPORT  EightBitHistogram_ASM
		
;uint16_t EightBitHistogram_ASM(uint16_t width, uint16_t height, uint8_t * p_image, uint16_t * p_histogram);
; R0 = width
; R1 = height
; R2 = p_image
; R3 = p_histogram
; R4 = 65546 (64K)
; R5 = image_size
; R6 = 

; R10 = copia do endereco para loop de limpeza
; R11 = valor maximo do contador
; R12 = contador limpar histograma

EightBitHistogram_ASM
	LDR R4, =65536 ; 64K
	MUL R5, R0, R1 ; uint32_t image_size = (uint32_t)width * height;
	
	; Verifica tamanho maximo de 64K
	CMP R5, R4 ; if (image_size > 65536)
	BHI retorna
	
	; Limpa o histograma
	MOV	R12, #0 ;
    MOV	R11, #256 ;valor maximo do contador
    MOV	R10, R3 ; salva o endereco inicial

limpeza
    STRH R12, [R10], #2 ; salva 0 no endereco e decrementa em 2 bytes
    SUBS R11, R11, #1 ; decrementa o contador e atualiza as flags
    BNE limpeza ; compara a flag Z


	; Calcula o histograma



retorna
	MOV R0, #0
	BX	LR ; return 0


	ALIGN
    END