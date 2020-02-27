/*
 * File:   Quang_tro.c
 * Author: Admin
 *
 * Created on May 28, 2019, 7:17 PM
 */


#include "main.h"
#include "ADC.h"
#include "lcd4.h"

void Lcd_Display(unsigned int value);
void main(void) 
{
    // bien
    unsigned int a;
    // port
    TRISA0 = 1;
    // chuong trinh con
    Lcd_Set_Port('D');
    Lcd_Init();
    ADC_Init();
    // beign
    Lcd_Write_String("Gia tri: ");
    while(1)
    {
        a = Read_ADC(0);
        Lcd_Set_Cursor(1, 10);
        Lcd_Display(a);
        __delay_ms(500);
    }
    return;
}
void Lcd_Display(unsigned int value)
{
    Lcd_Write_Char(value/1000+48);
    Lcd_Write_Char(value%1000/100+48);
    Lcd_Write_Char(value%100/10+48);
    Lcd_Write_Char(value%10+48);
}
