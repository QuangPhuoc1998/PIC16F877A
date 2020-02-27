/*
 * File:   MPU6050.c
 * Author: Admin
 *
 * Created on June 2, 2019, 12:54 AM
 */


#include "main.h"
#include <stdio.h>
#include "lcd4.h"
#include "MPU6050_res_define.h"
#include "I2C_Master_File.h"

void MPU6050_Init()		/* Gyro initialization function */
{
	__delay_ms(150);		/* Power up time >100ms */
	I2C_Start_Wait(0xD0);
	I2C_Write(GYRO_CONFIG);	/* Write to Gyro configuration register */
	I2C_Write(0x18);	/* Full scale range +/- 2000 degree/C */
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(INT_ENABLE);	/* Write to interrupt enable register */
	I2C_Write(0x01);
	I2C_Stop();
}
void MPU_Start_Loc()
{
	I2C_Start_Wait(0xD0);	/* I2C start with device write address */
	I2C_Write(0x3B);/* Write start location address to read */ 
	I2C_Repeated_Start(0xD1);/* I2C start with device read address */
}
void main(void) 
{
    // bien 
	int Ax;
    float Xa;
    char buffer[20];
    // chuong trinh con
    Lcd_Set_Port('D');
    Lcd_Init();
    I2C_Init();
    __delay_ms(100);
    MPU6050_Init();
    while(1)
    {
        MPU_Start_Loc();
		/* Read Gyro values continuously & send to terminal over UART */
		Ax = (((int)I2C_Read(0)<<8) | (int)I2C_Read(1));
		I2C_Stop();
        
        Xa = Ax;	
        sprintf(buffer,"Ax=%.2f \t",Xa);
        Lcd_Set_Cursor(1,1);
		Lcd_Write_String(buffer);
        __delay_ms(150);
    }
    return;
}
