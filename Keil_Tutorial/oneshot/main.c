#include "TM4C123.h"                    // Device header
 
#define RED 1UL<<1

void CONFIG(void);
void timer1_oneshot(int delay);
void timer1_periodic(int delay);

int main()
{
	CONFIG();
	
	while(1)
	{
		GPIOF->DATA ^= RED;
		timer1_periodic(10000);
	}
}

void timer1_periodic(int delay)
{
	SYSCTL->RCGCTIMER |= 0x01;	//timer 0
	TIMER0->CTL =0x00;
	TIMER0->CFG =0x04;	//16 bits timer
	TIMER0->TAMR = 0x02; //periodic
	TIMER0->TAILR = 16000 -1;
	TIMER0->ICR = 0x1;
	TIMER0->CTL =0x01;
	for(int i=0; i<delay; i++)
	{
		while((TIMER0->RIS &0x01)==0){}// wait for timeout
		TIMER0->ICR = 0x1;
	} 
}


void timer1_oneshot(int delay)
{
	SYSCTL->RCGCTIMER |= 0x01;	//timer 0
	TIMER0->CTL =0x00;
	TIMER0->CFG =0x04;	//16 bits timer
	TIMER0->TAMR = 0x01; //one-shot
	TIMER0->TAILR = 16000 * delay -1;
	TIMER0->ICR = 0x1;
	TIMER0->CTL =0x01;
	while((TIMER0->RIS &0x01)==0){} // wait for timeout
}

void CONFIG(void)
{
	SYSCTL->RCGCGPIO |= 0x20;
	GPIOF->DIR |= RED;
	GPIOF->DEN |= RED;
}
