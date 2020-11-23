#include <TM4C123GH6PM.h>
#include <string.h>
#include <stdio.h>
#include "Globals.h"
#include "TM4C123.h"                    // Device header

/*------------------------------------------------------/
  Variables --------------------------------------------/
/------------------------------------------------------*/
_Bool green_on = False;
_Bool red_on = False;
_Bool blue_on = False;
_Bool FirstCycle = True;
bit SW1;
bit SW2;
bit SW1e2;
Timer T1;
Timer T2;
int GPIOF_DATA = 0UL;

volatile int flags = FLAG_NONE;

/*------------------------------------------------------/
  main() -----------------------------------------------/
/------------------------------------------------------*/
int main()
{
	FirstCycle = True;
	green_on = False;
	red_on = False;
	blue_on = False;
	GPIOF_DATA = 0UL;
	PauseAndBlink("RB", 10000, 1000000);
	PauseAndBlink("G" , 7000000, 1000);
	T1.time= 100000;
	T2.time= 200000;
	
	while(1){
		GPIOF_DATA = GPIOA_Read();
		SW1.IsOn = (~GPIOF_DATA & 1UL<<4)>>4; 	update_bit(&SW1, 	 FirstCycle);
		SW2.IsOn = (~GPIOF_DATA & 1UL<<0)>>0; 	update_bit(&SW1, 	 FirstCycle);
		SW1e2.IsOn = (GPIOF_DATA & 0x11UL)==0;	update_bit(&SW1e2, FirstCycle);
		T1.En.IsOn = SW1.IsOn && !SW2.IsOn;			update_bit(&T1.En, FirstCycle);	TON(&T1, FirstCycle);
		T2.En.IsOn=T1.Q;												update_bit(&T2.En, FirstCycle); TOF(&T2, FirstCycle);
		
		blue_on		= T2.Q;
		TIMER0->CTL = SW2.IsOn;
		green_on ^= SW1e2.R_Trig;
		if (flags == FLAG_Toggle_LED){flags = FLAG_NONE; red_on ^= 1;}
		
		GPIOF_DATA = 0UL;
		if (red_on)		{GPIOF_DATA |= Red;}
		if (blue_on)	{GPIOF_DATA |= Blue;}
		if (green_on)	{GPIOF_DATA |= Green;}
		GPIOA_Write(GPIOF_DATA, FirstCycle);
		
		FirstCycle = False;
		
		
		
		
//		if((TIMER0->RIS & 0x01)==1){
//			TIMER0->ICR = 1UL;
//			red_on ^= 1;
//		}
		
		
		
		
		
		

		
		
		//Wait(10);
	}
}
