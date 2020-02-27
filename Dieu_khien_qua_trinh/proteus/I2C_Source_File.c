
/*
 * PIC18F4550 I2C Source File
 * http://www.electronicwings.com
 */ 


#include "main.h"
#include "I2C_Master_File.h"

void I2C_Init()
{
    TRISC3 = 1;                     /* Set up I2C lines by setting as input */
	TRISC4 = 1;
	SSPSTAT = 80;                   /* Slew rate disabled, other bits are cleared */
    SSPCON = 0x28;					/* Enable SSP port for I2C Master mode, clock = FOSC / (4 * (SSPADD+1))*/ 
	SSPCON2 = 0;
    SSPADD = BITRATE;               /* Set clock frequency */  
    SSPIE = 1;                      /* Enable SSPIF interrupt */
    SSPIF = 0;
}

char I2C_Start(char slave_write_address)
{   
    SSPCON2bits.SEN = 1;            /* Send START condition */
    while(SSPCON2bits.SEN);         /* Wait for completion of START */
    SSPIF=0;
    if(!SSPSTATbits.S)              /* Return 0 if START is failed */
    return 0;
    return (I2C_Write(slave_write_address)); /* Write slave device address with write to communicate */
}

void I2C_Start_Wait(char slave_write_address)
{
  while(1)
  {   
    SSPCON2bits.SEN = 1;            /* Send START condition */
    while(SSPCON2bits.SEN);         /* Wait for completion of START */
    SSPIF = 0;
    if(!SSPSTATbits.S)              /* Continue if START is failed */
        continue;
    I2C_Write(slave_write_address); /* Write slave device address with write to communicate */
    if(ACKSTAT)                     /* Check whether Acknowledgment received or not */
    {
        I2C_Stop();                 /* If not then initiate STOP and continue */
        continue;
    }    
    break;                          /* If yes then break loop */
  }
}

char I2C_Repeated_Start(char slave_read_address)
{
    RSEN = 1;                       /* Send REPEATED START condition */
    while(SSPCON2bits.RSEN);        /* Wait for completion of REPEATED START condition */
    SSPIF = 0;
    if(!SSPSTATbits.S)              /* Return 0 if REPEATED START is failed */
    return 0;
    I2C_Write(slave_read_address);  /* Write slave device address with read to communicate */
    if (ACKSTAT)                    /* Return 2 if acknowledgment received else 1 */
     return 1;
    else
     return 2;
}

char I2C_Write(unsigned char data)
{
      SSPBUF = data;                /* Write data to SSPBUF */
      I2C_Ready();
      if (ACKSTAT)                  /* Return 2 if acknowledgment received else 1 */
        return 1;
      else
        return 2;
}

void I2C_Ack()
{
    ACKDT = 0;  					/* Acknowledge data 1:NACK,0:ACK */
	ACKEN = 1;        				/* Enable ACK to send */
    while(ACKEN);
}

void I2C_Nack()
{
    ACKDT = 1;          			/* Not Acknowledge data 1:NACK,0:ACK */
	ACKEN = 1;              		/* Enable ACK to send */	          
    while(ACKEN);
}
char I2C_Read(char flag)            /* Read data from slave devices with 0=Ack & 1=Nack */
{
    char buffer;
    RCEN = 1;                       /* Enable receive */
    while(!SSPSTATbits.BF);         /* Wait for buffer full flag which set after complete byte receive */
    buffer = SSPBUF;                /* Copy SSPBUF to buffer */
    if(flag==0)
        I2C_Ack();                  /* Send acknowledgment */
    else
        I2C_Nack();                 /* Send negative acknowledgment */
    I2C_Ready();
    return(buffer);
}

char I2C_Stop()
{
    PEN = 1;                        /* Initiate STOP condition */
    while(PEN);                     /* Wait for end of STOP condition */
    SSPIF = 0;
    if(!SSPSTATbits.P);             /* Return 0 if STOP failed */
    return 0;
}

void I2C_Ready()
{
    while(!SSPIF);                  /* Wait for operation complete */
    SSPIF=0;                        /*clear SSPIF interrupt flag*/
}



