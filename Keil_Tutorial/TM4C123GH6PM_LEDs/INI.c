#include<TM4C123GH6PM.h>
#define KEY 0x4C4F434B

void SYSTEM_Setup(void)
{
/*------------------------------------------------------/
  GPIOF ------------------------------------------------/
/------------------------------------------------------*/
	/* GPIO Run Mode Clock Gating Control (RCGCGPIO), see pg.340
		 Enables the clock of GPIO ports in run mode. 
		 *((uint32_t volatile *)0x400F.E608) = 0B0010 0000:	Enables Port F only */
	SYSCTL->RCGCGPIO |= 1UL<<5;

	/* GPIO Lock (GPIOLOCK), see pg.684
		 Locks the GPIOCR register.
		 Writing 0x4C4F.434B to the GPIOLOCK of a port unlocks it's GPIOCR register.
		 Reading GPIOLOCK, regardless of what have been written into it,
		 returns 0 or 1 showing the status of lock.
		 PORT F: *((uint32_t volatile *)0x4002.5520) = 0x4C4F434B:	Unlocks the GPIOCR of port F */
	GPIOF->LOCK = KEY;
	
	/* GPIO Commit (GPIOCR), see pg.685
		 Manages the access to data write.
		 All GPIO are locked to write if their corresponding bit in GPIOCR is 0.
		 Except some special pins (see Table 10-10, pg.682) all other are write-allowed by default.
		 PORT F: GPIOF->CR = oxFE by default, means, PF0(Switch2) is blocked to write. 
		 PORT F: *((uint32_t volatile *)0x4002.5524) = 0b1111 1111:	Makes porf F all writable.*/
	GPIOF->CR = 0xFF;

	/* GPIO Direction (GPIODIR), see pg.663
		 Specifies each pin of a port as bit or output
		 PORT F: *((uint32_t volatile *)0x4002.5400) = 0b0000 1110
		 PF0(Switch2) and PF4(Switch1) are bit
		 PF1(LEDR), PF2(LEDB), PF3(LEDG), PF5, PF6, and PF7 are output */
	GPIOF->DIR |= 0x0E;
	
	/* GPIO Pull-Up Select (GPIOPUR), see pg.677
		 Enables the internal Pull-Up resister of each pin of a port
		 PORT F: *((uint32_t volatile *)0x4002.5510) = 0b0001 0001
		 The pull-up resistor PF0(Switch2) and PF4(Switch1) are Enabled
		 and the rest are disabled */
	GPIOF->PUR |= 0x11;
	
	/* GPIO Digital Enable (GPIODEN), see pg.682
		 Enables the digital functionality of each pin of a port
		 PORT F: *((uint32_t volatile *)0x4002.551C) = 0b0001 1111
		 PF0 to PF4 are enabled and the rest are disabled */
	GPIOF->DEN |= 0x1F;
	
	/* GPIO Data (GPIODATA), see pg.662
		 Returns the current state of each pin of a port
		 and writable for output pins
		 PORT F: 0x4002.53FC: with access to all pins */
	GPIOF->DATA = 0x00;
	
/*------------------------------------------------------/
  TIMER0 A ---------------------------------------------/
/------------------------------------------------------*/
	/* General-Purpose Timer Run Mode Clock Gating Control(RCGCTIMER), see pg.338
		 Enables the clock of 16/32 GPTM in run mode.
		 *((uint32_t volatile *)0x400F.E604) = 0b00 0001: Enables Timer 0 */
	SYSCTL->RCGCTIMER = 1;
	
	/* GPTM Control (GPTMCTL), see pg.737
		Activates the timer to count.
		 To configure the timer the corresponiding control bit needs to be disabled.
		 *((uint32_t volatile *)0x4003.000C) = 0b0000 0000: Disable Timer A0 */
	TIMER0->CTL &= ~0x1;

	/*  (GPTMCFG), see pg.
		 */
	TIMER0->CFG = 0x0;

	/* GPTM Timer A Mode (GPTMTAMR), see pg.729
		 periodic timer
		 0x4003.0004 = :  */
	TIMER0->TAMR  = 0x2;
	//TIMER0->TAMR &= ~(1UL<<4);

	//(GPTMTAILR) start value
	TIMER0->TAILR = 64000000; // 16MHZ = 1s
	
	TIMER0->IMR|=1;
	NVIC_EnableIRQ(TIMER0A_IRQn);
	
	// timeout, time reached, is shown in TIMER0->RIS
	// reset the timer afrer timout TIMER0->ICR
}
