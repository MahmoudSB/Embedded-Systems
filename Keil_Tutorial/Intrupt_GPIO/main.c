#include "TM4C123.h"                    // Device header

int main()
{
	SYSCTL->RCGCGPIO	|= 0x20;
	GPIOF->LOCK				 = 0x4C4F434B;
	GPIOF->CR 				 = 0x01;
	GPIOF->LOCK				 = 0;
	GPIOF->DIR				&=~0x11;
	GPIOF->DIR				|= 0x0E;
	GPIOF->DEN				|= 0x1F;
	GPIOF->PUR				|= 0x11;
	
	
	__disable_irq();
	GPIOF->IS					&=~0x11;	// pf0 and pf4 edge sensitve
	GPIOF->IBE				&=~0x11;	// pf0 and pf4 intrupt controlled by GPIOFIEV
	GPIOF->IEV				&=~0x11;	// pf0 and pf4 falling edge detection
	GPIOF->ICR				|= 0x11;	// clear any prior intrupt
	GPIOF->IM				  |= 0x11;	// unmask intrupt, intrupt sent to the interrupt controller.
	
	NVIC->IP[30] 			 = 3<<5;	// setting intrupt to priority 3
	NVIC->ISER[0] 			 = 0x40000000;	//enable IRQ30
	__enable_irq();
	
	while(1){
		
	}
}

void GPIOF_Handler(void)
{
	volatile int readback;
	
	GPIOF->DATA ^= 0x02;
	
	GPIOF->ICR				|= 0x11;
	readback = GPIOF->ICR;
}
