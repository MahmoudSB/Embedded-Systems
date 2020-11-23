			AREA	|.text|, CODE, READONLY, ALIGN=2
			THUMB
			EXPORT SFC
			IMPORT GPIO_READ
			IMPORT main
			IMPORT GPIO_WRITE
SFC
			LDR R0, =GPIO_READ
            BLX R0
			
			LDR R0, =main
            BLX R0
			
			LDR R0, =GPIO_WRITE
            BLX R0
			
			B   SFC
			
			ALIGN
			END