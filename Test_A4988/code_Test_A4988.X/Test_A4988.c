#include "main.h"
#include "lcd4.h"

unsigned int buffer;
// global variable
char m;
unsigned int a;
unsigned long int speed, sum;
unsigned int x = 0, t = 0;
//
void ADC_Init();
unsigned int Read_ADC(unsigned char channel);
void Lcd_Display(unsigned int speed_feed,unsigned int speed);
void Timer0_Init();
void Timer1_Init();
void Capture_Init();
long map(long x, long in_min, long in_max, long out_min, long out_max);
void main(void) 
{
    // port
    TRISA0 = 1;
    TRISC7 = 0;
    //
    Lcd_Set_Port('D');
    Lcd_Init();
    ADC_Init();
    Timer0_Init();
    Timer1_Init();
    Capture_Init();
    //
    Lcd_Write_String("feed:      rpm");
    Lcd_Set_Cursor(2,1);
    Lcd_Write_String("Toc do:     rpm");
    while(1)
    {
        a = Read_ADC(0);
        if (a>1020) 
        {
            TMR0IE = 0;
            speed = 0;
        } 
        else 
        {
            TMR0IE = 1;
            buffer = map(a,0,1023, 242, 0);
            speed = 60000000/((256-buffer)*0.2f*2*256*200);
        }
        //
        x = CCPR1;
        sum +=(60000000/(x*0.2f*8*40));
		if (m < 40) m++;
		else {
			t = sum / 40;  
			sum = 0; 
			m=0;
		}
        if(speed <= 116) t = 0;
        //
        Lcd_Display(t,speed);
        __delay_ms(10);
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
void Lcd_Display(unsigned int speed_feel,unsigned int speed)
{
    Lcd_Set_Cursor(1,7);
    if(speed_feel == 0)
    {
        Lcd_Write_String("ERRO");
    }
    else
    {
        Lcd_Write_Char(speed_feel/100+48);
        Lcd_Write_Char(speed_feel%100/10+48);
        Lcd_Write_Char(speed_feel%10+48);
        Lcd_Write_Char(' ');
    }
    //
    Lcd_Set_Cursor(2,9);
    Lcd_Write_Char(speed/100+48);
    Lcd_Write_Char(speed%100/10+48);
    Lcd_Write_Char(speed%10+48);
}
void Timer0_Init()
{
    OPTION_REG = 0x07; //0000 0111 : Fosc/256
    TMR0 = 0;
    TMR0IE=1;       //Enable timer interrupt bit in PIE1 register
    GIE=1;          //Enable Global Interrupt
    PEIE=1;         //Enable the Peripheral Interrupt
}
void Timer1_Init()
{
    // cai dat gia tri thanh ghi TMR1
    TMR1 = 0;
    // cai dat thanh ghi T1CON
    T1CKPS1 = 1;
    T1CKPS0 = 1; // chia 8
    T1OSCEN = 0;
    T1SYNC = 0;
    TMR1CS = 0;
    // cau hinh ngat
    GIE = 1;
    PEIE = 1;
    TMR1IE = 0; // tat ngat timer1
    // bat dau timer1
    TMR1ON = 1;
}
void Capture_Init()
{
    TRISC2 = 1;
    // cau hinh thanh ghi CCPR1
    CCPR1 = 0;
    // cau hinh ngat
    CCP1IE = 1;
    // cau hinh thanh ghi CCP1CON
    CCP1M3 = 0;
    CCP1M2 = 1; // canh len
    CCP1M1 = 0;
    CCP1M0 = 1;
}
void __interrupt() MyInterrup()
{
    if(CCP1IE == 1 && CCP1IF == 1)
    {
        TMR1 = 0;
        CCP1IF = 0;
    }
    if(TMR0IF == 1 && TMR0IE == 1 )
    {     
      RC7 = !RC7;
      TMR0 = buffer; 
      TMR0IF = 0;
    }
}
long map(long x, long in_min, long in_max, long out_min, long out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
