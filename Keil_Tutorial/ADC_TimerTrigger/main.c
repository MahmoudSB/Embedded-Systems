#include "TM4C123.h"                    // Device header

volatile int Temp=0;

int main(void)
{
	
	SYSCTL->RCGCADC |=0x01;
	SYSCTL->RCGCWTIMER |=0x01;
	
	//ADC init
	ADC0->ACTSS &=~8;
	ADC0->EMUX &=~0xF000;
	ADC0->EMUX  = 0x5000; // timer trigger conversion sequence 0
	ADC0->SSMUX3 =0;
	ADC0->SSCTL3 =0x0E;	// take mcu temperature, set flat at first sample
	ADC0->ACTSS |=8;
	
	// WTimer init
	SystemCoreClockUpdate();
	
	WTIMER0->CTL = 0;
	WTIMER0->CFG = 0x04; //32 bit
	WTIMER0->TAMR = 0x02;	// periodic down-counter mode
	WTIMER0->TAILR = SystemCoreClock; // 1hz timer
	WTIMER0->CTL |= 0x20;
	WTIMER0->CTL |= 0x01;
	
	while(1)
	{
		while((ADC0->RIS & 8)==0){}
		Temp = 147-(247*ADC0->SSFIFO3)/4096;
		ADC0->ISC = 8;	// clear complition flag
	}
}
