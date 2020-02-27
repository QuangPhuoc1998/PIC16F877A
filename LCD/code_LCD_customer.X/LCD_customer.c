/*
 * File:   LCD_customer.c
 * Author: Admin
 *
 * Created on August 3, 2019, 9:48 AM
 */


#include "main.h"
#include "lcd4.h"

void main(void) 
{
    // value
    char  i;
    //
    Lcd_Set_Port('D');
    Lcd_Init();
    while(1)
    {
        for(i=1;i<17;i++)
        {
        Lcd_Set_Cursor(1,i);
        Lcd_Write_Char(1); // 
        if(i==1); else Lcd_Set_Cursor(1,i-1);
        Lcd_Write_Char(' '); // Display Custom Character 0
        __delay_ms(100);
        if(i==16); else Lcd_Set_Cursor(1,i);
        Lcd_Write_Char(' ');
        }
    }
    return;
}
