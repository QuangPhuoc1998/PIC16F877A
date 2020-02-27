#include "main.h"
#include "I2C_Master_File.h"

int DECIMALtoBCD(int DEC) 
{ 
     int L, H; 
     L=DEC%10; //make digit low 
     H=DEC/10<<4; //make digit high 
     return (H+L); 
} 
int BCDtoDECIMAL(int BCD) 
{ 
     int L, H; 
     L=BCD & 0x0F; //ones 
     H=(BCD>>4) * 10;//tens 
     return (H+L); 
} 
void DS1307_Init(uint8_t hour, uint8_t min, uint8_t date, uint8_t month, uint8_t year)
{
    I2C_Start(0xD0);
    I2C_Write(0x07);
    I2C_Write(0x00);
    I2C_Stop();
    
    hour = DECIMALtoBCD(hour);
    min = DECIMALtoBCD(min);
    date = DECIMALtoBCD(date);
    month = DECIMALtoBCD(month);
    year = DECIMALtoBCD(year);
    // reset second
    I2C_Start(0xD0);
    I2C_Write(0x00);
    I2C_Write(0x00);
    I2C_Stop();
    // minute
    I2C_Start(0xD0);
    I2C_Write(0x01);
    I2C_Write(min);
    I2C_Stop();
    // hour
    I2C_Start(0xD0);
    I2C_Write(0x02);
    I2C_Write(hour);
    I2C_Stop();
    // date
    I2C_Start(0xD0);
    I2C_Write(0x04);
    I2C_Write(date);
    I2C_Stop();
    // month
    I2C_Start(0xD0);
    I2C_Write(0x05);
    I2C_Write(month);
    I2C_Stop();
    // year
    I2C_Start(0xD0);
    I2C_Write(0x06);
    I2C_Write(year);
    I2C_Stop();
}