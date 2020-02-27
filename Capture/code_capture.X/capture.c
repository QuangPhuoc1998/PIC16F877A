/*
 * File:   capture.c
 * Author: ADMIN
 *
 * Created on 26 March 2019, 21:57
 */


#include "main.h"
#include "lcd4.h"

void Timer1_Init();
void Capture_Init();
void main(void) 
{
    // khai bao bien
    unsigned int x = 0;
    unsigned int t = 0;
    // khai bao port
    TRISD = 0x00;
    // begin
    Timer1_Init();
    Capture_Init();
    Lcd_Init();
    Lcd_Write_String("Gia tri: ");
    Lcd_Set_Cursor(2,1);
    Lcd_Write_String("Toc do: ");
    while(1)
    {
        x = CCPR1;
        t = 60000000/(x*0.2f*8*24);
      Lcd_Set_Cursor(1,10);
      Lcd_Write_Char(x/10000+48);
      Lcd_Write_Char((x%10000)/1000+48);
      Lcd_Write_Char((x%1000)/100+48);
      Lcd_Write_Char((x%100)/10+48);
      Lcd_Write_Char(x%10+48);
      // hien thi toc do
      Lcd_Set_Cursor(2,9);
      Lcd_Write_Char(t/10000+48);
      Lcd_Write_Char((t%10000)/1000+48);
      Lcd_Write_Char((t%1000)/100+48);
      Lcd_Write_Char((t%100)/10+48);
      Lcd_Write_Char(t%10+48);
      
    }
    return;
}
void Timer1_Init()
{
    // cai dat gia tri thanh ghi TMR1
    TMR1 = 0;
    // cai dat thanh ghi T1CON
    T1CKPS1 = 1;
    T1CKPS0 = 1; // chia 8
    T1OSCEN = 0;
    T1SYNC = 0;
    TMR1CS = 0;
    // cau hinh ngat
    GIE = 1;
    PEIE = 1;
    TMR1IE = 0; // tat ngat timer1
    // bat dau timer1
    TMR1ON = 1;
}
void Capture_Init()
{
    TRISC2 = 1;
    // cau hinh thanh ghi CCPR1
    CCPR1 = 0;
    // cau hinh ngat
    CCP1IE = 1;
    // cau hinh thanh ghi CCP1CON
    CCP1M3 = 0;
    CCP1M2 = 1; // canh len
    CCP1M1 = 0;
    CCP1M0 = 1;
}
void __interrupt() My_interrupt()
{
    if(CCP1IE == 1 && CCP1IF == 1)
    {
        TMR1 = 0;
        CCP1IF = 0;
    }
}
