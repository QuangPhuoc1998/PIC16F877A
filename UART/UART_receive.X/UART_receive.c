/*
 * File:   UART_receive.c
 * Author: ADMIN
 *
 * Created on 28 April 2019, 21:51
 */


#include "main.h"
#include "lcd4.h"
#include "USART.h"
#include <conio.h>

unsigned char a, data[8];
unsigned int x_value = 0, y_value = 0;
void Lcd_Display(unsigned int a, unsigned int y_valu);
void main(void) 
{
    // bien 
    
    // port
    TRISB = 0x00;
    PORTB = 0xAA;
    TRISD = 0x00;
    // interrupt uart
    GIE = 1; // ngat toan cuc
    PEIE = 1; // ngat ngoai vi
    RCIE = 1;
    // chuong trinh con
    UART_Init(9600);
    Lcd_Init();
    // begin
    Lcd_Write_String("x = ");
    Lcd_Set_Cursor(2,1);
    Lcd_Write_String("y = ");
    while(1)
    {
       Lcd_Display(x_value, y_value);
    }
    return;
}
void Lcd_Display(unsigned int x_value, unsigned int y_value)
{
    Lcd_Set_Cursor(1, 5);
    Lcd_Write_Char(x_value/1000+48);
    Lcd_Write_Char(x_value%1000/100+48);
    Lcd_Write_Char(x_value%100/10+48);
    Lcd_Write_Char(x_value%10+48);
    
    Lcd_Set_Cursor(2, 5);
    Lcd_Write_Char(y_value/1000+48);
    Lcd_Write_Char(y_value%1000/100+48);
    Lcd_Write_Char(y_value%100/10+48);
    Lcd_Write_Char(y_value%10+48);
}
void __interrupt() My_interrupt(void)
{
  if(RCIE == 1 && RCIF == 1)
  {
    a = UART_Read();
    if(a == ':')
    {
        UART_Read_Text(data, 8);
    }
    x_value = data[0]*1000+data[1]*100+data[2]*10+data[3];
    y_value = data[4]*1000+data[5]*100+data[6]*10+data[7];
  }
}
