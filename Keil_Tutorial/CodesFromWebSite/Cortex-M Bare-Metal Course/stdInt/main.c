#include <stdint.h>

int main()
{
	 int number;
	  
	 int8_t x1;
	 uint8_t x2;
	
	 int16_t y1;
	 uint16_t y2;
	
	 int32_t z1;
	 uint32_t z2;
	
	
	 int number_size =  sizeof(number);
	 
	 int8_t signed8 = sizeof(x1);
	 uint8_t usigned8 = sizeof(x2);
	
	  int16_t signed16 = sizeof(y1);
	 uint16_t usigned16 = sizeof(y2);
	
	  int32_t signed32 = sizeof(z1);
	 uint32_t usigned32 = sizeof(z2);
	 
}