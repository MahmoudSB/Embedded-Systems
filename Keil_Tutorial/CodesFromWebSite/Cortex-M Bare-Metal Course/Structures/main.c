#include <stdint.h>

typedef struct{
	uint8_t age;
	uint8_t height;
}Boy;

Boy Kobe,Lebron;

typedef struct{
  Boy error[3];
}Precision;

Precision p;

int main()
{

	
	uint8_t kobe_age_with_error_high;
	uint8_t kobe_age_with_error_low;
	
	Kobe.age = 35;
	Kobe.height = 6;
	
	 
	Lebron.age = Kobe.age - 5;
	
	p.error[0].age =1;
	p.error[1].height =2;
	
	kobe_age_with_error_high = Kobe.age + p.error[0].age;
	kobe_age_with_error_low  = Kobe.age - p.error[0].age;
	
	 Boy * pBoy;
	 pBoy = &Kobe;
//	 (*pBoy).age =29;
//	 (*pBoy).age =39;
//	 (*pBoy).age =49;
	 
	 pBoy->age=29;
	 pBoy->age=39;
	 pBoy->age=49;
	 
	 
	
}