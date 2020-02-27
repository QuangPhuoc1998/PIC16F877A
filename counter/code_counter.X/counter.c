/*
 * File:   counter.c
 * Author: ADMIN
 *
 * Created on 20 March 2019, 19:58
 */


#include "main.h"
#include "lcd4.h"

void Timer_Init();
void main(void)
{
    // cau hinh port
    TRISD = 0x00;
    unsigned int xung;
    Timer_Init();
    Lcd_Init();
    Lcd_Write_String("Gia tri: ");
    while(1)
    {
        xung = TMR0;
        Lcd_Set_Cursor(1,10);
        Lcd_Write_Char(xung/100+0x30);
        Lcd_Write_Char((xung%100)/10+0x30);
        Lcd_Write_Char(xung%10+0x30);
    }
    return;
}
void Timer_Init()
{
    TRISA4 = 1;
    // cau hinh thanh ghi OPTION_REG
    T0CS = 1; // nguon xung ngoai
    T0SE = 1; // canh xuong
    PSA = 0; // gan bo chia truoc cho timer
    PS0 = 0;
    PS1 = 0;  // chia 2
    PS2 = 0;
    TMR0 = 0;
}
