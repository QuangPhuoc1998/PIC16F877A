/*
 * File:   Joystick.c
 * Author: ADMIN
 *
 * Created on 25 April 2019, 10:12
 */


#include "main.h"
#include "lcd4.h"

void ADC_Init();
unsigned int Read_ADC(unsigned char channel);
void Lcd_Display(unsigned int x_value, unsigned int y_value);
void main(void) 
{
    // bien
    unsigned int a;
    unsigned int x_value, y_value;
    // port
    TRISD = 0x00;
    TRISA = 0xFF;
    // chuong trinh con
    Lcd_Init();
    ADC_Init();
    // begin
    Lcd_Write_String("x_value = ");
    Lcd_Set_Cursor(2,1);
    Lcd_Write_String("y_value = ");
    while(1)
    {
      a = Read_ADC(0);
      x_value = a;
      __delay_us(100);
      a = Read_ADC(1);
      y_value = a;
      Lcd_Display(x_value, y_value);    
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
void Lcd_Display(unsigned int x_value, unsigned int y_value)
{
    Lcd_Set_Cursor(1, 11);
    Lcd_Write_Char(x_value/1000+48);
    Lcd_Write_Char(x_value%1000/100+48);
    Lcd_Write_Char(x_value%100/10+48);
    Lcd_Write_Char(x_value%10+48);
    
    Lcd_Set_Cursor(2, 11);
    Lcd_Write_Char(y_value/1000+48);
    Lcd_Write_Char(y_value%1000/100+48);
    Lcd_Write_Char(y_value%100/10+48);
    Lcd_Write_Char(y_value%10+48);
}