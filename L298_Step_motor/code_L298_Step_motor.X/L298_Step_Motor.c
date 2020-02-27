#include "main.h"

unsigned char full_drive_right[4] = {0x09,0x0C, 0x06, 0x03};
unsigned char full_drive_left[4] = {0x03,0x06, 0x0C, 0x09};

void GPIO_Init();
void Delay_customer(unsigned int timer);
void Timer_Init();
void ADC_Init();
unsigned int Read_ADC(unsigned char channel);
long map(long x, long in_min, long in_max, long out_min, long out_max);
void main(void) 
{
    static short t;
    unsigned int adc_value = 10;
    //
    ADC_Init();
    GPIO_Init();
    //Timer_Init();
    //
    while(1)
    {
        adc_value = map(Read_ADC(0),0,1023,700,10000);
        switch (t)
        {
            case 0:
            PORTB = full_drive_right[0];
            break;
            case 1:
            PORTB = full_drive_right[1];
            break;
            case 2:
            PORTB = full_drive_right[2];
            break;
            case 3:
            PORTB = full_drive_right[3];
            break;
            default: break;
        }
        if(t==3) t=0; else t++;
        __delay_us(10000);
    }
    return;
}
void GPIO_Init()
{
    TRISB = 0x00;
    TRISA0 = 1;
}
void Delay_customer(unsigned int time)
{
    unsigned char x; 
    for(x=0;x<time;x++)
    {
        __delay_us(1);
    }
}
void Timer_Init()
{
    TMR1= 62411;
    //
    T1CKPS1 = 1;
    T1CKPS0 = 1; // chia 8
    T1OSCEN = 0; // tat bo dao dong
    T1SYNC = 0; // dong bo ngo vao xung clock tu ben ngoai
    TMR1CS = 0; //xung noi
    //
    GIE=1; // cho phep ngat toan cuc 
    PEIE=1; // cho phep ngat ngoai vi  
    TMR1IE=1; // cho phep ngat timer1
    //
    TMR1ON = 1; // cho phep bo timer bat dau dem
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
long map(long x, long in_min, long in_max, long out_min, long out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
void __interrupt() MyInterrup()
{
    static short t;
    if(TMR1IE == 1 && TMR1IF == 1)
    {
        switch (t)
        {
            case 0:
            PORTB = full_drive_right[0];
            break;
            case 1:
            PORTB = full_drive_right[1];
            break;
            case 2:
            PORTB = full_drive_right[2];
            break;
            case 3:
            PORTB = full_drive_right[3];
            break;
            default: break;
        }
        if(t==3) t=0; else t++;
      // nap lai cho timer
      TMR1= map(Read_ADC(0),0,1023,0,64911);  
      TMR1IF = 0;
    }
}
