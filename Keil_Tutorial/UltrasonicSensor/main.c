#include "TM4C123.h"                    // Device header

#define ECHO 		1UL<<6
#define TRIGGER 1UL<<4
#define BLUE 		1UL<<2

uint32_t Falling_Edge, Rising_Edge, Distance;
const double _16MHZ_1clock = 62.5e-9;
const uint32_t Multiplier  = 5882;

void Timer0_Init(void);
void delay_us(int t);
void Ports_Init(void);
uint32_t Measure_Dist_cm(void);

int main()
{
	Ports_Init();
	Timer0_Init();
	
	while(1)
	{
		Distance = Measure_Dist_cm();
		if(Measure_Dist_cm()>100){GPIOF->DATA |= BLUE;} else{GPIOF->DATA &=~ BLUE;}
	}
}

void Timer0_Init(void)
{
	
	
	SYSCTL->RCGCGPIO  |= 1UL<<1;
	GPIOB->DIR				&=~ECHO;
	GPIOB->PDR				|= ECHO;
	GPIOB->DEN				|= ECHO;
	GPIOB->AFSEL			|= ECHO;
	GPIOB->PCTL				&=~0x0F000000;
	GPIOB->PCTL				|= 0x07000000;
	
	SYSCTL->RCGCTIMER |= 1UL<<0;
	TIMER0->CTL				&=~1;
	TIMER0->CFG				 = 0x4;
	TIMER0->TAMR			 = 0x17; // capture mode, edge-time mode, up counter 
	TIMER0->CTL				|= 0x0C;	// sets TEAVENT bit to both edges
	TIMER0->CTL				|= 1;
}

void delay_us(int t)
{
	SYSCTL->RCGCTIMER |= 1UL<<1;
	TIMER1->CTL				&=~1;
	TIMER1->CFG				 = 0x4;
	TIMER1->TAMR			 = 0x02;
	TIMER1->TAILR			 = 16-1;
	TIMER1->ICR			 	 = 0x1;
	TIMER1->CTL				|= 1;
	
	for(int i=0; i<t; i++){
		while((TIMER1->RIS & 1UL<<0) == 0){}
		TIMER1->ICR			 	 = 0x1;
	}
}

void Ports_Init(void)
{
	SYSCTL->RCGCGPIO  |= 1UL<<0;
	SYSCTL->RCGCGPIO  |= 1UL<<5;
	GPIOA->DIR				|= TRIGGER;
	GPIOF->DIR				|= BLUE;
	GPIOA->DEN				|= TRIGGER;
	GPIOF->DEN				|= BLUE;
}

uint32_t Measure_Dist_cm(void)
{
	GPIOA->DATA				&=~TRIGGER;
	delay_us(12);
	GPIOA->DATA				|= TRIGGER;
	delay_us(12);
	GPIOA->DATA				&=~TRIGGER;
	
	TIMER0->ICR			 	 = 0x4;	// clear timer capture flag by writing 1 to CAECINT bit (bit 2)
	while((TIMER0->RIS & 1UL<<2) == 0){} // wait till captured, by checking CAECINT bit (bit 2)
	Rising_Edge = TIMER0->TAR;
		
	TIMER0->ICR			 	 = 0x4;	// clear timer capture flag by writing 1 to CAECINT bit (bit 2)
	while((TIMER0->RIS & 1UL<<2) == 0){} // wait till captured, by checking CAECINT bit (bit 2)
	Falling_Edge = TIMER0->TAR;
		
	return (double)Falling_Edge-Rising_Edge * (double)Multiplier * _16MHZ_1clock;
}
