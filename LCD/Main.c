#include "TM4C123.h" 
#include <string.h>

void LCD_Cmd(uint8_t cmd);
void delay_micro(int n);
void delay_milli(int n);
void LCD_Data(const char data[]);

int main()
{
	SYSCTL->RCGCGPIO =0x01;
	SYSCTL->RCGCGPIO |=0x02;
	GPIOA->DIR |=0xE0;
	GPIOA->DEN |=0xE0;
	GPIOB->DIR |=0xFF;
	GPIOB->DEN |=0xFF;
	
	LCD_Cmd(0x38); // 8 bit, 2 lines, 5x7 font
	LCD_Cmd(0x06); // increament automatically
	LCD_Cmd(0x0F); // turn on display
	LCD_Cmd(0x01); // clear display
	delay_milli(0);
	LCD_Data("Fati");
	delay_milli(0);
}

void LCD_Cmd(unsigned char cmd)
{
	GPIOA->DATA = 0x00; // RS=0, RW=0, E=0
	GPIOB->DATA = cmd;
	GPIOA->DATA = 0x80; // RS=0, RW=0, E=1 secure command
	delay_micro(0);
	if(cmd<4){delay_milli(2);}
	else	{delay_micro(40);}
}

void LCD_Data(const char data[])
{
	for (int itr=0; itr<strlen(data) ;itr++)
	{
		GPIOA->DATA  = 0x20; // RS=1, RW=0, E=0
		GPIOB->DATA  = data[itr];
		GPIOA->DATA |= 0x80; // RS=1, RW=0, E=1  secure command
		delay_milli(1);
		GPIOA->DATA = 0x00; // RS=0, RW=0, E=0
		delay_milli(1);
	}
}

void delay_micro(int n)
{
	for(int itr=0; itr<n; itr++)
		for(int itr2=0; itr2<3; itr2++){}
}

void delay_milli(int n)
{
	for(int itr=0; itr<n; itr++)
		for(int itr2=0; itr2<3180; itr2++){}
}
