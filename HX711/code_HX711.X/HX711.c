/*
 * File:   HX744.c
 * Author: Admin
 *
 * Created on August 9, 2019, 8:57 AM
 */


#include "main.h"
#include "I2C_LCD_v2.h"
#include "I2C_Master_File.h"

#define CLK RB7
#define Da RB6
signed long int ReadCount()        /* Function to read measurement from HX711 */
{
    signed long int Count;  
    unsigned char i;
    Da=1; 
    CLK = 0;                     /* Clear Clock line to start conversion */
    Count = 0;
    while (Da);      /* Wait for measurement conversion. */
    for (i=0; i<24; i++)
    {
        CLK = 1;           /* Clock signal High */
        Count = Count << 1;       /* Shift value left */
        __delay_us(10);
        CLK = 0;            /* Clock signal Low */
        if(Da) Count++; 
        __delay_us(10);
    }
    CLK = 1;
    Count=Count^0x800000;
    __delay_us(10);
    CLK = 0;
    return Count;
}
void main(void) 
{
    //
    signed long int data;
    char buffer[20];
    //
    TRISB7 = 0;
    TRISB6 = 1;
    I2C_Init(); 
    Lcd_Init ();
    Lcd_Write_String("Gia tri: ");
    Lcd_Set_Cursor(2,7);
    Lcd_Write_String("Gram");
    while(1)
    {
        
        data = ReadCount();
        data = (data - 8273000)/4.0768f;
        if(data < 0) data = 0;
        Lcd_Set_Cursor(2,1);
        Lcd_Write_Char(data/1000000+48);
        Lcd_Write_Char(data%1000000/100000+48);
        Lcd_Write_Char(data%100000/10000+48);
        Lcd_Write_Char(data%10000/1000+48);
        Lcd_Write_Char(data%1000/100+48);
        
        
        __delay_ms(500);
    }
    return;
}
