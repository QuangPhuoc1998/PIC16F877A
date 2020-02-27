#include "main.h"
  
#define TMR1PRESCALE 8                     
#define OUT RC2                           
unsigned long CCPR = 0;                  
unsigned long current_period = 0;          
unsigned long total_period = 0;  
 
void PWM_Init(unsigned int period);
void Duty_Init(unsigned char Duty);
void main() 
{
   PWM_Init(20000);
   while (1) 
   {                                          
       Duty_Init(5);
       __delay_ms(1000);
       Duty_Init(10);
       __delay_ms(1000);
   }
}
void PWM_Init(unsigned int period)
{
   total_period = period/(0.2f*TMR1PRESCALE);
   TRISC = 0;                 
   PORTC = 0;              
   // thanh ghi T1CON = 0b00110000;    
   T1CKPS1 = 1;  // chia 8
   T1CKPS0 = 1;
   TMR1H = 0;                 
   TMR1L = 0;
   // thanh ghi CCP1CON = 0x0b;            
   CCP1M3 = 1;
   CCP1M2 = 0;
   CCP1M1 = 1;
   CCP1M0 = 1;
   // interrupt
   CCPR = 0;                  
   CCP1IF = 0;              
   CCP1IE = 1;               
   GIE = 1; // ngat toan cuc
   PEIE = 1; // ngat ngoai vi
   TMR1ON = 1; // timer bat dau dem
}
void Duty_Init(unsigned char Duty)
{
    current_period = total_period * Duty/100;
}
void __interrupt() tmr1isr() {
   if (CCP1IF == 1) {                           
       if ((current_period > 0) && (current_period < total_period))
       { 
           if (OUT == 1)
           {                                 
           OUT = 0;                                  
           CCPR = total_period - current_period;     
           }
                 
      else 
        {                                    
         OUT = 1;                               
         CCPR = current_period;                
        }
       }
      else 
       {
           if (current_period == total_period) { OUT = 1;}             
           if (current_period == 0)            {OUT = 0;}              
       }
      CCPR1H = CCPR >> 8;                       
      CCPR1L = CCPR;                            
      CCP1IF = 0;                           
   }
}