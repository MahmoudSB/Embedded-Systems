#include "TM4C123.h"                    // Device header

#define RED (1U<<1)
#define BLUE (1U<<2)
#define GREEN (1U<<3)

int main()
{  
	int volatile delay;
	//SYSCTRL_RCGC_R= 0x20U;
	SYSCTL->RCGCGPIO = 0x20U;
	GPIOF->DIR = 0xEU;
	//GPIO_PORTF_DIR_R  =0xEU;
	GPIOF->DEN = 0xEU;
 
	GPIOF->DATA |= GREEN;
	while(1)
	{
		delay = 0;
		while(delay <1000000){
			GPIOF->DATA =GPIOF->DATA|BLUE;
			delay++;
	}
		delay =0;
	 while(delay<1000000){
	 GPIOF->DATA = GPIOF ->DATA & (~BLUE);
		delay++;
	 }
}

}
