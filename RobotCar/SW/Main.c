#include "TM4C123.h"                    // Device header

#define S1_ECHO					1UL<<0
#define S1_TRIGGER			1UL<<4
#define S2_ECHO					1UL<<1
#define S2_TRIGGER			1UL<<5

typedef struct{
	uint8_t  Trigger;
	uint8_t  Echo;
	uint32_t RisingEdge;
	uint32_t FallingEdge;
	uint32_t Distance;
}Sensor;

Sensor S1,S2;

void Dist_cm (Sensor *S);

int main()
{
	S1.Trigger = S1_TRIGGER;
	S1.Echo		 = S1_ECHO;
	S2.Trigger = S2_TRIGGER;
	S2.Echo		 = S2_ECHO;


	while(1)
	{
		Dist_cm (&S1);
		Dist_cm (&S2);
	}
}
