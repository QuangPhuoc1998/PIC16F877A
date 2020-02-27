/*
 * File:   I2C.c
 * Author: Admin
 *
 * Created on May 27, 2019, 9:16 PM
 */


#include "main.h"
#include "I2C.h"

void main(void)
{
    // bien
    
    // port
    TRISD = 0x00;
    // chuong trinh con
    I2C_Master_Init(100000);      //Initialize I2C Master with 100KHz clock
    // begin
    while(1)
    {
      I2C_Master_Start();         //Start condition
      I2C_Master_Write(0x40);     //7 bit address + Write
      I2C_Master_Write(0xAA);
      I2C_Master_Stop();          //Stop condition
      __delay_ms(100);
    }
    return;
}

