#include "TM4C123.h"                    // Device header
#include "delay.h"

#define BLUE (1U<<2)
#define GREEN (1U<<3)
#define RED   (1U<<1)



#define SW1 (1U<<4)
#define SW2 (1U<<0)


#define KEY1 0x10
#define KEY2 0x01


#define FKEY 0x4C4F434B


void LED_ON(uint32_t LED);
void LED_OFF(uint32_t LED);
uint32_t SW_INPUT();
int main()
	
{
	uint32_t sw_state;
	SYSCTL->RCGCGPIO |= (1U<<5);
	GPIOF->LOCK = FKEY;
	GPIOF->CR =0xFF;
  GPIOF->DIR |=(BLUE|GREEN);
	GPIOF->PUR |=(SW1 |SW2);
	GPIOF->DEN |=(BLUE | GREEN |SW1 |SW2);
	
	
	
	
	while(1){
		sw_state =SW_INPUT();
		switch(sw_state){
		 
		 case KEY1:	
		 LED_ON(GREEN);
		 break;

		 case KEY2:
		 LED_ON(BLUE);
		 break;
	}
}
	}

void LED_ON (uint32_t LED){
 GPIOF->DATA =LED;
	delay(2000000);
 GPIOF->DATA &=~LED;
}

void LED_OFF (uint32_t LED){
 GPIOF->DATA &=~LED;
	delay(1000000);
}
uint32_t SW_INPUT(){
 return (GPIOF->DATA&0x11);
}