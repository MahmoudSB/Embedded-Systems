#include "TM4C123.h"              		// Device header

#define PID_Sample_Freq 20e3

#define RED							1UL<<1
#define BLUE						1UL<<2
#define GREEN						1UL<<3

#define S1_ECHO					1UL<<0
#define S1_TRIGGER			1UL<<4
#define S2_ECHO					1UL<<1
#define S2_TRIGGER			1UL<<5

double PID_Sample_Time=0;
uint32_t SysClk=0;
uint32_t PID_sf=0;

void Config(void)
{
	SystemCoreClockUpdate ();
	SysClk= SystemCoreClock;
	
	if (PID_Sample_Freq>SysClk){PID_sf=SysClk;}
	else if (PID_Sample_Freq<1){PID_sf=1;}
	else {PID_sf=PID_Sample_Freq;}
	
	PID_Sample_Time = (double) 1/PID_sf;
	
	SYSCTL->RCGCGPIO  |= 1UL<<1;					// Enable port B
	
	GPIOB->DIR				&=~S1_ECHO;					// Set pin S1_ECHO as input
	GPIOB->PDR				|= S1_ECHO;					// Enable pull-down resistor for pin S1_ECHO
	GPIOB->DEN				|= S1_ECHO;					// Activate digital function for pin S1_ECHO
	GPIOB->AFSEL			|= S1_ECHO;					// Activate Alternative function for pin S1_ECHO
	GPIOB->PCTL				&=~0xFUL<<0;				// Clear pin S1_ECHO's corresponding bits in control port register
	GPIOB->PCTL				|= 0x7UL<<0;				// Set T2CCP0 as function of pin S1_ECHO in control port register
	
	GPIOB->DIR				|= S1_TRIGGER;			// Set pin S1_TRIGGER as output
	GPIOB->DEN				|= S1_TRIGGER;			// Activate digital function for pin S1_TRIGGER
	
	GPIOB->DIR				&=~S2_ECHO;					// Set pin S2_ECHO as input
	GPIOB->PDR				|= S2_ECHO;					// Enable pull-down resistor for pin S2_ECHO
	GPIOB->DEN				|= S2_ECHO;					// Activate digital function for pin S2_ECHO
	GPIOB->AFSEL			|= S2_ECHO;					// Activate Alternative function for pin S2_ECHO
	GPIOB->PCTL				&=~0xFUL<<4;				// Clear pin S2_ECHO's corresponding bits in control port register
	GPIOB->PCTL				|= 0x7UL<<4;				// Set T2CCP1 as function of pin S2_ECHO in control port register
	
	GPIOB->DIR				|= S2_TRIGGER;			// Set pin S2_TRIGGER as output
	GPIOB->DEN				|= S2_TRIGGER;			// Activate digital function for pin S2_TRIGGER
	
	
	SYSCTL->RCGCGPIO  |= 1UL<<5;					// Enable port F
	GPIOF->DIR				|= RED|BLUE|GREEN;
	GPIOF->DEN				|= RED|BLUE|GREEN;
	
	
	SYSCTL->RCGCTIMER |= 1UL<<0;					// Enable clock of TIMER0
	TIMER0->CTL				&=~1UL<<0;					// disable TIMER0
	TIMER0->CFG				 = 0x0;							// 32 bit timer
	TIMER0->TAMR			 = 0x2;							// Periodic, Count-down counter
	TIMER0->TAILR			 = SysClk/PID_sf;		// Time to count, provides given sample frequency
	TIMER0->IMR				|= 0x1;							// Enable TATORIS (Timer A Time-Out Interrupt Mask) for TIMER0
	TIMER0->ICR				 = 0x1;							// clears the TATORIS (Timer A Time-Out Interrupt Mask) bit in the TIMER0->RIS 
	TIMER0->CTL				|= 1UL<<0;					// Enable TIMER0 A (Begin counting)
	NVIC->ISER[0]			|= 1UL<<19;					// Enable IRQ19 (bit 19 of ISER[0])
	
	
	SYSCTL->RCGCTIMER |= 1UL<<2;					// Enable clock of TIMER2
	TIMER2->CTL				&=~1;								// Disable TIMER2
	TIMER2->CFG				 = 0x4;							// 16 bit timer
	
	TIMER2->TAMR			 = 0x00;						// Clean TIMER2 A mode
	TIMER2->TAMR			|= 0x03UL<<0; 			// Set TIMER2 A mode as Capture mode
	TIMER2->TAMR			|= 1UL<<2; 					// Set TIMER2 A mode as Edge-time mode
	TIMER2->TAMR			|= 1UL<<4; 					// Set TIMER2 A mode as Count-up mode
	TIMER2->CTL				|= 0x3<<2;					// set TEAVENT (Timer A Event Mode) bits to both edges
	TIMER2->CTL				|= 1UL<<0;					// Enable TIMER2 A
	
	TIMER2->TBMR			 = 0x00;						// Clean TIMER2 B mode
	TIMER2->TBMR			|= 0x03UL<<0; 			// Set TIMER2 B mode as Capture mode
	TIMER2->TBMR			|= 1UL<<2; 					// Set TIMER2 B mode as Edge-time mode
	TIMER2->TBMR			|= 1UL<<4; 					// Set TIMER2 B mode as Count-up mode
	TIMER2->CTL				|= 0x3UL<<10;				// set TBEVENT (Timer B Event Mode) bits to both edges
	TIMER2->CTL				|= 1UL<<8;					// Enable TIMER2 B
	
	
	SYSCTL->RCGCTIMER |= 1UL<<3;					// Enable clock of TIMER3
	TIMER3->CTL				&=~1UL<<0;					// disable TIMER3
	TIMER3->CFG				 = 0x4;							// 16 bit timer
	TIMER3->TAMR			 = 0x2;							// Periodic, Count-down counter
	TIMER3->TAILR			 = SysClk/1e-6;			// Time to count, 1us
	TIMER3->ICR				 = 0x1;							// clears the TATORIS (Timer A Time-Out Interrupt Mask) bit in the TIMER3->RIS 

	
}
