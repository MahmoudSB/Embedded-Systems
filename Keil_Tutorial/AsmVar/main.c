#include<stdint.h>

extern uint32_t amount;
static uint32_t c_amount;
uint32_t c2_amount;

uint32_t Amount_Func(void);

int main(void)
{
	Amount_Func();
	c_amount=amount;
	c2_amount=c_amount;
}
