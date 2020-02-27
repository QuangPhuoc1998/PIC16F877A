/*
 * File:   main.c
 * Author: Admin
 *
 * Created on June 8, 2019, 11:02 PM
 */


#include "main.h"
#include "ADC.h"

#define L1 RC0
#define L2 RC1
#define L3 RC2
#define L4 RC3
#define L5 RC4

#define LED7 PORTD

unsigned char code7seg[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
void display(unsigned int number);
void main(void) 
{
    int t;
    // port
    TRISA0 = 1;
    TRISD = 0x00;
    TRISC = 0x00;
    PORTD = 0x00;
    PORTC = 0x00;
    // chuong trinh con
    ADC_Init();
    while(1)
    { 
        t = Read_ADC(0);
        t = t*0.488f;
        display(t);
    }
    return;
}
void display(unsigned int number)
{
    L1 = 1;
    LED7 = 0xC6; // chu C
    __delay_ms(10);
    L1 = 0;
    //
    L2 = 1; // ki tu do
    LED7 = 0x9C; 
    __delay_ms(10);
    L2 = 0;
    //
    L3 = 1;
    LED7 = code7seg[number%10]; 
    __delay_ms(10);
    L3 = 0;
    //
    L4 = 1;
    LED7 = code7seg[number%100/10];
    __delay_ms(10);
    L4 = 0;
    //
    L5 = 1; 
    LED7 = code7seg[number/100];
    __delay_ms(10);
    L5 = 0;
}
