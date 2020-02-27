#include "main.h"

#define LCD_RS RB3
#define LCD_RW RB1
#define LCD_EN RB2
#define LCD_RS_TRIS TRISB3
#define LCD_RW_TRIS TRISB1
#define LCD_EN_TRIS TRISB2

#define LCD_D7 RD7
#define LCD_D6 RD6
#define LCD_D5 RD5
#define LCD_D4 RD4
#define LCD_D3 RD3
#define LCD_D2 RD2
#define LCD_D1 RD1
#define LCD_D0 RD0
#define LCD_D7_TRIS TRISD7
#define LCD_D6_TRIS TRISD6
#define LCD_D5_TRIS TRISD5
#define LCD_D4_TRIS TRISD4
#define LCD_D3_TRIS TRISD3
#define LCD_D2_TRIS TRISD2
#define LCD_D1_TRIS TRISD1
#define LCD_D0_TRIS TRISD0

#define LCD_CLEAR_DISPLAY 0x01
#define LCD_CURSOR_HOME 0x80
#define LCD_UP_NOSHIFT 0x06
#define LCD_CURSOR_OFF 0x0C

void LCD_8_Init();
void LCD_Init();
void LCD_8_Cmd(char select, char cmd);
void LCD_Cmd(char select, char cmd);
void LCD_Out_Str(char str[]);
void LCD_Out_Int(signed int value);
void LCD_Out_Double(double value);
unsigned char LCD_IsBusy();
void LCD_GotoXy(unsigned char col, unsigned char row);