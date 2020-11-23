
#include "tm4c123gh6pm.h"
 

 int main()
	
 {
	  int volatile delay;
	  SYSCTL_RCGCGPIO_R =0x20U;
	  GPIO_PORTF_DIR_R =0x0EU;
	  GPIO_PORTF_DEN_R=0x0EU;
	
	  while(1){
			
	  delay =0;
	  while(delay < 1000000){
		 GPIO_PORTF_DATA_R= 0x0EU;
		++delay;
		}
		
		delay =0;
		while(delay <1000000)
		{
	 GPIO_PORTF_DATA_R=0x00U;
	  ++delay;
		}
	}
 }
 
 
