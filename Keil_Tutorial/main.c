#include "TM4C123.h"                    // Device header


int main()
{
	SYSCTL->RCGCGPIO |=0x20;
	GPIOF->DIR |= 0x0E;
	GPIOF->DEN |= 0x0E;
	
	// configure systick
	__disable_irq(); // disable global intrupts
	SysTick->LOAD = 1600000-1;
	SysTick->CTRL = 7; // enable, use intrupt, use system clock
	__enable_irq();
	
	while(1){}
}

void SysTick_Handler(void)
{
	GPIOF->DATA ^= 0x0E;
}
