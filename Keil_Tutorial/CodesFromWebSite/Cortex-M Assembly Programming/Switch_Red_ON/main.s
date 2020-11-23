SYSCTL_RCGCGPIO_R  EQU   0x400FE608
GPIO_PORTF_DATA_R  EQU 0x400253FC
GPIO_PORTF_DIR_R   EQU 0x40025400
GPIO_PORTF_DEN_R   EQU 0x4002551C

GPIO_PORTF_PUR_R   EQU 0x40025510
GPIO_PORTF_LOCK_R  EQU 0x40025520
GPIO_PORTF_CR_R    EQU 0x40025524
GPIO_LOCK_KEY      EQU 0x4C4F434B 
	
RED       EQU 0x02
SEC_DIV_FIVE     EQU 1066666    ;1second divided by 5


        AREA    |.text|, CODE, READONLY, ALIGN=2
        THUMB
        EXPORT  Main
		
Main
    BL  GPIOF_init                  ; initialize input and output pins of Port F
loop
    LDR R0, = SEC_DIV_FIVE             ; R0 = FIFTHSEC (delay 0.2 second)
    BL  delay                       ; delay at least (3*R0) cycles
    BL  Input                 ; read all of the switches on Port F
    CMP R0, #0x01                   ; R0 == 0x01?
    BEQ SWITCH_ON                  ; if so, switch 1 pressed
    BL  Output                ; turn all of the LEDs on
    B   loop

GPIOF_init
    LDR R1, =SYSCTL_RCGCGPIO_R      ; 1) activate clock for Port F
    LDR R0, [R1]                 
    ORR R0, R0, #0x20               ; set bit 5 to turn on clock
    STR R0, [R1]                  
                              
    LDR R1, =GPIO_PORTF_LOCK_R      ; 2) unlock the lock register
    LDR R0, =0x4C4F434B             ; unlock GPIO Port F Commit Register
    STR R0, [R1]                    
    LDR R1, =GPIO_PORTF_CR_R        ; enable commit for Port F
    MOV R0, #0xFF                   ; 1 means allow access
    STR R0, [R1]                    
    LDR R1, =GPIO_PORTF_DIR_R       ; 5) set direction register
    MOV R0,#0x0E                    ; PF0 and PF7-4 input, PF3-1 output
    STR R0, [R1]                               
    LDR R1, =GPIO_PORTF_PUR_R       ; pull-up resistors for PF4,PF0
    MOV R0, #0x11                   ; enable weak pull-up on PF0 and PF4
    STR R0, [R1]              
    LDR R1, =GPIO_PORTF_DEN_R       ; 7) enable Port F digital port
    MOV R0, #0xFF                   ; 1 means enable digital I/O
    STR R0, [R1]                   
    BX  LR      
SWITCH_ON
    MOV R0, #RED                   ; R0 = BLUE (blue LED on)
    BL  Output                ; turn the blue LED on
    B   loop
delay
    SUBS R0, R0, #1                 
    BNE delay                       
    BX  LR                          

Input
    LDR R1, =GPIO_PORTF_DATA_R 
    LDR R0, [R1]               
    AND R0,R0,#0x11            
    BX  LR                     
Output
    LDR R1, =GPIO_PORTF_DATA_R 
    STR R0, [R1]               
    BX  LR                    

    ALIGN                          
    END                          
