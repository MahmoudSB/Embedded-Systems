#include "TM4C123.h"                    // Device header

const uint32_t Multiplier  = 5882;

typedef struct{
	uint8_t  Trigger;
	uint8_t  Echo;
	uint32_t RisingEdge;
	uint32_t FallingEdge;
	uint32_t Distance;
}Sensor;


void delay_us(int us);

void Dist_cm (Sensor *S)
{
	GPIOB->DATA &=~S->Trigger;
	delay_us(12);
	GPIOB->DATA |= S->Trigger;
	delay_us(12);
	GPIOB->DATA &=~S->Trigger;
	
	TIMER3->ICR    = 1UL<<2;					 		// Timer A Capture Mode Event Interrupt Clear
	while(!(TIMER3->RIS & 1UL<<2)){}			// Wait till captured, TIMER3->RIS (bit 2):Timer A Capture Mode Event Raw Interrupt
	S->RisingEdge  = TIMER0->TAR;					// TIMER0->TAR: Returns the current value of the GPTM Timer A Count Register
	TIMER3->ICR    = 1UL<<2;					 		// Timer A Capture Mode Event Interrupt Clear
	while(!(TIMER3->RIS & 1UL<<2)){}			// Wait till captured, TIMER3->RIS (bit 2):Timer A Capture Mode Event Raw Interrupt
	S->FallingEdge = TIMER0->TAR;					// TIMER0->TAR: Returns the current value of the GPTM Timer A Count Register
	
	S->Distance    = (S->FallingEdge - S->RisingEdge) * Multiplier * (1/SystemCoreClock);
}


void delay_us(int us)
{
	TIMER3->ICR	 = 0x1;										// disable TIMER3
	TIMER3->CTL	|= 1UL<<0;								// Enable TIMER3 A (Begin counting)
	for(int i=0; i<us; i++)
		while(!(TIMER3->RIS & 1UL<<0)){}
	TIMER3->ICR	 = 0x1;
	TIMER3->CTL	&=~1UL<<0;								// disable TIMER3
}
