 /*
 * File            : spi.c
 * Author          : Ligo George
 * Company         : electroSome
 * Project         : SPI Library for MPLAB XC8
 * Microcontroller : PIC 16F877A
 * Created on April 15, 2017, 5:59 PM
 */

#include "spi.h"

void Spi_Init(Spi_Type sType, Spi_Data_Sample sDataSample, Spi_Clock_Idle sClockIdle, Spi_Transmit_Edge sTransmitEdge)
{
    TRISC5 = 0;
    if(sType & 0b00000100) //If Slave Mode
    {
        SSPSTAT = sTransmitEdge;
        TRISC3 = 1;
    }
    else              //If Master Mode
    {
        SSPSTAT = sDataSample | sTransmitEdge;
        TRISC3 = 0;
    }
    SSPCON = sType | sClockIdle;
}

static void spiReceiveWait()
{
    while ( !SSPSTATbits.BF ); // Wait for Data Receive complete
}

void Spi_Write(char dat)  //Write data to SPI bus
{
    SSPBUF = dat;
}
void Spi_Write_Text(char text[])
{
	int i;
	for(i=0;text[i]!='\0';i++)
	Spi_Write(text[i]);
}
unsigned Spi_Data_Ready() //Check whether the data is ready to read
{
    if(SSPSTATbits.BF)
        return 1;
    else
        return 0;
}

char Spi_Read() //REad the received data
{
    spiReceiveWait();        // wait until the all bits receive
    return(SSPBUF); // read the received data from the buffer
}
void Spi_Read_Text(char *Output, unsigned int length)
{
	int i;
	for(i=0;i<length;i++)
	Output[i] = Spi_Read();
}
