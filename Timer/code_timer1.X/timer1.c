/*
 * File:   timer1.c
 * Author: ADMIN
 *
 * Created on 21 March 2019, 21:05
 */


#include "main.h"
#include "lcd4.h"

void Timer_Init();
void main(void) 
{
    Timer_Init();
    TRISC7 = 0;
    RC7 = 0;
    while(1)
    {
        __delay_ms(10);
    }
    return;
}
void Timer_Init()
{
    TMR1H=0xFD;    // delay 1ms
    TMR1L=0x8F;
    //
    T1CKPS1 = 1;
    T1CKPS0 = 1; // chia 8
    T1OSCEN = 0; // tat bo dao dong
    T1SYNC = 0; // dong bo ngo vao xung clock tu ben ngoai
    TMR1CS = 0; //xung noi
    //
    GIE=1; // cho phep ngat toan cuc 
    PEIE=1; // cho phep ngat ngoai vi  
    TMR1IE=1; // cho phep ngat timer1
    //
    TMR1ON = 1; // cho phep bo timer bat dau dem
}
void __interrupt() MyInterrup()
{
    if(TMR1IE == 1 && TMR1IF == 1)
    {
      RC7 = !RC7;
      TMR1H=0xFD;    // delay 1ms
      TMR1L=0x8F;
      TMR1IF = 0;
    }
}
