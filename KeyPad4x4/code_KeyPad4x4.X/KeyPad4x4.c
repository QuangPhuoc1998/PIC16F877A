/*
 * File:   KeyPad4x4.c
 * Author: ADMIN
 *
 * Created on 03 May 2019, 20:22
 */


#include "main.h"
#include "lcd4.h"
#include "KeyPad4x4.h"

#define L1 RB6
#define L2 RB7
unsigned char code7seg[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
void Led7_display(unsigned int number);
void main(void)
{
    
    // bien
    unsigned char key;
    // port
    TRISD = 0xF0;
    PORTD = 0x0F;
    TRISB = 0x00;
    TRISC = 0x00;
    // chuong trinh con
    Lcd_Init();
    // begin
    Lcd_Write_String("Gia tri: ");
    PORTC = code7seg[0];
    while(1)
    {
       if(Key_press() != 0) key = Key_press();
       Lcd_Display(key);
       Led7_display(key);
    }
    return;
}
void Led7_display(unsigned int number)
{
    L1 = 1;
    PORTC = code7seg[number%10];
    __delay_ms(10);
    L1 = 0;
    L2 = 1;
    PORTC = code7seg[number/10];
    __delay_ms(10);
    L2 = 0;
}
