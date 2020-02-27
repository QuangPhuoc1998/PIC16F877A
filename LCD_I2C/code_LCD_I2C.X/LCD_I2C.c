/*
 * File:   newmain.c
 * Author: omar
 *
 * Created on 23 August, 2018, 12:03 PM
 */
#include "main.h"
#include <stdint.h>
#include "I2C_LCD.h"
#include "I2C_Master_File.h"
#include "DS1307.h"

unsigned int time[7];
void DS1307_Read_Time();
void main(void) {
    
    // initialise I2C at 100 KHz
    I2C_Init();
    Lcd_Init();
    // send string to LCD
    while (1)
    {
        DS1307_Read_Time();
        
        Lcd_Set_Cursor(1,5);
        Lcd_Write_Char(time[2]/10+48);
        Lcd_Write_Char(time[2]%10+48);
        Lcd_Write_Char(':');
        Lcd_Write_Char(time[1]/10+48);
        Lcd_Write_Char(time[1]%10+48);
        Lcd_Write_Char(':');
        Lcd_Write_Char(time[0]/10+48);
        Lcd_Write_Char(time[0]%10+48);
        
        Lcd_Set_Cursor(2,4);
        Lcd_Write_Char(time[4]/10+48);
        Lcd_Write_Char(time[4]%10+48);
        Lcd_Write_Char(':');
        Lcd_Write_Char(time[5]/10+48);
        Lcd_Write_Char(time[5]%10+48);
        Lcd_Write_Char(':');
        Lcd_Write_String("20");
        Lcd_Write_Char(time[6]/10+48);
        Lcd_Write_Char(time[6]%10+48);
        __delay_ms(1000);
    }
    return;
}
void DS1307_Read_Time()
{
    I2C_Start(0xD0);
    I2C_Write(0x00);
    I2C_Repeated_Start(0xD1);
    time[0] = I2C_Read(0);
    time[1] = I2C_Read(0);
    time[2] = I2C_Read(0);
    time[3] = I2C_Read(0);
    time[4] = I2C_Read(0);
    time[5] = I2C_Read(0);
    time[6] = I2C_Read(1);
    I2C_Stop();
    
    time[0] = BCDtoDECIMAL(time[0]);
    time[1] = BCDtoDECIMAL(time[1]);
    time[2] = BCDtoDECIMAL(time[2]);
    time[4] = BCDtoDECIMAL(time[4]);
    time[5] = BCDtoDECIMAL(time[5]);
    time[6] = BCDtoDECIMAL(time[6]);
}
