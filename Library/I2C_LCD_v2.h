#ifndef _I2C_LCD_H_
#define _I2C_LCD_H_

void Lcd_Write_Char(unsigned char data);
void lcd_send_cmd(unsigned char data);
void Lcd_Clear ();
void Lcd_Init ();
void Lcd_Write_String(char *str);
void Lcd_Set_Cursor(unsigned char row, unsigned char col);

#endif