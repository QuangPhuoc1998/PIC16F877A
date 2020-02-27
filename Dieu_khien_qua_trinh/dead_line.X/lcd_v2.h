#ifndef _LCD_H_
#define _LCD_H_

#include "main.h"
void Lcd_Port(unsigned char Data);
void Lcd_Cmd(char CMD);
void Lcd_Clear();
void Lcd_Set_Cursor(unsigned char r, unsigned char c);
void Lcd_Init();
void Lcd_Write_Char(char a);
void Lcd_Write_String(char *a);
void Lcd_Shift_Left();
void Lcd_Shift_Right();

#endif 