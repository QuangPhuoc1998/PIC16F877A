/*
 * File:   main.c
 * Author: Admin
 *
 * Created on June 22, 2019, 1:38 PM
 */


#include "main.h"
#include "USART.h"

unsigned char a;
void main(void) 
{
    
    //
    UART_Init(9600);
    TRISD0 = 0;
    RD0 = 0;
    // interrupt uart
    GIE = 1; // ngat toan cuc
    PEIE = 1; // ngat ngoai vi
    RCIE = 1;
    //
    while(1)
    {
    }
    return;
}
void __interrupt() My_interrupt(void)
{
    a = UART_Read();
    if(a == '0')
    {
        RD0 = 0;
    }
    if(a == '1')
    {
        RD0 = 1;
    }
}
