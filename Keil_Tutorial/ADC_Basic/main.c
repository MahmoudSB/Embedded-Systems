#include "TM4C123.h"                    // Device header

int result=0;

void Init(void);
	

int main()
{
	Init();
		while(1)
	{
		ADC0->PSSI		 |= 8;	// start a convertion at SS3
		while((ADC0->RIS &8) == 0){}	//wait for convertion complete
		result = ADC0->SSFIFO3;
		ADC0->ISC = 8; // clear completion flag
	}
}

void Init(void)
{
	SYSCTL->RCGCGPIO |= 1UL<<4;	//enable clock for Port E
	SYSCTL->RCGCADC	 |= 1UL<<0;	//enable clock for ADC module 0
	
	// PE3 init
	GPIOE->AFSEL 		 |= 8;		//enable alternate function
	GPIOE->DEN			 &=~8;		//disable digital function
	GPIOE->AMSEL 		 |= 8;		//enable analog function
	
	// ADC enable
	ADC0->ACTSS			 &=~8;		// disable Sample Sequenser 3 (SS3)
	ADC0->EMUX			 &=~0xF000;	// softeawe trigger convertion
	ADC0->SSMUX3			= 0;			// get input from channel 0
	ADC0->SSCTL3		 |= 6;			// take one sample at a time, set flag at first sample
	ADC0->ACTSS			 |= 8;		// enable Sample Sequenser 3 (SS3)
	

	
}
