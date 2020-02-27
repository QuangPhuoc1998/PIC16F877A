#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include "lcd4.h"

#define DHT11_PIN RB0
#define DHT11_TRIS TRISB0

void Request()				/* Microcontroller send start pulse/request */
{
	DHT11_TRIS = 0;
	DHT11_PIN = 0;	/* set to low pin */
	__delay_ms(20);			/* wait for 20ms */
	DHT11_PIN = 1;	/* set to high pin */
}
void Response()				/* receive response from DHT11 */
{
	DHT11_TRIS = 1;
	while(DHT11_PIN);
	while(!DHT11_PIN);
	while(DHT11_PIN);
}
uint8_t Receive_data()			/* receive data */
{
	uint8_t c=0;
	for (int q=0; q<8; q++)
	{
		while(!DHT11_PIN);  /* check received bit 0 or 1 */
		__delay_us(30);
		if(DHT11_PIN)/* if high pulse is greater than 30ms */
		c = (c<<1)|(0x01);	/* then its logic HIGH */
		else			/* otherwise its logic LOW */
		c = (c<<1);
		while(DHT11_PIN);
	}
	return c;
}
void main()
{
    char data[5];
    uint8_t I_RH,D_RH,I_Temp,D_Temp,CheckSum;
    //
    Lcd_Set_Port('D');
    Lcd_Init();
    Lcd_Write_String("Nhiet do: ");
    Lcd_Set_Cursor(2,1);
    Lcd_Write_String("Do am: ");
    while(1)
    {
        Request();		/* send start pulse */
		Response();		/* receive response */
		I_RH=Receive_data();	/* store first eight bit in I_RH */
		D_RH=Receive_data();	/* store next eight bit in D_RH */
		I_Temp=Receive_data();	/* store next eight bit in I_Temp */
		D_Temp=Receive_data();	/* store next eight bit in D_Temp */
		CheckSum=Receive_data();/* store next eight bit in CheckSum */
        if ((I_RH + D_RH + I_Temp + D_Temp) != CheckSum)
		{
			Lcd_Set_Cursor(1,0);
			Lcd_Write_String("Error");
		}
        else
		{
			Lcd_Set_Cursor(2,8);
            sprintf(data,"%d",I_RH);
			Lcd_Write_String(data);
            Lcd_Write_Char('.');
            sprintf(data,"%d",D_RH);
			Lcd_Write_String(data);
            
            Lcd_Set_Cursor(1,11);
            sprintf(data,"%d",I_Temp);
			Lcd_Write_String(data);
            Lcd_Write_Char('.');
            sprintf(data,"%d",D_Temp);
			Lcd_Write_String(data);
		}
    }
}