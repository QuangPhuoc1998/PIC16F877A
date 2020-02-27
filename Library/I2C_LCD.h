#ifndef _I2C_LCD_H_
#define _I2C_LCD_H_

void I2C_Init (uint32_t clock);
void I2C_wait ();
void I2C_start ();
void I2C_repeated_start ();
void I2C_stop ();
void I2C_write(uint8_t data);
void Lcd_Write_Char(unsigned char data);
void lcd_send_cmd(unsigned char data);
void Lcd_Clear ();
void Lcd_Init ();
void Lcd_Write_String(char *str);
void Lcd_Set_Cursor(unsigned char row, unsigned char col);

#endif