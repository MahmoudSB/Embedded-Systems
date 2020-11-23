
; SW1:PF4, SW2:PF0, LEDR:PF1, LEDG:PF2, LEDB:PF3
;1. Activate clock of the port in RCGCGPIO registers (Page 313)
;2. Set direction of pin in DIR register (Page 585)
;3. Enable pin in DEN register (Page 604)
;4. Writing/Read data : GPIODATA register (584)
; “Commit Control” on page 578

SYSCTL_RCGCGPIO_R	EQU 0x400FE608
GPIO_PORTF_DIR_R	EQU 0x40025400
GPIO_PORTF_DEN_R	EQU 0x4002551C
GPIOF_PORTF_DATA_R	EQU 0x400253fc

;0x40025000, 0x400FF610  memory to map in debug mode

				AREA	|.text|,CODE,READONLY,ALIGN=2
				THUMB
				EXPORT main
					
main
		BL		GPIOF_Init
		
loop	BL		LIGHT_ON
		B		loop
		
GPIOF_Init
		LDR R1,=SYSCTL_RCGCGPIO_R
		LDR R0,[R1]
		ORR R0,R0, #0x20 ; 0b 0000 0010 : GPIO F clock enabled
		STR R0,[R1]
		
		LDR R1,=GPIO_PORTF_DIR_R
		MOV R0,#0x02 ; 0b 0000 0010 : GPIO F, pin 2(LEDR): is an output. the rest are input
		STR R0,[R1]
		
		LDR R1,=GPIO_PORTF_DEN_R
		MOV R0,#0X02 ; 0b 0000 0010 : GPIO F, pin 2(LEDR): digital functions enabbled. the rest are disabled
		STR R0,[R1]
		BX  LR
		
LIGHT_ON
		LDR R1,=GPIOF_PORTF_DATA_R
		MOV R0,#0xF
		STR R0,[R1]
		BX  LR
		
		ALIGN
		END