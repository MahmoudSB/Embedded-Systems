;1. Activate clock of the port in RCGCGPIO registers (Page 340)
;2. Set direction of pin in DIR register (Page 663)
;4. Enable pin in DEN register (Page 682)
;   Writing/Read data : GPIODATA register (654)
SYSCTL_RCGCGPIO_R EQU 0x400FE608
GPIO_PORTF_DIR_R  EQU 0x40025400
GPIO_PORTF_DEN_R  EQU 0x4002551C
GPIO_PORTF_DATA_R EQU 0x400253FC
	



				AREA	|.text|,CODE,READONLY,ALIGN=2
				THUMB
				EXPORT Main
					
Main
		BL		GPIOF_Init
		
loop    BL		LIGHT_ON
        B		loop

		
GPIOF_Init		
		LDR R1,=SYSCTL_RCGCGPIO_R
		LDR R0,[R1]
		ORR R0,R0,#0x20
		STR R0,[R1]
		
		LDR R1,=GPIO_PORTF_DIR_R
		MOV R0,#0x02  ;0B 0000 0010
		STR R0,[R1]
		
		LDR R1,=GPIO_PORTF_DEN_R
		MOV R0,#0x02
		STR R0,[R1]
		BX	LR
		
		
LIGHT_ON
       LDR R1,= GPIO_PORTF_DATA_R
	   MOV R0,#0x02
	   STR R0,[R1]
	   BX LR
	   
	   ALIGN
	   END
      
