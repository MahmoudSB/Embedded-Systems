#include <TM4C123GH6PM.h>

#ifndef Red 
#define Red 							1UL<<1 
#endif

#ifndef	Blue
#define Blue 							1UL<<2
#endif

#ifndef Green
#define Green 						1UL<<3
#endif

#ifndef Off
#define Off								0x00
#endif

#ifndef True
#define True							1
#endif

#ifndef False
#define False							0
#endif

#ifndef FLAG_NONE
#define FLAG_NONE 				0
#endif

#ifndef FLAG_Toggle_LED
#define FLAG_Toggle_LED 	1
#endif

#ifndef __Struct_bit__
	#define __Struct_bit__
	typedef struct  {
		_Bool IsOn;
		_Bool R_Trig;
		_Bool F_Trig;
		_Bool tmp;
	}bit;
#endif
	
#ifndef __Struct_Timer__
	#define __Struct_Timer__
	typedef struct  {
		 bit En;
		_Bool Q;
		_Bool R;
		int time;
		int CDT;
	} Timer;
#endif

#ifndef __GPIOA_Read__
	#define __GPIOA_Read__
	uint32_t GPIOA_Read(void);
#endif

#ifndef __GPIOA_Write__
	#define __GPIOA_Write__
	void GPIOA_Write(uint32_t GPIOF_DATA_Aux, _Bool FC);
#endif

#ifndef __TON__
	#define __TON__
	void TON (Timer *Tx, _Bool FC);
#endif

#ifndef __TOF__
	#define __TOF__
	void TOF (Timer *Tx, _Bool FC);
#endif

#ifndef __Wait__
	#define __Wait__
	void Wait(int t);
#endif

#ifndef __PauseAndBlink__
	#define __PauseAndBlink__
	void PauseAndBlink(char color[], int On_Time, int Off_Time);
#endif

#ifndef __TIMER0A_Handler__
	#define __TIMER0A_Handler__
	void TIMER0A_Handler(void);
#endif

#ifndef __update_bit__
	#define __update_bit__
	void update_bit(bit *Bit, _Bool FC);
#endif

extern volatile int flags;
