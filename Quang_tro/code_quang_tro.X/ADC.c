#include "main.h"

void ADC_Init()
{
    // chon phuong an 3 kenh vao so va Vref la dung chung vdk
    PCFG0 = 0;
    PCFG1 = 1;
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
    ADCON0 &= 0b11000101; //Clearing the Channel Selection Bits
    ADCON0 |= channel << 3;
    __delay_ms(2);
    GO_nDONE = 1;
    while(GO_nDONE);
    N = ADRESH;
    return ((N<<8)+ADRESL);
    __delay_us(10);
}