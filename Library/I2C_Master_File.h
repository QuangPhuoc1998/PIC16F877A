
/*
 * PIC18F4550 I2C Master Header File
 * http://www.electronicwings.com
 */ 

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef I2C_Master_H
#define	I2C_Master_H

#include <xc.h>                         /* Include processor files - each processor file is guarded. */
#define F_OSC 20000000                   /* Define F_OSC, here it's 8 MHz */
#define I2C_CLOCK 100000                /* I2C clock frequency is 100 kHz*/
#define BITRATE ((F_OSC/(4*I2C_CLOCK))-1) /* find bit rate to assign this value to SSPADD register*/

void I2C_Ready();                       /* Check weather I2C is ready/idle or not */
void I2C_Init();                        /* Initialize I2C configuration*/
char I2C_Start(char);                   /* Send START pulse with slave device write address */
void I2C_Start_Wait(char);              /* Send START pulse with slave device write address until acknowledgement */
char I2C_Repeated_Start(char);          /* Send REPEATED START pulse with slave device read address*/
char I2C_Stop();                        /* Send STOP pulse*/
char I2C_Write(unsigned char);          /* Write data/address to slave device */
void I2C_Ack();                         /* Send acknowledge to slave for continue read */
void I2C_Nack();                        /* Send negative acknowledge to slave for stop current communication */
char I2C_Read(char);                    /* Read data from slave devices with 0=Ack & 1=Nack */

#endif	/* I2C_Master_H */

