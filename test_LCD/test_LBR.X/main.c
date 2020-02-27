/*
 * File:   main.c
 * Author: ADMIN
 *
 * Created on 05 March 2019, 22:49
 */


#include "main.h"
#include "lcd4.h"

void main(void) 
{
    TRISD = 0x00;
    Lcd_Init();
    Lcd_Write_String("Phuoc dep trai");
    while(1)
    {
        __delay_ms(1000);
    }
    return;
}
