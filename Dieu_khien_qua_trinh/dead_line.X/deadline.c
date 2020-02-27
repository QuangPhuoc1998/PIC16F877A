/*
 * File:   deadline.c
 * Author: Admin
 *
 * Created on September 30, 2019, 8:48 PM
 */


#include "main.h"
#include "lcd_v2.h"

#define STA RC0
#define UP RC1
#define DOWN RC2
#define Led_red RD6
#define Led_gre RD7
// value
unsigned int temp;
int sum = 0, sum_avg = 0;
char m=0,set_temp = 50;
unsigned int duty = 0;
// PID
float E, E1, E2, T;
double a1, a2, a3, Kp, Ki, Kd;
double out, pre_out;
//
void Display(unsigned char temp, unsigned char set_temp);
long map(long x, long in_min, long in_max, long out_min, long out_max);
void ADC_Init();
unsigned int Read_ADC(unsigned char channel);
void Timer1_Init();
void Interrupt_Init();
unsigned int PID_Init(unsigned int nhietdo, unsigned int nhietdodat);
void __interrupt() My_interrupt();
void main(void) 
{
     // gan gia tri bien PID
	T = 0.5;
	Kp = 150;
	Ki = 0.0002151;
	Kd = 0;
	E = E1 = E2 = 0;
	a1 = a2 = a3 = 0;
	out = pre_out = 0;
    // port
    TRISA0 = 1;
    TRISA1 = 1;
    TRISB0 = 1;
    TRISB1 = 0;
    TRISC0 = 1;
    TRISC1 = 1;
    TRISC2 = 1;
    //
    Led_red = 1;
    Led_gre = 1;
    RB1 = 0;
    //
    Lcd_Init();
    ADC_Init();
    Timer1_Init();
    Interrupt_Init();
    //
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("1. TEST MODE");
    Lcd_Set_Cursor(2,1);
    Lcd_Write_String("2. NORMAL MODE");
    while(1)
    {
        if(RC1 == 0) // mode 1
        {
            __delay_ms(10);
            if(RC1 == 0)
            {
                __delay_ms(10);
                while(RC1 == 0);
                // mode1
                mode1:;
                Led_red = 0;
                Led_gre = 1;
                INTE = 1;
                Lcd_Clear();
                Lcd_Set_Cursor(1,1);
                Lcd_Write_String("Temp:    oC");
                Lcd_Set_Cursor(2,1);
                Lcd_Write_String("Duty:     %");
                while(1)
                {
                    temp = Read_ADC(0)*0.488f+0.5f;
                    duty = map(Read_ADC(1),0,1023,0,8000);
                    //
                    sum +=temp;
                    if (m < 9) m++;
                    else  
                    {
                        sum_avg = sum / 10;  
                        sum = 0; 
                        m=0;
                    } 
                    //
                    Lcd_Set_Cursor(1,7);
                    Lcd_Write_Char(sum_avg/10+48);
                    Lcd_Write_Char(sum_avg%10+48); 
                    Lcd_Set_Cursor(2,7);
                    Lcd_Write_Char(map(Read_ADC(1),0,1023,100,0)/100+48);
                    Lcd_Write_Char(map(Read_ADC(1),0,1023,100,0)%100/10+48);
                    Lcd_Write_Char(map(Read_ADC(1),0,1023,100,0)%10+48); 
                    if(RC0 == 0) // mode 2
                    {
                        __delay_ms(10);
                        if(RC0 == 0)
                        {
                            __delay_ms(10);
                            while(RC0 == 0);
                            goto mode2;
                        }
                    }
                    __delay_ms(10);
                }
                // end mode1
            }
        }
        if(RC2 == 0) // mode 2
        {
            __delay_ms(10);
            if(RC2 == 0)
            {
                __delay_ms(10);
                while(RC2 == 0);
                mode2:;
                // mode 2
                INTE = 1;
                Led_red = 1;
                Led_gre = 0;
                Lcd_Clear();
                Lcd_Set_Cursor(1,1);
                Lcd_Write_String("Temp:    oC");
                Lcd_Set_Cursor(2,1);
                Lcd_Write_String("Set temp:    oC");
                while(1)
                {
                    temp = Read_ADC(0)*0.488f+0.5f;
                    duty = PID_Init(temp, set_temp);
                    //
                    sum +=temp;
                    if (m < 9) m++;
                    else  
                    {
                    sum_avg = sum / 10;  
                    sum = 0; 
                    m=0;
                    } 
                    //
                    if(UP==0 && set_temp < 80)
                    {
                        __delay_ms(10);
                        if(UP==0 && set_temp < 80)
                        {
                            __delay_ms(10);
                            if(UP==0 && set_temp < 80)
                                while(UP==0 && set_temp < 80)
                                {
                                    set_temp++;
                                    Display(sum_avg,set_temp);
                                    __delay_ms(250);
                                }  
                        }
                    }
                    if(DOWN==0 && set_temp > 40)
                    {
                        __delay_ms(10);
                        if(DOWN==0 && set_temp > 40)
                        {
                            __delay_ms(10);
                            if(DOWN==0 && set_temp > 40)
                            {
                                while(DOWN==0 && set_temp > 40)
                                {
                                    set_temp--;
                                    Display(sum_avg,set_temp);
                                    __delay_ms(250);
                                }
                            }
                        }
                    }
                    if(RC0 == 0) // mode 2
                    {
                        __delay_ms(10);
                        if(RC0 == 0)
                        {
                            __delay_ms(10);
                            while(RC0 == 0);
                            goto mode1;
                        }
                    }
                    //
                    if(RC0 == 0) // mode 2
                    {
                        __delay_ms(10);
                        if(RC0 == 0)
                        {
                            __delay_ms(10);
                            while(RC0 == 0);
                            goto mode1;
                        }
                    }
                    //
                    Display(sum_avg,set_temp);
                    __delay_ms(10);
                    //
                }   
            }
        }
    }
    return;
}
void Display(unsigned char a, unsigned char b)
{
    Lcd_Set_Cursor(1,7);
    Lcd_Write_Char(a/10+48);
    Lcd_Write_Char(a%10+48);
    //
    Lcd_Set_Cursor(2,11);
    Lcd_Write_Char(b%100/10+48);
    Lcd_Write_Char(b%10+48);
}
long map(long x, long in_min, long in_max, long out_min, long out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
void ADC_Init()
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
void Timer1_Init()
{
    TMR1H=0x00;    // delay 1ms
    TMR1L=0x00;
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
void Interrupt_Init()
{
    TRISB0 = 1;
    // cau hinh ngat ngoai
    INTEDG = 1; // ngat canh len
    // cau hinh ngat
    GIE = 1; // ngat toan cuc
    PEIE = 1; // ngat ngoai vi
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
	return 6500-out;
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
        TMR1= 65535-(500+duty)/0.2f;    // delay
        TMR1IF = 0; 
        //        
        RB1 = 1;
        INTF = 0;
    }
}
