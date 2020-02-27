/*
 * File:   SPI.c
 * Author: ADMIN
 *
 * Created on 26 April 2019, 09:58
 */


#include "main.h"
#include "spi.h"
#include <stdio.h>


void ADC_Init(unsigned char channel);
unsigned int Read_ADC(unsigned char channel);
void main(void) 
{
    unsigned int a, b;
    // port
   
    // chuong trinh con
    Spi_Init(SPI_MASTER_OSC_DIV4, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
    ADC_Init(0);
    ADC_Init(1);
    // begin
                                                                                                                                                                                                          
    while(1)
    { 
        a = Read_ADC(0);
        b = Read_ADC(1);
        Spi_Write(':');
        __delay_us(10);
        Spi_Write(a/1000);
        Spi_Write(a%1000/100);
        Spi_Write(a%100/10);
        Spi_Write(a%10);
        __delay_ms(10);
        Spi_Write(b/1000);
        Spi_Write(b%1000/100);
        Spi_Write(b%100/10);
        Spi_Write(b%10);
        __delay_ms(10);
    }
    return;
}
void ADC_Init(unsigned char channel)
{
    // chon phuong an 3 kenh vao so va Vref la dung chung vdk
    PCFG0 = 0;
    PCFG1 = 0;
    PCFG2 = 1;
    PCFG3 = 0;
    // chon tan so ADC la 1/64
    ADCS0 = 0;
    ADCS1 = 1;
    ADCS2 = 1;
    // ket qua chuyen doi can phai
    ADFM = 1;
    // bat ADC
    ADON = 1;
    // vo hieu hoa ngat
    ADIE = 0;
    ADIF = 0;
    // cai dat chan
    switch (channel)
    {
        case 1:
            TRISA0 = 1;
            break;
        case 2:
            TRISA1 = 1;
            break;
        case 3:
            TRISA2 = 1;
            break;  
        case 4:
            TRISA3 = 1;
            break; 
        default:
            break;
    }
    
}
unsigned int Read_ADC(unsigned char channel)
{
    unsigned int N;
    ADCON0 &= 0x11000101; //Clearing the Channel Selection Bits
    if(channel > 3) return 0;
    ADCON0 |= channel << 3;
    __delay_ms(2);
    GO_nDONE = 1;
    while(GO_nDONE);
    N = ADRESH;
    return ((N<<8)+ADRESL);   
}
