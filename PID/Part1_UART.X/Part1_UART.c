/*
 * File:   Part1_UART.c
 * Author: ADMIN
 *
 * Created on 28 March 2019, 21:31
 */


#include "main.h"
#include "USART.h"


void main(void) 
{
    UART_Init(9600);
    while(1)
    {
       UART_TxChar('A');
       __delay_ms(1000);
    }
    return;
}
