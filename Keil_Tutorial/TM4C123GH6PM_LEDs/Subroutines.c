#include <TM4C123GH6PM.h>
#include <string.h>
#include "Globals.h"

void Wait(int t)
{
	for(int itr=0; itr<=(t); itr++);
}

void update_bit(bit *Bit, _Bool FC)
{
	Bit->R_Trig = (Bit->IsOn != Bit->tmp) && Bit->IsOn;
	Bit->F_Trig = (Bit->IsOn != Bit->tmp) && !Bit->IsOn;
	Bit->tmp = Bit->IsOn;
	if (FC){Bit->IsOn =0; Bit->tmp=0; Bit->R_Trig = 0; Bit->F_Trig =0;}
}

void TON (Timer *Tx, _Bool FC)
{
	if (Tx->En.R_Trig || (Tx->En.IsOn && Tx->R)){Tx->CDT = Tx->time;}
	if (Tx->En.IsOn){ Tx->CDT--;} else{Tx->CDT = 0;}
	if (Tx->CDT <= 0){Tx->CDT = 0;}
	Tx->Q = Tx->CDT == 0 && Tx->En.IsOn;
	if (FC){Tx->Q = 0; Tx->CDT =0;}
}

void TOF (Timer *Tx, _Bool FC)
{
	if (Tx->En.IsOn  || (Tx->Q && Tx->R)){Tx->CDT = Tx->time;}
	if (!Tx->En.IsOn){ Tx->CDT--;}
	if (Tx->CDT <= 0){Tx->CDT = 0;}
	Tx->Q = Tx->CDT > 0;
	if (FC){Tx->Q = 0; Tx->CDT =0; Tx->R=0;}
}

uint32_t GPIOA_Read(void)
{
	return GPIOF->DATA & 0x11UL;
}

void GPIOA_Write(uint32_t GPIOF_DATA_Aux, _Bool FC)
{
	if (FC){GPIOF->DATA = 0x0;}
	else   {GPIOF->DATA = GPIOF_DATA_Aux;}
}

void PauseAndBlink(char color[], int On_Time, int Off_Time)
{
	GPIOF->DATA = 0x0;
	for (int itr=0; itr < strlen(color); itr++)
	{
		switch (color[itr])
		{
			case 'R' :
				GPIOF->DATA = Red;
				break;
			
			case 'G' :
				GPIOF->DATA = Green;
				break;
			
			case 'B' :
				GPIOF->DATA = Blue;
				break;
		}
				Wait(On_Time);
		GPIOF->DATA = 0x0;
		Wait(Off_Time);	
	}
}

void TIMER0A_Handler(void)
{
	flags = FLAG_Toggle_LED;
	TIMER0->ICR = 1UL;
}
