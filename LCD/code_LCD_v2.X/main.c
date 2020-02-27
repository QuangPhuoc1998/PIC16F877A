/*
 * File:   main.c
 * Author: Admin
 *
 * Created on June 8, 2019, 1:12 PM
 */


#include "main.h"

#define LCD_RS RD0
#define LCD_RW RD6
#define LCD_EN RD1
#define LCD_D4 RD2
#define LCD_D5 RD3
#define LCD_D6 RD4
#define LCD_D7 RD5

#define _LCD_CLEAR				1   		
#define _LCD_RETURN_HOME		2
#define _LCD_ENTRY_MODE			6
#define _LCD_TURN_OFF			8
#define _LCD_TURN_ON			12
#define _LCD_CURSOR_OFF			12 	  
#define _LCD_UNDERLINE_ON		14
#define _LCD_BLINK_CURSOR_ON	15
#define _LCD_MOVE_CURSOR_LEFT	16
#define _LCD_MOVE_CURSOR_RIGHT	17
#define _LCD_SHIFT_LEFT			24
#define _LCD_SHIFT_RIGHT		28
#define _LCD_4BIT_1LINE_5x7FONT	0x20
#define _LCD_4BIT_2LINE_5x7FONT	0x28
#define _LCD_8BIT_1LINE_5x7FONT	0x30
#define _LCD_8BIT_2LINE_5x7FONT	0x38
#define _LCD_FIRST_ROW			128
#define _LCD_SECOND_ROW			192
	
void Lcd_Write_High_Nibble(unsigned char);
void Lcd_Write_Low_Nibble(unsigned char );

#ifdef	USE_CHECK_BUSY
void Lcd_Busy();
#endif


/*-------------------------------------*-
	Lcd_Write_High_Nibble - Local Function
-*-------------------------------------*/
void Lcd_Write_High_Nibble(unsigned char b)
{
	LCD_D7 = b & 0x80;
	LCD_D6 = b & 0x40;
	LCD_D5 = b & 0x20;
	LCD_D4 = b & 0x10; 	
}

/*-------------------------------------*-
	Lcd_Write_High_Low - Local Function
-*-------------------------------------*/
void Lcd_Write_Low_Nibble(unsigned char b)
{
 	LCD_D7 = b & 0x08;
	LCD_D6 = b & 0x04;
	LCD_D5 = b & 0x02;
	LCD_D4 = b & 0x01;
}

/*-------------------------------------*-
	Lcd_Delay_us - Local Function
-*-------------------------------------*/

/*-------------------------------------*-
	Lcd_Busy - Local Function
-*-------------------------------------*/
void Lcd_Busy()
{
	bit busy_flag;
	LCD_D7 = 1;			// Read data
	LCD_RS = 0;
	LCD_RW = 1;			// Read
	do{
		LCD_EN = 0;		// Read High Nibble
		LCD_EN = 1;
		busy_flag = LCD_D7;
		LCD_EN = 0;	 	// Read Low Nibble
		LCD_EN = 1;
	}while(busy_flag);
	LCD_EN = 0;	
}

/*-------------------------------------*-
	Lcd_Init
	- Khoi tao LCD che do 4 bit, font 5x7
-*-------------------------------------*/
void Lcd_Cmd(unsigned char cmd)
{
#ifdef	USE_LCD_RW
	LCD_RW = 0;
#endif
	LCD_RS = 0;
	Lcd_Write_High_Nibble(cmd); 
	LCD_EN = 1;
	LCD_EN = 0;

	Lcd_Write_Low_Nibble(cmd);
	LCD_EN = 1;
	LCD_EN = 0;

#ifdef	USE_CHECK_BUSY
	Lcd_Busy(); 
#else
	switch(cmd)
	{
		case _LCD_CLEAR:
		case _LCD_RETURN_HOME:
			__delay_ms(2);
			break;
		default:
			__delay_us(37);
			break;
	}
#endif
}
void Lcd_Init()
{	
	LCD_RS = 0;
	LCD_EN = 0;
#ifdef	USE_LCD_RW
	LCD_RW = 0;
#endif
	
	__delay_ms(20);

	Lcd_Write_Low_Nibble(0x03);
	LCD_EN = 1;
	LCD_EN = 0;
    __delay_ms(5);

	Lcd_Write_Low_Nibble(0x03);
	LCD_EN = 1;
	LCD_EN = 0;
    __delay_us(100);

	Lcd_Write_Low_Nibble(0x03);
	LCD_EN = 1;
	LCD_EN = 0;
#ifdef	USE_CHECK_BUSY
	Lcd_Busy(); 
#else
	__delay_ms(1);
#endif

	Lcd_Write_Low_Nibble(0x02);
	LCD_EN = 1;
	LCD_EN = 0;
	__delay_ms(1);
		
	Lcd_Cmd(_LCD_4BIT_2LINE_5x7FONT);
	Lcd_Cmd(_LCD_TURN_ON);
	Lcd_Cmd(_LCD_CLEAR);
	Lcd_Cmd(_LCD_ENTRY_MODE);
}

/*-------------------------------------*-
	Lcd_Cmd
	- Gui lenh cho LCD
-*-------------------------------------*/


/*-------------------------------------*-
	Lcd_Chr_Cp
-*-------------------------------------*/
void Lcd_Chr_Cp(unsigned char achar)
{
#ifdef	USE_LCD_RW
	LCD_RW = 0;
#endif
	LCD_RS = 1;
	Lcd_Write_High_Nibble(achar);
	LCD_EN = 1;
	LCD_EN = 0;
	
	Lcd_Write_Low_Nibble(achar);
	LCD_EN = 1;
	LCD_EN = 0;
	
#ifdef	USE_CHECK_BUSY
	Lcd_Busy(); 
#else
	__delay_us(37+4);
#endif	
} 

/*-------------------------------------*-
	Lcd_Chr
	- In ky tu ra man hinh tai (row, column)
-*-------------------------------------*/
void Lcd_Chr(unsigned char row, unsigned char column, 
	unsigned char out_char)
{
	unsigned char add;
	add = (row==1?0x80:0xC0);
	add += (column - 1);
	Lcd_Cmd(add);
	Lcd_Chr_Cp(out_char);
}

void Lcd_Out_Cp(unsigned char * str)
{
	unsigned char i = 0;
	while(str[i])
	{
		Lcd_Chr_Cp(str[i]);
	 	i++;
	}
}

/*-------------------------------------*-
	Lcd_Out
	- In chuoi (text) ra man hinh
	- Vi tri bat dau tai (row, column)
-*-------------------------------------*/
void Lcd_Out(unsigned char row, unsigned char column, 
	unsigned char* text)
{
	unsigned char add;
	add = (row==1?0x80:0xC0);
	add += (column - 1);
	Lcd_Cmd(add);
	Lcd_Out_Cp(text); 
}
/*-------------------------------------*-
   dua con tro toi vi tri hang cot
_*-------------------------------------*/
void Lcd_gotoxy(unsigned char row, unsigned char col)
{
  unsigned char cmd;
  cmd = (row==1?0x80:0xC0) + col - 1;
  Lcd_Cmd(cmd);
}
/*-------------------------------------*-
	Lcd_Custom_Chr Function
	- Tao ky tu tren LCD
	- Tham so:
		location: Vi tri tren CGRAM (0÷7)
		lcd_char: Con tro den mang Font ky tu
	- Ex: Tao ky tu "Clock" sau do in len dong 1, cot 1
		unsigned char code Lcd_Char_Clock[] = {14,21,21,23,17,17,14,0};
		//...
		Lcd_Init();
		Lcd_Custom_Chr(0,Lcd_Char_Clock);
		Lcd_Chr(1,1,0);
		//...
-*-------------------------------------*/
void Lcd_Custom_Chr(unsigned char location, unsigned char * lcd_char) 
{
  	unsigned char i;
    Lcd_Cmd(0x40+location*8);
    for (i = 0; i<=7; i++) 
		Lcd_Chr_Cp(lcd_char[i]);
}
void main(void) 
{
    TRISD = 0x00;
    //
    Lcd_Init();
    Lcd_Out(1,1,"Nhiet do: ");
    while(1)
    {
        
    }
    return;
}
