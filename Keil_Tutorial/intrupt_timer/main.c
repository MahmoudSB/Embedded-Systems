#include "TM4C123.h"                    // Device header

#define RED		1UL<<1
#define BLUE	1UL<<2
#define GREEN	1UL<<3

void T1A_1Hz_Init(void);
void T2A_10Hz_Init(void);

int main(void)
{
	SYSCTL->RCGCGPIO	|= 1UL<<5;
	GPIOF->DIR = 0x0E;
	GPIOF->DEN = 0x0E;
	
	T1A_1Hz_Init();
	T2A_10Hz_Init();
	__enable_irq();
	
	while(1){
		GPIOF->DATA ^= BLUE;
	}
}

void T1A_1Hz_Init(void)
{
	SYSCTL->RCGCTIMER |= 1UL<<1;
	TIMER1->CTL				&=~1UL<<0;
	TIMER1->CFG				 = 0x4;
	TIMER1->TAMR			 = 0x2;
	TIMER1->TAPR			 = 250;	// 16 MHz /250= 64000 Hz
	TIMER1->TAILR			 = 64000;	// 64000 Hz /64000= 1 Hz
	TIMER1->ICR				 = 0x1;
	TIMER1->IMR				|= 0x1;
	TIMER1->CTL				|= 1UL<<0;
	NVIC->ISER[0]			|=0x200000;	//enable IRQ21 (D21 of ISER[0])
}

void T2A_10Hz_Init(void)
{
	SYSCTL->RCGCTIMER |= 1UL<<2;
	TIMER2->CTL				&=~1UL<<0;
	TIMER2->CFG				 = 0x4;	//16 bit
	TIMER2->TAMR			 = 0x2;	// periodic, down counter
	TIMER2->TAPR			 = 250;	// 16 MHz /250= 64000 Hz
	TIMER2->TAILR			 = 6400;	//64000 Hz /6400= 10 Hz
	TIMER2->ICR				 = 0x1;
	TIMER2->IMR				|= 0x1;
	TIMER2->CTL				|= 1UL<<0;
	NVIC->ISER[0]			|=0x800000;	//enable IRQ23 (D23 of ISER[0])
}

void TIMER1A_Handler(void)
{
	volatile int clear;
	if (TIMER1->MIS & 0x1){
		GPIOF->DATA ^= RED;
		TIMER1->ICR	= 0x01;
	}else{
		TIMER1->ICR	= TIMER2->MIS;
	}
	clear=TIMER1->ICR; // a read to force clearing of intrupt flag
}

void TIMER2A_Handler(void)
{
	volatile int clear;
	if (TIMER2->MIS & 0x1){
		GPIOF->DATA ^= GREEN;
		TIMER2->ICR	= 0x01;
	}else{
		TIMER2->ICR	= TIMER2->MIS;
	}
	clear=TIMER2->ICR;
}
