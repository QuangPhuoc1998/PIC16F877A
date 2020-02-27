/*
 * File:   DKND.c
 * Author: ADMIN
 *
 * Created on 31 March 2019, 23:44
 */


#include "main.h"
#include "lcd4.h"


// bien toan phan
unsigned int time = 65536-(1000+8000)/(0.2f);
//
double E, E1, E2, T;
double a1, a2, a3, Kp, Ki, Kd;
double out, pre_out;
//
void delay_customer(unsigned int t);
void ADC_Init(unsigned char channel);
unsigned int Read_ADC(unsigned char channel);
void Interrupt_Init();
void Timer1_Init();
long map(long x, long in_min, long in_max, long out_min, long out_max);
unsigned int PID_Init(unsigned int nhietdo, unsigned int nhietdodat);
void __interrupt() My_interrupt();
void main(void)
{
    // gan gia tri bien PID
	T = 0.5;
	Kp = 100;
	Ki = 0;
	Kd = 0;
	E = E1 = E2 = 0;
	a1 = a2 = a3 = 0;
	out = pre_out = 0;
    //
    // khai bao bien
    unsigned int a;
    char m=0,temp = 0;
    float sum = 0;
    // cau hinh port
    TRISD = 0x00;
    PORTD = 0;
    RD6 = 1;
    RD7 = 1;
    TRISB1 = 0;
    TRISB0 = 1;
    TRISA0 = 1;
    TRISA1 = 1;
    // chuong trinh con
    ADC_Init(1);
    Lcd_Init();
    __delay_ms(100);
    Interrupt_Init();
    // begin
    Lcd_Write_String("Nhiet do: ");
    
    while(1)
    {
        temp = Read_ADC(0)*0.488f+0.5f;
        time = PID_Init(temp,90);
        Lcd_Set_Cursor(1,11);
        Lcd_Write_Char(temp/100+48);
        Lcd_Write_Char(temp/10+48);
        Lcd_Write_Char(temp%10+48);
        __delay_ms(500);
    }
    return;
}
void delay_customer(unsigned int t)
{
	for(int i=0;i<t;i++);
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
    ADCON0 &= 0x11000101;
    if(channel > 3) return 0;
    ADCON0 |= channel << 3;
    __delay_ms(2);
    GO_nDONE = 1;
    while(GO_nDONE);
    N = ADRESH;
    return ((N<<8)+ADRESL);   
}
void Interrupt_Init()
{
    TRISB0 = 1;
    // cau hinh ngat ngoai
    INTEDG = 1; // ngat canh len
    // cau hinh ngat
    GIE = 1; // ngat toan cuc
    PEIE = 1; // ngat ngoai vi
    INTE = 1; // cho phep ngat ngoai
}
void Timer1_Init()
{
    TMR1 = 0;    // delay 1ms
    //
    T1CKPS1 = 0;
    T1CKPS0 = 0; // chia 1
    T1OSCEN = 0; // tat bo dao dong
    T1SYNC = 0; // dong bo ngo vao xung clock tu ben ngoai
    TMR1CS = 0; //xung noi
    //
    TMR1IE = 0; // ko cho phep ngat timer1
    //
    TMR1ON = 0; // chua cho phep bo timer bat dau dem
}
long map(long x, long in_min, long in_max, long out_min, long out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
unsigned int PID_Init(unsigned int nhietdo, unsigned int nhietdodat)
{
	E = nhietdodat-nhietdo;
	a1 = Kp + (Ki*T)/2 + Kd/2;
	a2 = -Kp + (Ki*T)/2 - 2*Kd/T;
	a3 = Kd/T;
	out = pre_out + E*a1 + E1*a2 + E2*a3;
	pre_out = out;
	E2 = E1;
	E1 = E;
    if(out<0) out = 0;
    if(out>=8000) out = 8000;
	return 8000-out;
}
void __interrupt() My_interrupt()
{
    if(INTE == 1 && INTF == 1)
    {
        RB1 = 0;
        //
        TMR1ON = 1;
        while(TMR1IF==0);
        TMR1ON = 0;
        TMR1= 65536-(1000+time)/0.2f;    // delay
        TMR1IF = 0; 
        //        
        RB1 = 1;
        INTF = 0;
    }
}
