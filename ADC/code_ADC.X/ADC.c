#include "main.h"
#include "lcd4.h"
#include "USART.h"

// bien toan phan
unsigned int time = 65536-(1000+18000)/(8*0.2f);
// khai bao bien PID
double E, E1, E2, T;
double a1, a2, a3, beta, gamma, Kp, Ki, Kd;
double out, pre_out, chot;

void ADC_Init(unsigned char channel);
unsigned int Read_ADC(unsigned char channel);
void Interrupt_Init();
void Timer1_Init();
void __interrupt() My_interrupt();
void PID_Init(unsigned int nhietdo, unsigned int nhietdodat);


void main()
{
    __delay_ms(250);
    // PID
    // gan gia tri bien PID
    T = 0.5;
    Kp = 30;
    Ki = 0.01;
    Kd = 0;
    E = E1 = E2 = 0;
    a1 = a2 = a3 = 0;
    out = pre_out = 0;
    // bien
    unsigned int a;
    unsigned int t;
    unsigned char start;
    unsigned char buffer[2];
    unsigned int t_load = 0;
    unsigned int _t_load;
    // port
    TRISD = 0x00;
    TRISC0 = 0;
    TRISB0 = 1;
    TRISB7 = 0;
    // khoi tao
    ADC_Init(1); // khoi tao ADC
    // thu vien con
    UART_Init(9600);
    Lcd_Init();
    Timer1_Init();
    Interrupt_Init();
    // chuong trinh chinh
    Lcd_Write_String("Temp load: ");
    Lcd_Set_Cursor(2,1);
    Lcd_Write_String("Temp: ");
    while(1)
    {
    while(1)
    {
       start = UART_Read();
       if(start == 's') break;
       else
           if(t_load == 0)
           {
           UART_Read_Text(buffer, 2);
           }
       t_load = (buffer[1]-0x30)*10 + (buffer[0]-0x30);
       _t_load = t_load;
       Lcd_Set_Cursor(1,12);
       Lcd_Write_Char(t_load/10 + 48);
       Lcd_Write_Char(t_load%10 + 48);
    }
    while(1)
    {
        a = Read_ADC(0);
        t = a*0.48828f;
        // hien thi gia tri
        Lcd_Set_Cursor(1,12);
        Lcd_Write_Char(t_load/100+48);
        Lcd_Write_Char((t_load%100)/10+48);
        Lcd_Write_Char(t_load%10+48);
        // hien thi nhiet do
        Lcd_Set_Cursor(2,7);
        Lcd_Write_Char(t/100+48);
        Lcd_Write_Char((t%100)/10+48);
        Lcd_Write_Char(t%10+48);
        // send to serial port
        PID_Init(t, t_load);
        UART_Write(t);
        if(t > t_load) RB7 = 0;
        else RB7 = 1;
        __delay_ms(500);
    }
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
        TMR1= time;    // delay
        TMR1IF = 0;
        //        
        RC0 = 1;
        INTF = 0;
    }
}
void PID_Init(unsigned int nhietdo, unsigned int nhietdodat)
{
    E = nhietdodat-nhietdo;
    a1 = Kp + (Ki*T)/2 + Kd/2;
    a2 = -Kp + (Ki*T)/2 - 2*Kd/T;
    a3 = Kd/T;
    out = pre_out + E*a1 + E1*a2 + E2*a3;
    pre_out = out;
    E2 = E1;
    E1 = E;
    chot = 6000 - out;
    if(chot < 0) chot = 0;
    time = 65536-(1000+chot)/(8*0.2f);
}

