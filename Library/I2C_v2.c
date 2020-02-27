/*
 * File:   I2C.c
 * Author: mbeddedc.com
 *
 * Created on 12 October, 2017, 8:24 PM
 */


#include <xc.h>
#include "I2C.h"

// Function Purpose: Configure I2C module
void InitI2C(void)
{	
	SDA_DIR = 1;		// Make SDA and 
	SCK_DIR = 1;		// SCK pins input

	SSPADD  = ((_XTAL_FREQ/4000)/I2C_SPEED) - 1;	
	SSPSTAT = 0x80;		// Slew Rate control is disabled
	SSPCON  = 0x28;		// Select and enable I2C in master mode
}


// Function Purpose: I2C_Start sends start bit sequence
void I2C_Start(void)
{
	SEN = 1;			// Send start bit
	while(!SSPIF);		// Wait for it to complete
	SSPIF = 0;			// Clear the flag bit
}


// Function Purpose: I2C_ReStart sends start bit sequence
void I2C_ReStart(void)
{
	RSEN = 1;			// Send Restart bit
	while(!SSPIF);		// Wait for it to complete
	SSPIF = 0;			// Clear the flag bit
}


//Function : I2C_Stop sends stop bit sequence
void I2C_Stop(void)
{
	PEN = 1;			// Send stop bit
	while(!SSPIF);		// Wait for it to complete
	SSPIF = 0;			// Clear the flag bit
}



//Function : I2C_Send_ACK sends ACK bit sequence
void I2C_Send_ACK(void)
{
	ACKDT = 0;			// 0 means ACK
	ACKEN = 1;			// Send ACKDT value
	while(!SSPIF);		// Wait for it to complete
	SSPIF = 0;			// Clear the flag bit
}


//Function : I2C_Send_NACK sends NACK bit sequence
void I2C_Send_NACK(void)
{
	ACKDT = 1;			// 1 means NACK
	ACKEN = 1;			// Send ACKDT value
	while(!SSPIF);		// Wait for it to complete
	SSPIF = 0;			// Clear the flag bit
}


// Function Purpose: I2C_Write_Byte transfers one byte
bit I2C_Write_Byte(unsigned char Byte)
{
	SSPBUF = Byte;		// Send Byte value
	while(!SSPIF);		// Wait for it to complete
	SSPIF = 0;			// Clear the flag bit

	return ACKSTAT;		// Return ACK/NACK from slave
}


// Function Purpose: I2C_Read_Byte reads one byte
unsigned char I2C_Read_Byte(void)
{
	RCEN = 1;			// Enable reception of 8 bits
	while(!SSPIF);		// Wait for it to complete
	SSPIF = 0;			// Clear the flag bit
 
    return SSPBUF;		// Return received byte
}
