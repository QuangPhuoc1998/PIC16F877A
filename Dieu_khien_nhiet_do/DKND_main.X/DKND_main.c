/*
 * File:   DKND.c
 * Author: ADMIN
 *
 * Created on 31 March 2019, 23:44
 */


#include "main.h"
#include "lcd4.h"
// bien toan phan
unsigned int time;
// khai bao bien PID
double E, E1, E2, T;
double P, I, D, beta, gamma, Kp, Ki, Kd;
double out, pre_out;
//*******************************
void ADC_Init(unsigned char channel);
unsigned int Read_ADC(unsigned char channel);
void Timer1_Init();
void Interrupt_Init();
void __interrupt() My_interrupt();
unsigned int PID_Init(unsigned int temp, unsigned int set_temp);
void main(void)
{
    // gan gia tri bien PID
    T = 0.5;
    Kp = 17;
    Ki = 0.05;
    Kd = 0.05;
    E = E1 = E2 = 0;
    P = I = D = 0;
    out = pre_out = 0;
    // khai bao bien
    unsigned int buffer;
    unsigned int a, set_temp, temp;
    set_temp = 60;
    // cau hinh port
    TRISD = 0x00;
    PORTD = 0;
    TRISC0 = 0;
    TRISB7 = 0;
    // chuong trinh con
    ADC_Init(1);
    Lcd_Init();
    Timer1_Init();
    Interrupt_Init();
    // begin
    Lcd_Write_String("Nhiet do dat: ");
    Lcd_Set_Cursor(2,1);
    Lcd_Write_String("Nhiet do: ");
    while(1)
    {
        a = Read_ADC(0);
        temp = 0.488f*a + 0.5f;
        time = 65536-(1000+buffer)/(8*0.2f);
        
        
        // nhiet do dat
        Lcd_Set_Cursor(1,15);
        Lcd_Write_Char(set_temp/10+48);
        Lcd_Write_Char(set_temp%10+48);
        // nhiet do do duoc
        Lcd_Set_Cursor(2,11);
        Lcd_Write_Char(temp/10+48);
        Lcd_Write_Char(temp%10+48);
        buffer = PID_Init(temp, set_temp);
        __delay_ms(500);
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
    if(channel > 3) return 0;
    ADCON0 |= channel << 3;
    __delay_us(10);
    GO_nDONE = 1;
    while(GO_nDONE);
    N = ADRESH;
    return ((N<<8)+ADRESL);   
}
void Timer1_Init()
{
    TMR1H=0x0;    // delay 1ms
    TMR1L=0x0;
    //
    T1CKPS1 = 1;
    T1CKPS0 = 1; // chia 8
    T1OSCEN = 0; // tat bo dao dong
    T1SYNC = 0; // dong bo ngo vao xung clock tu ben ngoai
    TMR1CS = 0; //xung noi
    //
    TMR1IE = 0; // ko cho phep ngat timer1
    //
    TMR1ON = 0; // chua cho phep bo timer bat dau dem
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
void __interrupt() My_interrupt()
{
    if(INTE == 1 && INTF == 1)
    {
        RC0 = 0;
        //
        TMR1ON = 1;
        while(TMR1IF==0);
        TMR1ON = 0;
        TMR1= time;    // delay 1ms
        TMR1IF = 0;
        //        
        RC0 = 1;
        INTF = 0;
    }
}
unsigned int PID_Init(unsigned int temp, unsigned int set_temp)
{
    E = set_temp-temp;
    P = Kp*(E - E1);
    I = 0.5*Ki*T*(E + E1);
    D = (Kd*( E - 2*E1+ E2))/T;
    out = pre_out + P + I + D ;
    pre_out = out;
    E2 = E1;
    E1 = E;
    if(out > 6000) out = 6000;
    if(out < 0) out = 0;
    return out;
}
