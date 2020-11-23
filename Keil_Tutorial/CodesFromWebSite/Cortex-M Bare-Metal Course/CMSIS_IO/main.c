#include "TM4C123.h"                    // Device header
#include "delay.h"
#include "io.h"



int main()
{
	 uint32_t sw_state;
	 PortF_INIT();
	
	while(1){
		sw_state = SW_INPUT();
		
		switch(sw_state){
			case SW1_:
			LED_ON(GREEN);
			break;
			case SW2_:
			LED_ON(BLUE);
			break;
			
		}
	}
	
}





