#include "main.h"
#include "I2C.h"

void I2C_Master_Init(const unsigned long c)
{
  SSPCON = 0b00101000;
  SSPCON2 = 0;
  SSPADD = (_XTAL_FREQ/(4*c))-1;
  SSPSTAT = 0;
  TRISC3 = 1;        
  TRISC4 = 1;        
}
void I2C_Master_Wait()
{
  while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}
void I2C_Master_Start()
{
  I2C_Master_Wait();
  SEN = 1;
}
void I2C_Master_RepeatedStart()
{
  I2C_Master_Wait();
  RSEN = 1;
}
void I2C_Master_Stop()
{
  I2C_Master_Wait();
  PEN = 1;
}
void I2C_Master_Write(unsigned d)
{
  I2C_Master_Wait();
  SSPBUF = d;
}
unsigned short I2C_Master_Read(unsigned short a)
{
  unsigned short temp;
  I2C_Master_Wait();
  RCEN = 1;
  I2C_Master_Wait();
  temp = SSPBUF;
  I2C_Master_Wait();
  ACKDT = (a)?0:1;
  ACKEN = 1;
  return temp;
}
// che do master
void I2C_Slave_Init(short address) 
{
  SSPSTAT = 0x80;    
  SSPADD = address; 
  SSPCON = 0x36;    
  SSPCON2 = 0x01;
  TRISC3 = 1;       
  TRISC4 = 1;      
  GIE = 1;          
  PEIE = 1;       
  SSPIF = 0;       
  SSPIE = 1;        
}
