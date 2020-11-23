#include <TM4C123GH6PM.h>                   // Device header

#define BLUE (1U<<2)
#define GREEN (1U<<3)
#define RED   (1UL<<1)

#define SW1 (1U<<4)
#define SW2 (1U<<0)

#define KEY1 0x10
#define KEY2 0x01

#define KEY 0x4C4F434B

typedef volatile unsigned char  boolean;



int main()
{
	SYSCTL->RCGCGPIO |= (1U<<5);
	GPIOF->LOCK = KEY;
	GPIOF->CR =0xFF;
  GPIOF->DIR |=(BLUE|GREEN);
	GPIOF->PUR |=(SW1 |SW2);
	GPIOF->DEN |=(BLUE | GREEN |SW1 |SW2);
	
	boolean bit = 0b0000;
	unsigned char SW1_Status = 0b0000;
	while(1){
		SW1_Status = (unsigned char)((~GPIOF->DATA & SW1)>>4);
		bit = (bit & 0b1110) | (SW1_Status & 0b0001);
		
		switch(bit & 0b1001){
			case 0b1001:
				bit &= 0b1001;
				break;
			case 0b0000:
				bit &= 0b1001;
				break;
			case 0b0001:
				bit = (bit & 0b1001) | 0b0010;
				break;
			case 0b1000:
				bit = (bit & 0b1001) | 0b0100;
				break;
		}
		bit = (bit & 0b0111) | (bit<<3 & 0b1000);
		
		int rise_bit =(bit&0b0010)>>1;
		
		if ( rise_bit == 1)
			{
				
				GPIOF->DATA = BLUE;
			} else {GPIOF->DATA &= ~BLUE;}

	}
}
