#include "main.h"
#include <stdint.h>
#include "I2C_Master_File.h"
#include "I2C_LCD_v2.h"

#define SLAVE_ADDRESS_LCD 0x40
void Lcd_Write_Char(unsigned char data)
{
	unsigned char data_l, data_u;
	data_l = (data<<4)&0xf0;  //select lower nibble by moving it to the upper nibble position
	data_u = data&0xf0;  //select upper nibble

	I2C_Start(SLAVE_ADDRESS_LCD);
	I2C_Write(data_u|0x0D);  //enable=1 and rs =1
	I2C_Write(data_u|0x09);  //enable=0 and rs =1
	I2C_Write(data_l|0x0D);  //enable =1 and rs =1
	I2C_Write(data_l|0x09);  //enable=0 and rs =1
	I2C_Stop();
}
// send command to LCD
void lcd_send_cmd (unsigned char data)
{
	unsigned char data_l, data_u;
	data_l = (data<<4)&0xf0;  //select lower nibble by moving it to the upper nibble position
	data_u = data&0xf0;  //select upper nibble

	I2C_Start(SLAVE_ADDRESS_LCD);
	I2C_Write(data_u|0x0C);  //enable=1 and rs =0
	I2C_Write(data_u|0x08);  //enable=0 and rs =0

	I2C_Write(data_l|0x0C);  //enable =1 and rs =0
	I2C_Write(data_l|0x08);  //enable=0 and rs =0

	I2C_Stop();
}
void Lcd_Clear()
{
    lcd_send_cmd(0);
	lcd_send_cmd(1);
}

// initialise LCD

void Lcd_Init()
{
	lcd_send_cmd(0x02);
	lcd_send_cmd(0x28);
	lcd_send_cmd(0x0c);
	lcd_send_cmd(0x80);
}
void Lcd_Write_String(char *str)
{
	while (*str) Lcd_Write_Char(*str++);
}
void Lcd_Set_Cursor(unsigned char row, unsigned char col)
{
  unsigned char cmd;
  cmd = (row==1?0x80:0xC0) + col - 1;
  lcd_send_cmd(cmd);
}