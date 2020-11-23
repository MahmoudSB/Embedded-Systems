#include <TM4C1230H6PM.h>
#define RED (1U<<1)
#define BLUE (1U<<2)
#define GREEN (1U<<3)
int main()
{
	SYSCTL->RCC2 |= (1U<<5);
	//SYSCTL->GPIOHSCTL |=(1U<<5);
	GPIOF->AMSEL =0x00;
	//GPIOF->AFSEL=0x00;
//	GPIOF->PCTL=0x00;

	//GPIOF->CR =(1U<<3);
	GPIOF->DIR =0xFF;
	GPIOF->DEN =0xFF;
	
	
	
	while(1)
	{
		GPIOF->DATA =GREEN;
	}
}
