/*
 * File:   test.c
 * Author: ADMIN
 *
 * Created on 24 March 2019, 23:06
 */


#include "main.h"

void main(void)
{
    TRISA = 0x00;
    TRISB = 0x00;
    TRISC = 0x00;
    TRISD = 0x00;
    TRISE0 = 0;
    TRISE1 = 0;
    TRISE2 = 0;
    while(1)
    {
        PORTA = PORTB = PORTC = PORTD = PORTE = 0xAA;
        __delay_ms(500);
        PORTA = PORTB = PORTC = PORTD = PORTE = 0x55;
        __delay_ms(500);
    }
    return;
}
