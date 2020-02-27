/*
 * File:   Giao_tiep_may_tinh.c
 * Author: ADMIN
 *
 * Created on 04 April 2019, 09:38
 */


#include "main.h"
#include "USART.h"

void main(void) 
{
    unsigned char c;
    // cau hinh port
    TRISC7 = 1;
    TRISC6 = 0;
    TRISD0 = 0;
    TRISD1 = 0;
    TRISD2 = 0;
    RD0 = 0;
    RD1 = 0;
    RD2 = 0;        
    // begin
    UART_Init(9600);         
    while(1)
    {
       c = UART_Read();
       switch (c)
       {
           case '1':
               RD0 = !RD0;
               break;
           case '2':
               RD1 = !RD1;
               break;
           case '3':
               RD2 = !RD2;
               break;
           default:
               break;
       }
       UART_Write(0xAA);
       __delay_ms(100);
    }
    return;
}
