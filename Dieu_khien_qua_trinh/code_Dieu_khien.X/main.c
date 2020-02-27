#include "main.h"
#include "lcd4.h"
//
#define STA RC0
#define UP RC1
#define DOWN RC2
#define Led_red RD6
#define Led_gre RD7

unsigned int t, duty;
//
double E, E1, E2, T;
double a1, a2, a3, Kp, Ki, Kd;
double out, pre_out;
//
void Timer1_Init();
void delay_customer(unsigned int t);
void Display(unsigned char temp, unsigned char set_temp);
void ADC_Init();
unsigned int Read_ADC(unsigned char channel);
void Interrupt_Init();
void __interrupt() My_interrupt();
long map(long x, long in_min, long in_max, long out_min, long out_max);
unsigned int PID_Init(unsigned int nhietdo, unsigned int nhietdodat);
void Set_temp();
void main(void) 
{
    // gan gia tri bien PID
	T = 0.5;
	Kp = 300;
	Ki = 0;
	Kd = 0;
	E = E1 = E2 = 0;
	a1 = a2 = a3 = 0;
	out = pre_out = 0;
    //
    TRISA0 = 1;
    TRISB1 = 0;
    TRISC0 = 1;
    TRISC1 = 1;
    TRISC2 = 1;
    //
    Lcd_Set_Port('D');
    Lcd_Init();
    ADC_Init();
    Interrupt_Init();
    Timer1_Init();
    //
    Lcd_Write_String("hello tml");
    while(1)
    {
        if(STA==0)
        {
            __delay_ms(10);
            if(STA==0)
            {
                __delay_ms(10);
                if(STA==0)
                {
                    __delay_ms(10);
                    if(STA==0)
                    {
                        while(STA==0);
                        Set_temp();
                    }
                }
            }
        }
        __delay_ms(10);
    }
    return;
}
void Timer1_Init()
{
    TMR1H=0x00;    // delay 1ms
    TMR1L=0x00;
    //
    T1CKPS1 = 0;
    T1CKPS0 = 0; // chia 8
    T1OSCEN = 0; // tat bo dao dong
    T1SYNC = 0; // dong bo ngo vao xung clock tu ben ngoai
    TMR1CS = 0; //xung noi
    //
    TMR1IE = 0; // ko cho phep ngat timer1
    //
    TMR1ON = 0; // chua cho phep bo timer bat dau dem
}
void Display(unsigned char temp, unsigned char set_temp)
{
    Lcd_Set_Cursor(1,11);

    Lcd_Write_Char(temp/10+48);
    Lcd_Write_Char(temp%10+48);
    //
    Lcd_Set_Cursor(2,15);
    Lcd_Write_Char(set_temp%100/10+48);
    Lcd_Write_Char(set_temp%10+48);
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
    if(channel > 3) return 0;
    ADCON0 |= channel << 3;
    __delay_us(10);
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
}
long map(long x, long in_min, long in_max, long out_min, long out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
unsigned int PID_Init(unsigned int nhietdo, unsigned int nhietdodat)
{
	E = nhietdodat-nhietdo;
    if(E<0) return 8000;
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
void Set_temp()
{
    here:
    Lcd_Clear();
    Led_red = 0;
    Led_gre = 1;
    //
    unsigned char set_temp = 60;
    //
    INTE = 0; // cho phep ngat ngoai
    __delay_ms(10);
    RB1 = 0;
    //
    Lcd_Write_String("Nhiet do: ");
    Lcd_Set_Cursor(2,0);
    Lcd_Write_String("NNhiet do dat: ");
    while(1)
    {
        t = Read_ADC(0)*0.488f+0.5f;
        if(UP==0 && set_temp < 99)
        {
            __delay_ms(10);
            if(UP==0 && set_temp < 99)
            {
                __delay_ms(10);
                if(UP==0 && set_temp < 99)
                    while(UP==0 && set_temp < 99)
                    {
                        set_temp++;
                        Display(t,set_temp);
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
                        Display(t,set_temp);
                        __delay_ms(250);
                    }
                }
            }
        }
        if(STA == 0)
        {
            __delay_ms(10);
            if(STA==0)
            {
                __delay_ms(10);
                if(STA==0)
                {
                    __delay_ms(10);
                    if(STA==0)
                    {
                        while(STA == 0);
                        Led_red = 1;
                        Led_gre = 0;
                        INTE = 1; // cho phep ngat ngoai
                        __delay_ms(10);
                        while(1)
                        {
                            t = Read_ADC(0)*0.488f+0.5f;
                            duty = PID_Init(t,set_temp);
                            if(STA == 0)
                            {
                                while(STA == 0);
                                goto here;
                            } 
                            Display(t,set_temp);
                            __delay_ms(50);
                            if(STA == 0)
                            {
                                while(STA == 0);
                                goto here;
                            }
                            __delay_ms(50);
                        }
                    }
                }
            }
        }
        Display(t,set_temp);
        __delay_ms(10);
    }
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
        TMR1= 65536-(1000+duty)/0.2f;    // delay
        TMR1IF = 0; 
        //        
        RB1 = 1;
        INTF = 0;
    }
}



