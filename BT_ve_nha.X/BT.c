#include "main.h"
#include "lcd4.h"

char mang_1[9] = {'N','E','K','O','_','C','H','A','N'};
char mang_2[12] = " konnichiwa \n";
char mang_5[10] = "Hom nay la:";
char mang_3[15] = {'T','h','u',' ','3',' ',' ','9','/','4','/','2','0','1','9'};
char mang_4[14] = "Happy birthday";
void main()
{ 
    unsigned char i;
    TRISD = 0x00;
    Lcd_Init();
    
    
    while(1)
    {
      Lcd_Set_Cursor(1,4);
      for(i=0;i<9;i++)
      {
          Lcd_Write_Char(mang_1[i]);
          __delay_ms(100);
      }
      for(i=17;i>2;i--)
      {
          Lcd_Set_Cursor(2,i);
          Lcd_Write_String(mang_2);
          __delay_ms(100);
      }
      __delay_ms(1500);
      Lcd_Clear();
      Lcd_Set_Cursor(1,1);
      Lcd_Write_String("Hom nay la: ");
    __delay_ms(500);
    Lcd_Set_Cursor(2,1);
    for(i=0;i<15;i++)
    {
        Lcd_Write_Char(mang_3[i]);
        __delay_ms(100);
    }
    __delay_ms(1500);
    Lcd_Clear(); 
    Lcd_Set_Cursor(1,3);
    Lcd_Write_String(mang_4);
    __delay_ms(500);
    Lcd_Set_Cursor(2,3);
    Lcd_Write_String("BAN SON DUY");
    __delay_ms(1000);
    Lcd_Clear();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("LOVE YOU (^_^)");
    __delay_ms(500);
    Lcd_Set_Cursor(2,3);
    Lcd_Write_String("LOVE YOU (^_^)");
    __delay_ms(1500);
    Lcd_Clear();
    
    }
    return;
}