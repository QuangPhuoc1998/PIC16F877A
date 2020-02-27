/*
 * File:   ngat_ngoai.c
 * Author: ADMIN
 *
 * Created on 25 March 2019, 13:58
 */


#include "main.h"

void main(void) 
{
    TRISB0 = 1;
    TRISD0 = 0;
    RD0 = 0;
    // cau hinh ngat ngoai
    INTEDG = 1; // ngat canh len
    // cau hinh ngat
    GIE = 1; // ngat toan cuc
    PEIE = 1; // ngat ngoai vi
    INTE = 1; // cho phep ngat ngoai
    // test PIC
    
    while(1)
    {
      RD0 = 1;
      __delay_ms(5000);
      RD0 = 0;
      __delay_ms(5000);   
    }
    return;
}
//void __interrupt() My_interrupt()
//{
//    if(INTE == 1 && INTF == 1)
//    {
//    RD0 = 0;
//    __delay_us(5000);
//    RD0 = 1;
//    INTF = 0;
//    }
//}

