#ifndef __IO__H_
#define __IO__H_

#define BLUE (1U<<2)
#define GREEN (1U<<3)
#define RED   (1U<<1)

#define SW1 (1U<<4)
#define SW2 (1U<<0)
#define SW1_ 0x10
#define SW2_ 0x01

#define KEY 0x4C4F434B

uint32_t SW_INPUT();
void LED_ON(uint32_t LED);
void PortF_INIT();
#endif
