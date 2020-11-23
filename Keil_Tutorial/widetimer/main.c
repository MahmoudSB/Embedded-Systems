#include "TM4C123.h"                    // Device header

#define BLUE	1UL<<2
#define T0		1UL<<0
#define T1		1UL<<1
#define T2		1UL<<2
#define T3		1UL<<3

uint32_t ms=0;

void GPIO_Init(void);
void Wide_Timer_32(int delay);
void Wide_Timer_64(int delay);
void Timer_16(int delay);
void Timer_32(int delay);

int main(void)
{
	GPIO_Init();
	while(1){
		SystemCoreClockUpdate();
		ms = SystemCoreClock/1000;
		Wide_Timer_64(15);
		GPIOF->DATA ^= BLUE;
	}
}

void GPIO_Init(void)
{
	SYSCTL->RCGCGPIO |= 1UL<<5;
	GPIOF->DIR			 |=	BLUE;
	GPIOF->DEN			 |= BLUE;
}

void Wide_Timer_32(int delay)
{
	SYSCTL->RCGCWTIMER |= T0;
	WTIMER0->CTL			 &=~1UL<<0;
	WTIMER0->CFG				= 0x4;
	WTIMER0->TAMR				= 0x2;
	WTIMER0->TAILR			= ms;
	WTIMER0->ICR				= 1;
	WTIMER0->CTL			 |= 1UL<<0;
	
	for(int i=0; i<delay; i++){
		while((WTIMER0->RIS & 0x01) ==0){}
		WTIMER0->ICR = 1;
	}
}
void Wide_Timer_64(int delay)
{
	SYSCTL->RCGCWTIMER |= T1;
	WTIMER1->CTL			 &=~1UL<<0;
	WTIMER1->CFG				= 0x0;
	WTIMER1->TAMR				= 0x2;
	WTIMER1->TAILR			= ms;
	WTIMER1->ICR				= 1;
	WTIMER1->CTL			 |= 1UL<<0;
	
	for(int i=0; i<delay; i++){
	while((WTIMER1->RIS & 0x01) ==0){}
	WTIMER1->ICR = 1;
	}
}

void Timer_16(int delay)
{
	SYSCTL->RCGCTIMER |= T2;
	TIMER2->CTL			  &=~1UL<<0;
	TIMER2->CFG				 = 0x4;
	TIMER2->TAMR			 = 0x2;
	TIMER2->TAILR			 = ms;
	TIMER2->ICR				= 1;
	TIMER2->CTL			  |= 1UL<<0;
	
	for(int i=0; i<delay; i++){
	while((TIMER2->RIS & 0x01) ==0){}
	TIMER2->ICR = 1;
	}
}

void Timer_32(int delay)
{
	SYSCTL->RCGCTIMER |= T3;
	TIMER3->CTL			  &=~1UL<<0;
	TIMER3->CFG				 = 0x0;
	TIMER3->TAMR			 = 0x2;
	TIMER3->TAILR			 = ms;
	TIMER3->ICR				= 1;
	TIMER3->CTL			  |= 1UL<<0;
	
	for(int i=0; i<delay; i++){
	while((TIMER3->RIS & 0x01) ==0){}
	TIMER3->ICR = 1;
	}
}
