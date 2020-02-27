/*
 * File:   DKND_button.c
 * Author: ADMIN
 *
 * Created on 02 April 2019, 21:16
 */


#include "main.h"
#include "lcd4.h"

// dinh nghia button
#define BTN_UP  RC0
#define BTN_DOWN  RC1
#define BTN_STA  RC2
#define BTN_STO  RC3
//
void main(void) 
{
    // khai bao bien
    unsigned int nhietdo = 34;
    // dinh nghia port
    TRISD = 0x00;
    TRISB = 0x00;
    TRISC0 = 1;
    TRISC1 = 1;
    TRISC2 = 1;
    TRISC3 = 1;
    // chuong trinh con
    Lcd_Init();
    // begin
    Lcd_Write_String("Nhiet do dat: ");
    while(1)
    {
        if(BTN_UP == 0)
        {
            while(BTN_UP == 0 );
            if(nhietdo == 60); 
            else nhietdo++;
        }
        if(BTN_DOWN == 0)
        {
            while(BTN_DOWN == 0 );
            if(nhietdo == 34); 
            else nhietdo--;
        }
        if(BTN_STA == 0)
        {
            while(BTN_STA == 0);
            goto here;
        }    
        Lcd_Set_Cursor(1,15);
        Lcd_Write_Char(nhietdo/10+48);
        Lcd_Write_Char(nhietdo%10+48);
    }
    here:
    while(1)
    {
        
    }
    return;
}
