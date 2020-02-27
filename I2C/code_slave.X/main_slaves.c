/*
 * File:   main.c
 * Author: Admin
 *
 * Created on July 27, 2019, 9:28 PM
 */


#include "main.h"
#include "I2C.h"

unsigned char code7seg[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
unsigned char data;
unsigned char key = 0;
void Led7_display(unsigned char number);
void main(void)
{
    unsigned char number,i;
    // port
    TRISB0 = 0;
    TRISB1 = 0;
    TRISD = 0x00;
    //
    PORTD = 0xFF;
    // chuong trinh con
    I2C_Slave_Init(0x30);
    while(1)
    {
        stop:
        if(key == 1)
        {
            key = 0;
            for(number=number;number<30;number++)
            {
                for(i=0;i<50;i++)
                {
                    Led7_display(number);
                    if(key == 2) 
                    {
                        goto stop;
                        key = 0;
                    }
                    if(key == 3) 
                    {
                        goto stop;
                        number = 0;
                        key = 0;
                    }
                    __delay_ms(10);
                }
            }
        }
        Led7_display(number);
        if(number == 30 || key == 3) 
        {
            number = 0;
            key = 0;
        }
         __delay_ms(10);
    }
    return;
}
void Led7_display(unsigned char number)
{
    RB1 = 0;
    PORTD = code7seg[number/10];
    __delay_ms(5);
    RB1 = 1;
    //
    RB0 = 0;
    PORTD = code7seg[number%10];
    __delay_ms(5);
    RB0 = 1;
}
void __interrupt() i2c_slave_read()
{
  if(SSPIF == 1)
  {
    CKP = 0;

    if ((SSPOV) || (WCOL))
    {
      data = SSPBUF; 
      SSPOV = 0; 
      WCOL = 0; 
      CKP = 1;
    }
  }

  if(!D_nA && !R_nW) 
  {
    data = SSPBUF;
    while(!BF);
    if(SSPBUF == 0x01) key = 1;
    if(SSPBUF == 0x02) key = 2;
    if(SSPBUF == 0x03) key = 3;
    CKP = 1;
  }
  else if(!D_nA && R_nW) 
  {
    data = SSPBUF;
    BF = 0;
    SSPBUF = PORTB ;
    CKP = 1;
    while(BF);
  }

  SSPIF = 0;
  }