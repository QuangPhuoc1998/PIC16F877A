/*
 * File:   spi2.c
 * Author: ADMIN
 *
 * Created on 27 April 2019, 10:48
 */


#include "main.h"
#include "spi.h"
#include "lcd4.h"

unsigned char s;
char data[8];
unsigned int x = 0, y = 0;
void Lcd_Display(unsigned int x, unsigned int y);
void main(void) 
{
    
    // port
    TRISB = 0x00;
    // chuong trinh con
    Spi_Init(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
    Lcd_Init();
    // interrup
    GIE = 1;
    PEIE = 1;
    SSPIE = 1;
    // begin
    Lcd_Write_String("x_value = ");
    Lcd_Set_Cursor(2,1);
    Lcd_Write_String("x_value = ");
    while(1)
    {
        Lcd_Display(x,y);
    }
    return;
}
void Lcd_Display(unsigned int x, unsigned int y)
{
    Lcd_Set_Cursor(1,11);
    Lcd_Write_Char(x/1000+48);
    Lcd_Write_Char(x%1000/100+48);
    Lcd_Write_Char(x%100/10+48);
    Lcd_Write_Char(x%10+48);
    Lcd_Set_Cursor(2,11);
    Lcd_Write_Char(y/1000+48);
    Lcd_Write_Char(y%1000/100+48);
    Lcd_Write_Char(y%100/10+48);
    Lcd_Write_Char(y%10+48);
}
void __interrupt() My_interrupt()
{
    if(SSPIE == 1 && SSPIF == 1)
    {
        s = Spi_Read();
        if(s == ':') 
        {
            Spi_Read_Text(data, 8);
            x = data[0]*1000+data[1]*100+data[2]*10+data[3];
            y = data[4]*1000+data[5]*100+data[6]*10+data[7];
        }
        SSPIF = 0;
    }
}