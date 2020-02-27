/*
 * File:   DS1307.c
 * Author: Admin
 *
 * Created on May 30, 2019, 8:25 AM
 */


#include "main.h"
#include "I2C_Master_File.h"
#include "lcd4.h"
#include "DS1307.h"


#define DS1307_Address 0x68
#define Write 0
#define Read 1

unsigned int time[7];
void Timer_Init();
void DS1307_Read_Time();
void main() 
{
    // bien
    
    // port
    TRISC0 = 0;
    // chuong trinh con
    Lcd_Set_Port('D');
    Lcd_Init();
    I2C_Init();
    //
    I2C_Start(0xD0);
    I2C_Write(0x07);
    I2C_Write(0x00);
    I2C_Stop();
    // beign
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("            ");
    Lcd_Set_Cursor(2,1);
    Lcd_Write_String("            ");
    while(1)
    {
        DS1307_Read_Time();
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("            ");
        Lcd_Set_Cursor(2,1);
        Lcd_Write_String("            ");
        Lcd_Set_Cursor(1,5);
        Lcd_Write_Char(time[2]/10+48);
        Lcd_Write_Char(time[2]%10+48);
        Lcd_Write_Char(':');
        Lcd_Write_Char(time[1]/10+48);
        Lcd_Write_Char(time[1]%10+48);
        Lcd_Write_Char(':');
        Lcd_Write_Char(time[0]/10+48);
        Lcd_Write_Char(time[0]%10+48);
        
        Lcd_Set_Cursor(2,4);
        Lcd_Write_Char(time[4]/10+48);
        Lcd_Write_Char(time[4]%10+48);
        Lcd_Write_Char(':');
        Lcd_Write_Char(time[5]/10+48);
        Lcd_Write_Char(time[5]%10+48);
        Lcd_Write_Char(':');
        Lcd_Write_String("20");
        Lcd_Write_Char(time[6]/10+48);
        Lcd_Write_Char(time[6]%10+48);
        __delay_ms(1000);
        
    }
}
void DS1307_Read_Time()
{
    I2C_Start(0xD0);
    I2C_Write(0x00);
    I2C_Repeated_Start(0xD1);
    time[0] = I2C_Read(0);
    time[1] = I2C_Read(0);
    time[2] = I2C_Read(0);
    time[3] = I2C_Read(0);
    time[4] = I2C_Read(0);
    time[5] = I2C_Read(0);
    time[6] = I2C_Read(1);
    I2C_Stop();
    
    time[0] = BCDtoDECIMAL(time[0]);
    time[1] = BCDtoDECIMAL(time[1]);
    time[2] = BCDtoDECIMAL(time[2]);
    time[4] = BCDtoDECIMAL(time[4]);
    time[5] = BCDtoDECIMAL(time[5]);
    time[6] = BCDtoDECIMAL(time[6]);
}
void Timer_Init()
{
    TMR1H=0x00;    // delay 1ms
    TMR1L=0x00;
    //
    T1CKPS1 = 1;
    T1CKPS0 = 1; // chia 8
    T1OSCEN = 0; // tat bo dao dong
    T1SYNC = 0; // dong bo ngo vao xung clock tu ben ngoai
    TMR1CS = 0; //xung noi
    //
    GIE=1; // cho phep ngat toan cuc 
    PEIE=1; // cho phep ngat ngoai vi  
    TMR1IE=1; // cho phep ngat timer1
    //
    TMR1ON = 1; // cho phep bo timer bat dau dem
}
void __interrupt() MyInterrup()
{
    if(TMR1IE == 1 && TMR1IF == 1)
    {
      RC0 = !RC0;
      TMR1H=0x00;    // delay 1ms
      TMR1L=0x00;
      TMR1IF = 0;
    }
}

