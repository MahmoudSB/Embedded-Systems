#include "TM4C123.h"                    // Device header

#define GREEN 1UL<<3
#define SW1		1UL<<4
#define SW1_Value (((~GPIOF->DATA) & SW1)>>4)
#define clear(target, bit) (target & ~(1UL<<bit))
#define bit_toggle(target, bit, toggle_source) (target = clear(target, bit) | toggle_source)
#define ms(n)	n*(16000-1)
#define s(n)	n*(16000000-1)

int main()
	
{ 
	SystemCoreClockUpdate ();
	
	SYSCTL->RCGCGPIO |= 0x20;
	GPIOF->DIR			 |= GREEN;
	GPIOF->PUR			 |= SW1;
	GPIOF->DEN			 |= GREEN	|SW1;
	
	SysTick->LOAD			= 1*SystemCoreClock;
	SysTick->CTRL			|= 1UL<<2;	// use system clock
//	SysTick->CTRL			|= 1UL<<1;	// enable intrupt
	
	
	while(1)
	{
		
		bit_toggle(SysTick->CTRL, 0, SW1_Value);
		
		if (SysTick->CTRL & 1UL<<16)
		{
			GPIOF->DATA ^= GREEN;
		}
		if (!SW1_Value)
		{
			GPIOF->DATA &= ~GREEN;
	
		}
	}
}
