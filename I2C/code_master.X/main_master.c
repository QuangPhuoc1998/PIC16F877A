/*
 * File:   main.c
 * Author: Admin
 *
 * Created on July 27, 2019, 9:28 PM
 */


#include "main.h"
#include "I2C.h"

#define BTN1 RD0
#define BTN2 RD1
#define BTN3 RD2

void main(void)
{
    // port
    TRISD0 = 1;
    TRISD1 = 1;
    TRISD2 = 1;
    // chuong trinh con
    I2C_Master_Init(100000);
    while(1)
    {
        if(BTN1 == 0)
        {
            while(BTN1 == 0);
            I2C_Master_Start();         
            I2C_Master_Write(0x30);
            __delay_ms(10);
            I2C_Master_Write(0x01);
            I2C_Master_Stop();         
        }
        if(BTN2 == 0)
        {
            while(BTN2 == 0);
            I2C_Master_Start();         
            I2C_Master_Write(0x30);
            __delay_ms(10);
            I2C_Master_Write(0x02);
            I2C_Master_Stop();         
        }
        if(BTN3 == 0)
        {
            while(BTN3 == 0);
            I2C_Master_Start();         
            I2C_Master_Write(0x30);
            __delay_ms(10);
            I2C_Master_Write(0x03);
            I2C_Master_Stop();         
        }
    }
    return;
}
