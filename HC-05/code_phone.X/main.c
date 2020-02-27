/*
 * File:   main.c
 * Author: Admin
 *
 * Created on June 22, 2019, 7:25 PM
 */


#include "main.h"
#include "USART.h"

#define BTN1 RD0
#define BTN2 RD1
void main(void) 
{
    TRISD0 = 1;
    TRISD1 = 1;
    //
    UART_Init(9600);
    while(1)
    {
        if(BTN1 == 0)
        {
            while(BTN1==0);
            UART_Write('1');
        }
        if(BTN2 == 0)
        {
            while(BTN2==0);
            UART_Write('0');
        }
    }
    return;
}
