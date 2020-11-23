#include "TM4C123.h"                    // Device header

void T3A_RisingEdgeEvent_Init(void);
int T3A_RisingEdgeEvent_Capture(void);
uint32_t number_of_events =0;

int main()
{
	T3A_RisingEdgeEvent_Init();
	
	while(1){
		number_of_events= T3A_RisingEdgeEvent_Capture();
	}
	
}

void T3A_RisingEdgeEvent_Init(void)
{
	SYSCTL->RCGCTIMER |= 0x08;
	SYSCTL->RCGCGPIO |= 0x02;
	GPIOB->DIR &= ~0x04; // PB2 as input
	GPIOB->PDR |= 0x04;
	GPIOB->DEN |= 0x04;
	GPIOB->AFSEL |= 0x04;	//enable alternate function on PB2
	GPIOB->PCTL &= ~0xF00; // PB2 as T3CCP0 pin
	GPIOB->PCTL |= 0x700;
	
	TIMER3->CTL =0x00;
	TIMER3->CFG =0x04;	//16 bits timer
	TIMER3->TAMR = 0x13; //up-count, edge-count, capture
	TIMER3->TAMATCHR = 0xFFFF; // set count limit, compare to TAR to determine match event
	TIMER3->TAPMR = 0xFF;	// used with TAMATCHR to expand 0xFFFF with prescaler
	TIMER3->CTL |=1; 
}

int T3A_RisingEdgeEvent_Capture(void)
{
	return TIMER3->TAR;	// compare with TAMATCHR to determine match event
}
