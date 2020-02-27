/*
 * File:   MyMain.c
 * Author: ADMIN
 *
 * Created on 01 March 2019, 07:57
 */


// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 20000000
#define Role1 RD0
#define Role2 RD1
void main(void) 
{
    // c?u hình RD0 và RD1 là chân output
    TRISD0 = 0;
    TRISD1 = 0;
    Role1 = 0;
    Role2 = 0;
   
    
    
    while(1)
    {
        Role1 = 0;
        Role2 = 1; 
        __delay_ms(1000);
        Role1 = 1; 
        __delay_ms(1000);
        Role2 = 0;
        __delay_ms(2000);
        Role1 = 0;
        __delay_ms(1000);
      
    }
    return;
}
