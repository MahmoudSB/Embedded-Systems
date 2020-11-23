		AREA	DATA, ALIGN=2
		IMPORT num
		IMPORT adder
	
		AREA	|.text|, CODE, READONLY, ALIGN=2
		THUMB
		EXPORT main
		
main
	LDR R1, =num
	MOV R0, #100
	STR R0, [R1]
	
	BL adder
	
	ALIGN
	END