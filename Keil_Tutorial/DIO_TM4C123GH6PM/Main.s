; SW1:PF4, SW2:PF0, LEDR:PF1, LEDG:PF2, LEDB:PF3
;1. Activate clock of the port in RCGCGPIO registers (Page 313)
;2. Set direction of pin in DIR register (Page 585)
;3. Enable pin in DEN register (Page 604)
;4. Writing/Read data : GPIODATA register (584)
; “Commit Control” on page 578

SYSCTL_RCGCGPIO_R	EQU 0x400FE608
GPIO_PORTF_DIR_R	EQU 0x40025400
GPIO_PORTF_DEN_R	EQU 0x4002551C
GPIOF_PORTF_DATA_R	EQU 0x400253FC

GPIO_PORTF_PUR_R	EQU 0x40025510
GPIO_PORTF_LOCK_R	EQU 0x40025520
GPIO_PORTF_CR_R		EQU 0x40025524
GPIO_LOCK_KEY		EQU 0x4C4F434B

RED 				EQU 0x02
BLUE				EQU 0x04
GREEN				EQU 0x08
Cycles_per_ms		EQU 5333			 ; How many cycles is program executed per milisecond?

;0x400253EF, 0x400FF612  memory to map in debug session in simulation
;0x4C4F434A, 0x4C4F434C  memory to map in debug session in simulation

			AREA	|.text|,CODE,READONLY,ALIGN=2
			THUMB
			EXPORT main

main
			BL	GPIOF_Ini
			BL	Ini_Blink		

loop		LDR	R2, =Cycles_per_ms		; Delay in miliseconds
			BL	Wait
			BL	GPIORead
			BL	Process
			BL	GPIOWrite
			B   loop
	
GPIORead	LDR R1, =GPIOF_PORTF_DATA_R
			LDR R0, [R1]
			BX	LR
	
GPIOWrite	LDR R1, =GPIOF_PORTF_DATA_R
			STR R0, [R1]
			BX	LR
	
Process		AND R0, R0, #0xF1
SW1			MOV R3, R0
			AND R3, R3, #0x11
			CMP R3, #0x01
			BNE End_SW1
RED_on		ORR R0,#RED
End_SW1

SW2			MOV R3, R0
			AND R3, R3, #0x11
			CMP R3, #0x10
			BNE End_SW2
BLUE_on		ORR R0,#BLUE
End_SW2

SW1e2		MOV R3, R0
			AND R3, R3, #0x11
			CMP R3, #0x00
			BNE End_SW1e2
GREEN_on	ORR R0,#GREEN
End_SW1e2
			BX	LR

Wait		SUBS R2, R2, #1
			BNE  Wait
			BX	LR

GPIOF_Ini	LDR R1, =SYSCTL_RCGCGPIO_R
			LDR R0, [R1]
			ORR R0, R0, #0x20
			STR R0, [R1]

			LDR R1, =GPIO_PORTF_LOCK_R
			LDR R0, =GPIO_LOCK_KEY
			STR R0, [R1]

			LDR R1, =GPIO_PORTF_CR_R
			MOV R0, #0XFF
			STR R0, [R1]

			LDR R1, =GPIO_PORTF_DIR_R
			MOV R0, #0x0E
			STR R0, [R1]

			LDR R1, =GPIO_PORTF_PUR_R
			MOV R0, #0x10
			STR R0, [R1]

			LDR R1, =GPIO_PORTF_DEN_R
			MOV R0, #0x1F
			STR R0, [R1]
			BX	LR

Ini_Blink	MOV R6, #1
R_ON		MOV R3, #0x0
Color_R		ORR R3, #RED
R_Repeat	ORR R3, #0x00000020
R_Dur		ORR R3, #0x00950000
			LDR R5, =G_ON
			BL  Blink
			
G_ON		MOV R3, #0x0
Color_G		ORR R3, #GREEN
G_Repeat	ORR R3, #0x00000020
G_Dur		ORR R3, #0x00950000
			LDR R5, =B_ON
			BL  Blink
			
B_ON		MOV R3, #0x0
Color_B		ORR R3, #BLUE
B_Repeat	ORR R3, #0x00000020
B_Dur		ORR R3, #0x00950000
			LDR R5, =repeat_b
			BL  Blink

repeat_b	SUB R6, R6, #1
			CMP R6, #0
			BNE R_ON

			B   loop
			
Blink		
color_ON	AND R0, R3, #0x0000000F
			LDR R1, =GPIOF_PORTF_DATA_R
			STR R0, [R1]
			
Delay_ON	LSR R2, R3, #16
		   ;AND R2, R2, #0x0000FFFF
			MOV R4, #Cycles_per_ms
			MUL R2, R4, R2
			BL	Wait
			
LED_OFF		MOV R0, #0x0
			LDR R1, =GPIOF_PORTF_DATA_R
			STR R0, [R1]
Delay_OFF	LSR R2, R3, #16
		   ;AND R2, R2, #0x0000FFFF
			MOV R4, #Cycles_per_ms
			MUL R2, R4, R2
			BL	Wait

repeat_a	AND R4, R3, #0x000000F0
			SUB R4, R4, #0x10
			AND R3, R3, #0xFFFFFF0F
			ORR R3, R3, R4
			CMP R4, #0x0
			BNE Blink
			
			BX  R5

			
			ALIGN
			END