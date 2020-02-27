#include "main.h"
#include "lcd4.h"


void main(void) 
{
    TRISD = 0x00;
    Lcd_Init();
    Lcd_Write_String("hello");
    while(1)
    {
        __delay_ms(100);
    }
    return;
}
