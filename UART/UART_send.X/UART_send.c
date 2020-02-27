/*
 * File:   UART_send.c
 * Author: ADMIN
 *
 * Created on 28 April 2019, 20:28
 */


#include "main.h"
#include "lcd4.h"
#include "USART.h"
#include <stdio.h>

#define BT1 RB0
#define BT2 RB1
#define BT3 RB2

void ADC_Init();
unsigned int Read_ADC(unsigned char channel);
void UART_Send(unsigned int x_value, unsigned int y_value);
void main(void) 
{
    // bien
    unsigned int a, b;
    //port
    TRISB |= 0x00000111;
    PORTB |= 0x00000111;
    // chuong trinh con
    ADC_Init();
    UART_Init(9600);
    while(1)
    {
      a = Read_ADC(0);
      b = Read_ADC(1);
      UART_Send(a,b);    
    }
    return;
}
void ADC_Init()
{
    // chon phuong an 3 kenh vao so va Vref la dung chung vdk
    PCFG0 = 0;
    PCFG1 = 0;
    PCFG2 = 0;
    PCFG3 = 0;
    // chon tan so ADC la 1/64
    ADCS0 = 1;
    ADCS1 = 0;
    ADCS2 = 1;
    // ket qua chuyen doi can phai
    ADFM = 1;
    // bat ADC
    ADON = 1;
    // vo hieu hoa ngat
    ADIE = 0;
    ADIF = 0;
}
unsigned int Read_ADC(unsigned char channel)
{
    unsigned int N;
    ADCON0 &= 0x11000101; //Clearing the Channel Selection Bits
    ADCON0 |= channel << 3;
    __delay_ms(2);
    GO_nDONE = 1;
    while(GO_nDONE);
    N = ADRESH;
    return ((N<<8)+ADRESL);
    __delay_us(10);
}
void UART_Send(unsigned int x_value, unsigned int y_value)
{
   UART_Write(':');
   __delay_us(10);
   UART_Write(x_value/1000);
   UART_Write(x_value%1000/100);
   UART_Write(x_value%100/10);
   UART_Write(x_value%10);
   __delay_ms(50); 
   UART_Write(y_value/1000);
   UART_Write(y_value%1000/100);
   UART_Write(y_value%100/10);
   UART_Write(y_value%10);
   __delay_ms(50);
}

