
#ifndef LCD2x16_h
#define LCD2x16_h

#include "TM4C123.h"                    // Device header
#include <string.h>
#include <stdint.h>

//#define RS	1
//#define	RW	2
//#define	E		4

#define LCD_4BITS_CONFG			0x28		// 4 bits, , 2 lines, 5x7 font
#define LCD_8BITS_CONFG			0x38		// 8 bits, , 2 lines, 5x7 font
#define LCD_INCREMENT_AUTO	0x06
#define LCD_DISPLAY_ON			0x0F
#define LCD_DISPLAY_CLEAR		0x01


typedef struct{
	_Bool D0;
	_Bool D1;
	_Bool D2;
	_Bool D3;
	_Bool D4;
	_Bool D5;
	_Bool D6;
	_Bool D7;
	uint8_t Data;
		
}__DATA_R;

typedef struct{
	_Bool RS;
	_Bool RW;
	_Bool E;
	uint8_t Ctrl;
}__CTRL_R;

void LCD_INI( _Bool FourBitsMode, __DATA_R *DATAR, __CTRL_R *CTRLR );
void LCD_4BITS_WRITE( unsigned char __WORD );
void LCD_CMD( unsigned char cmd, __DATA_R *DATAR, __CTRL_R *CTRLR);
void LCD_DATA( unsigned char data, __DATA_R *DATAR, __CTRL_R *CTRLR );
void GPIO_UPDATE(uint8_t Data, uint8_t Ctrl, __DATA_R *DATAR, __CTRL_R *CTRLR );
void delay_us(int n);
void delay_ms(int n);

void LCD_DISP(  _Bool FourBitsMode, __DATA_R *DATAR, __CTRL_R *CTRLR, unsigned char WhatToDisp )
{
//	DATAR->Data =(DATAR->D7 <<7) |
//							 (DATAR->D6 <<6) |
//							 (DATAR->D5 <<5) |
//							 (DATAR->D4 <<4) |
//							 (DATAR->D3 <<3) |
//							 (DATAR->D2 <<2) |
//							 (DATAR->D1 <<1) |
//							 (DATAR->D0 <<0) ; 
//	
//	CTRLR->Ctrl =((CTRLR->E &=1) |
//							 (CTRLR->RW &=1) |
//							 (CTRLR->RS &=1) )
//							&(0x07);
	
LCD_INI( FourBitsMode, DATAR, CTRLR  );
LCD_DATA( WhatToDisp, DATAR, CTRLR  );
	
}



void LCD_INI( _Bool FourBitsMode, __DATA_R *DATAR, __CTRL_R *CTRLR )
{
	if (FourBitsMode){
		LCD_CMD(LCD_8BITS_CONFG, DATAR, CTRLR );
	}else{
		LCD_CMD(LCD_4BITS_CONFG, DATAR, CTRLR );
	}
	
	LCD_CMD(LCD_INCREMENT_AUTO, DATAR, CTRLR );
	LCD_CMD(LCD_DISPLAY_ON, DATAR, CTRLR );
	LCD_CMD(LCD_DISPLAY_CLEAR, DATAR, CTRLR );
}





void LCD_4BITS_WRITE( unsigned char __WORD )
{
	
}

void LCD_CMD( unsigned char cmd, __DATA_R *DATAR, __CTRL_R *CTRLR )
{
	CTRLR->Ctrl = 0x00;
	GPIO_UPDATE(DATAR->Data, CTRLR->Ctrl, DATAR, CTRLR );
	DATAR->Data = cmd;
	GPIO_UPDATE(DATAR->Data, CTRLR->Ctrl, DATAR, CTRLR );
	CTRLR->Ctrl = 0x04;
	GPIO_UPDATE(DATAR->Data, CTRLR->Ctrl, DATAR, CTRLR );
	
	if(cmd<4){delay_ms(2);}
	else{delay_us(40);}
}

void LCD_DATA( unsigned char data, __DATA_R *DATAR, __CTRL_R *CTRLR )
{
	CTRLR->Ctrl = 0x01;
	GPIO_UPDATE(DATAR->Data, CTRLR->Ctrl, DATAR, CTRLR );
	DATAR->Data = data;
	GPIO_UPDATE(DATAR->Data, CTRLR->Ctrl, DATAR, CTRLR );
	CTRLR->Ctrl |= 0x04;
	GPIO_UPDATE(DATAR->Data, CTRLR->Ctrl, DATAR, CTRLR );
	delay_ms(2);
	CTRLR->Ctrl = 0x00;
	GPIO_UPDATE(DATAR->Data, CTRLR->Ctrl, DATAR, CTRLR );
	delay_ms(2);
}

void GPIO_UPDATE(uint8_t Data, uint8_t Ctrl, __DATA_R *DATAR, __CTRL_R *CTRLR )
{
	DATAR->D7 = (Data & 0x80) >>7;
	DATAR->D7 = (Data & 0x40) >>6;
	DATAR->D7 = (Data & 0x20) >>5;
	DATAR->D7 = (Data & 0x10) >>4;
	DATAR->D7 = (Data & 0x08) >>3;
	DATAR->D7 = (Data & 0x04) >>2;
	DATAR->D7 = (Data & 0x02) >>1;
	DATAR->D7 = (Data & 0x01) >>0;
	
	CTRLR->E  = (Ctrl & 0x04) >>2;
	CTRLR->RW = (Ctrl & 0x02) >>1;
	CTRLR->RS = (Ctrl & 0x01) >>0;
	
}

void delay_us(int n)
{
	for(int itr=0; itr<n; itr++)
		for(int itr2=0; itr2<3; itr2++){}
}

void delay_ms(int n)
{
	for(int itr=0; itr<n; itr++)
		for(int itr2=0; itr2<3180; itr2++){}
}

#endif
