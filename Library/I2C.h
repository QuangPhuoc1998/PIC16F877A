#ifndef _I2C_H_
#define _I2C_H_

// che do master
void I2C_Master_Init(const unsigned long c);
void I2C_Master_Wait();
void I2C_Master_Start();
void I2C_Master_RepeatedStart();
void I2C_Master_Stop();
void I2C_Master_Write(unsigned d);
unsigned short I2C_Master_Read(unsigned short a);
// che do slave
void I2C_Slave_Init(short address); 
/* Example
I2C_Master_Start();         //Start condition
I2C_Master_Write(0x41);     //7 bit address + Write
PORTD = I2C_Master_Read(0);
I2C_Master_Stop();          //Stop condition
__delay_ms(100);
*/
#endif