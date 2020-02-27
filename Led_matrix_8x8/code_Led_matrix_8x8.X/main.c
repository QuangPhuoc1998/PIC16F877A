/*
 * File:   main.c
 * Author: Admin
 *
 * Created on June 9, 2019, 9:22 PM
 */


#include "main.h"

unsigned int n;
unsigned char hang[8]={0x3E,0x33,0x33,0x33,0x3E,0x30,0x30,0x78};
unsigned char cot[8]={0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F}; 
unsigned char code_1[8] = {0x18,0x1C,0x1E,0x18,0x18,0x18,0xFF,0xFF};
void main(void) 
{
    TRISC=0x00;
    TRISD=0x00; 
    while(1)
    {
        for(n=0;n<=7;n++)
        { 
            PORTC=cot[n];
            PORTD=code_1[n];
            __delay_ms(1);
        }
    }
    return;
}
