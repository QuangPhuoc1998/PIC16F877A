/*
 * File:   PWM.c
 * Author: ADMIN
 *
 * Created on 27 March 2019, 18:51
 */


#include "main.h"
#include "lcd4.h"
#define DIR RD7
// khai bao bien PID
double E, E1, E2, T;
double a1, a2, a3, beta, gamma, Kp, Ki, Kd;
double out, pre_out, chot;
// capture
void Timer1_Init();
void Capture_Init();
// PWM
void PWM_Init(unsigned int period);
void Duty_Init(unsigned int duty);
// PID
void PID_Init(unsigned int tocdo, unsigned int tocdodat);
// main
void main(void)
{ 
    // gan gia tri bien PID
    T = 0.01;
    Kp = 16.625;
    Ki = 0.25;
    Kd = 0;
    E = E1 = E2 = 0;
    a1 = a2 = a3 = 0;
    out = pre_out = 0;
    // khai bao bien
    unsigned int buffer;
    unsigned int t;
    // cau hinh port
    TRISD = 0x00;
    //cau hinh PWM
    unsigned int period = 255;
    PWM_Init(period);
    Duty_Init(0); 
    Timer1_Init();
    Capture_Init();
    Lcd_Init();
    Lcd_Write_String("Gia tri: ");
    Lcd_Set_Cursor(2,1);
    Lcd_Write_String("Toc do: ");
    DIR = 1;
    while(1)
    { 
      buffer = CCPR2;
      t = 60000000/(buffer*0.2f*8*24);
      // hien thi gia tri CCPR2
      Lcd_Set_Cursor(1,10);
      Lcd_Write_Char(buffer/10000+48);
      Lcd_Write_Char((buffer%10000)/1000+48);
      Lcd_Write_Char((buffer%1000)/100+48);
      Lcd_Write_Char((buffer%100)/10+48);
      Lcd_Write_Char(buffer%10+48);
      
      // hien thi toc do
      Lcd_Set_Cursor(2,9);
      Lcd_Write_Char(t/10000+48);
      Lcd_Write_Char((t%10000)/1000+48);
      Lcd_Write_Char((t%1000)/100+48);
      Lcd_Write_Char((t%100)/10+48);
      Lcd_Write_Char(t%10+48);
      PID_Init(t, 100);
      __delay_ms(10);
    }
    return;
}
void PWM_Init(unsigned int period)
{ 
    // thanh ghi PR2
    PR2 = period; // 256
    // thanh ghi CCP1CON
    CCP1M3 = 1; 
    CCP1M2 = 1; // che do PWM
    // pin CCP1
    TRISC2 = 0;
    /*-----------------------------------*/
    // thanh ghi TMR2
    TMR2 = 0;
    // thanh ghi T2CON
    TOUTPS3 = 0;
    TOUTPS2 = 0; // 1:1 postscale
    TOUTPS1 = 0;
    TOUTPS0 = 0;
    T2CKPS1 = 1; // pre = 16
    T2CKPS0 = 0;
    // timer2 bat dau hoat dong
    TMR2ON = 1;
}
void Duty_Init(unsigned int duty)
{  
    
  CCP1X = 1; // gan bit cho CCP1X
  CCP1Y = 0; // gan bit cho CCP1Y
  CCPR1L = duty; // gan gia tri cho CCPR1L
}
void Timer1_Init()
{
    TMR1 = 0;
    // chia 8
    T1CKPS1 = 1;
    T1CKPS0 = 1;
    // bat ngat
    GIE = 1;
    PEIE = 1;
    TMR1IE = 0;
    // khoi dong
    TMR1ON = 1;
}
void Capture_Init()
{
    TRISC1 = 1; // ccp2
    CCPR2 = 0;
    CCP2IE = 1;
    CCP2M3 = 0;
    CCP2M2 = 1; // capture canh len
    CCP2M1 = 0;
    CCP2M0 = 1;
}
void __interrupt() My_interrupt()
{
    if(CCP2IE == 1 && CCP2IF == 1)
    {
        TMR1 = 0;
        CCP2IF = 0;
    }
}
void PID_Init(unsigned int tocdo, unsigned int tocdodat)
{
    E = tocdodat-tocdo;
    a1 = Kp + (Ki*T)/2 + Kd/2;
    a2 = -Kp + (Ki*T)/2 - 2*Kd/T;
    a3 = Kd/T;
    out = pre_out + E*a1 + E1*a2 + E2*a3;
    pre_out = out;
    E2 = E1;
    E1 = E;
    if(out > 255) out = 255;
    if(out < 0) out = 0;
    Duty_Init(out);
}