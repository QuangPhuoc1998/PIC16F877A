#include "main.h"
#include "lcd_v2.h"

#define LCD_EN_Delay 500
#define LCD_DATA_PORT_D TRISD
#define LCD_RS_D TRISD0
#define LCD_EN_D TRISD1
#define RS RD0
#define EN RD1
#define D4 RD2
#define D5 RD3
#define D6 RD4
#define D7 RD5

void Lcd_Port(unsigned char Data)
{
  if(Data & 1)
    D4 = 1;
  else
    D4 = 0;
  if(Data & 2)
    D5 = 1;
  else
    D5 = 0;
  if(Data & 4)
    D6 = 1;
  else
    D6 = 0;
  if(Data & 8)
    D7 = 1;
  else
    D7 = 0;
}
void Lcd_Cmd(char CMD)
{
  // Select Command Register
  RS = 0;
  // Move The Command Data To LCD
  Lcd_Port(CMD);
  // Send The EN Clock Signal
  EN = 1;
  __delay_us(LCD_EN_Delay);
  EN = 0; 
}
void Lcd_Clear()
{
  Lcd_Cmd(0);
  Lcd_Cmd(1);
}
void Lcd_Set_Cursor(unsigned char r, unsigned char c)
{
  unsigned char Temp,Low4,High4;
  if(r == 1) 
  {
    Temp = 0x80 + c - 1; //0x80 is used to move the cursor
    High4 = Temp >> 4;
    Low4 = Temp & 0x0F;
    Lcd_Cmd(High4);
    Lcd_Cmd(Low4);
  }
  if(r == 2) 
  {
    Temp = 0xC0 + c - 1;
    High4 = Temp >> 4;
    Low4 = Temp & 0x0F;
    Lcd_Cmd(High4);
    Lcd_Cmd(Low4);
  }
}
void Lcd_Init()
{
  // IO Pin Configurations
  LCD_DATA_PORT_D = 0x00;
  LCD_RS_D = 0;
  LCD_EN_D = 0; 
  // The Init. Procedure As Described In The Datasheet
  Lcd_Port(0x00);
  __delay_ms(30);
  __delay_us(LCD_EN_Delay);
  Lcd_Cmd(0x03);
  __delay_ms(5);
  Lcd_Cmd(0x03);
  __delay_us(150);
  Lcd_Cmd(0x03);
  Lcd_Cmd(0x02);
  Lcd_Cmd(0x02);
  Lcd_Cmd(0x08);
  Lcd_Cmd(0x00);
  Lcd_Cmd(0x0C);
  Lcd_Cmd(0x00);
  Lcd_Cmd(0x06);
}
void Lcd_Write_Char(char a)
{
  char Low4,High4;
  Low4 = a & 0x0F;
  High4 = a & 0xF0;
  RS = 1;
  Lcd_Port(High4>>4);
  EN = 1;
  __delay_us(LCD_EN_Delay);
  EN = 0;
  __delay_us(LCD_EN_Delay);
  Lcd_Port(Low4);
  EN = 1;
  __delay_us(LCD_EN_Delay);
  EN = 0;
  __delay_us(LCD_EN_Delay);
}
void Lcd_Write_String(char *a)
{
  int i;
  for(i=0;a[i]!='\0';i++)
  Lcd_Write_Char(a[i]);
}
void Lcd_Shift_Left()
{
  Lcd_Cmd(0x01);
  Lcd_Cmd(0x08);
}
void Lcd_Shift_Right()
{
  Lcd_Cmd(0x01);
  Lcd_Cmd(0x0C);
}