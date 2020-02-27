#include "main.h"

unsigned int t = 0;
void __interrupt() My_interrupt();
void main()
{
    // cau hinh port
    TRISD6 = 0;
    RD6 = 0;
    // cau hinh timer0
    OPTION_REG = 0x06; //0000 0101 : Fosc/64
    TMR0 = 217;
    TMR0IE=1;       //Enable timer interrupt bit in PIE1 register
    GIE=1;          //Enable Global Interrupt
    PEIE=1;         //Enable the Peripheral Interrupt
    // chuong trinh chinh
    while(1)
    {
        
    }
    return;
}
void __interrupt() My_interrupt()
{
    if(TMR0IF == 1 && TMR0IE == 1 )
    {
      t++;
      if(t==500)
      {
        RD6 = !RD6;
        t=0;
      }
      TMR0 = 217; 
      TMR0IF = 0;
    }
}