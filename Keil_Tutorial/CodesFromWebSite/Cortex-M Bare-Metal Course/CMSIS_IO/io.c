#include "TM4C123.h"                    // Device header
#include <stdint.h>
#include "delay.h"
#include "io.h"

void LED_ON(uint32_t LED){
  GPIOF->DATA =LED;
	delay(2000000);
	GPIOF->DATA &=~LED;
	}

uint32_t SW_INPUT(){
return (GPIOF->DATA &0x11);   //0B 0001 0001 
}


void PortF_INIT(){
	SYSCTL->RCGCGPIO |=(1U<<5);
	GPIOF->LOCK = KEY;
	GPIOF->CR = 0xFF;
	GPIOF->DIR |=(BLUE | GREEN |RED);
  GPIOF->PUR |=(SW1 |SW2);
  GPIOF->DEN |= (BLUE |GREEN |RED |SW1 |SW2);	
}