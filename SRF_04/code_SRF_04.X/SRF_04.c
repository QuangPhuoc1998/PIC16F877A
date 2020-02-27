/*
 * File:   SRF_04.c
 * Author: ADMIN
 *
 * Created on 25 April 2019, 21:15
 */


#include "main.h"
#include "lcd4.h"

#define Echo RB1
#define Trig RB0
void Timer_Init();
void Lcd_Display(unsigned int s);
void main(void) 
{
    // bien
    unsigned int t;
    // port
    TRISD = 0x00;
    TRISB0 = 0;
    TRISB1 = 1;
    // chuong trinh con
    void Timer_Init();
    Lcd_Init();
    // begin
    Lcd_Write_String("S = ");
    Lcd_Set_Cursor(1, 9);
    Lcd_Write_String("cm");
    while(1)
    {
      Trig = 1; 
      __delay_ms(15);
      Trig = 0;
      //
      while(Echo == 0);
      TMR1ON = 1;
      while(Echo == 1);
      TMR1ON = 0;
      //
      t = TMR1*0.2f;
      t = t/58.82f; 
      if(t >= 2 && t <= 400)
      {
         Lcd_Display(t); 
      }
      else
      {
         Lcd_Display(0);  
      }
      TMR1 = 0;
      __delay_ms(1000);
    }
    return;
}
void Lcd_Display(unsigned int s)
{
    Lcd_Set_Cursor(1, 5);
    Lcd_Write_Char(s/100+48);
    Lcd_Write_Char(s%100/10+48);
    Lcd_Write_Char(s%10+48);
}
void Timer_Init()
{
    TMR1CS = 0; //xung noi
    T1CKPS1 = 0;
    T1CKPS0 = 1; // chia 2
}
