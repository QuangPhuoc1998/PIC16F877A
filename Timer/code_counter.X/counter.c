/*
 * File:   timer1.c
 * Author: ADMIN
 *
 * Created on 21 March 2019, 21:05
 */


#include "main.h"
#include "lcd4.h"

void Counter_Init();
void main(void) 
{
    // khai bao bien
    unsigned int x = 0;
    // cau hinh port
    TRISC0 = 1;
    TRISD = 0x00;
    // cau hinh ngoai vi
    Counter_Init();
    Lcd_Init();
    // lcd
    Lcd_Write_String("Gia tri: ");
    while(1)
    {
        x = (TMR1H<<8)+TMR1L;
        Lcd_Set_Cursor(1,10);
        Lcd_Write_Char(x/10000+48);
        Lcd_Write_Char((x%10000)/1000+48);
        Lcd_Write_Char((x%1000)/100+48);
        Lcd_Write_Char((x%100)/10+48);
        Lcd_Write_Char(x%10+48);
    }
    return;
}
void Counter_Init()
{
    TMR1H=0;    
    TMR1L=0;
    // TICON = 0x0F
    T1CKPS1 = 0;
    T1CKPS0 = 0; // chia 4
    T1OSCEN = 1; // bat bo dao dong
    T1SYNC = 1; // khon dong bo ngo vao xung clock tu ben ngoai
    TMR1CS = 1; //xung ngoai
    TMR1ON = 1; // cho phep bo timer bat dau dem
}

