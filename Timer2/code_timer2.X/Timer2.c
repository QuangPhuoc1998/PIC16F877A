/*
 * File:   Timer2.c
 * Author: ADMIN
 *
 * Created on 25 March 2019, 20:44
 */


#include "main.h"
#include "lcd4.h"

void Timer_Init();
void main(void) 
{
    // khao bao bien
    
    // cau hinh port
    TRISB0 = 0;
    RB0 = 0;
    // begin
    Timer_Init();
    while(1)
    {
    }
    return;
}
void Timer_Init()
{
    // cai dat thanh ghi TMR2
    TMR2 = 131; // delay 100us 
    // cau hinh thanh ghi T2CON
    TOUTPS3 = 0;
    TOUTPS2 = 0;
    TOUTPS1 = 0; // 1:1 postscale
    TOUTPS0 = 0;
    T2CKPS1 = 0; // pre = 16
    T2CKPS0 = 1;
    // cai dat ngat
    GIE = 1;
    PEIE = 1;
    TMR2IE = 1; // cho phep ngat timer 2
    // On timer2
    TMR2ON = 1;
}
void __interrupt() My_interrupt()
{
    if(TMR2IF == 1 && TMR2IE == 1 )
    {
        RB0 = !RB0;
        TMR2 = 131;
        TMR2IF = 0; 
    }
}
