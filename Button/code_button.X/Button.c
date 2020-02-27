#include "main.h"

void main()
{
    // cau hinh button
    TRISB0 = 1;
    TRISB1 = 1;
    TRISB2 = 1;
    // cau hinh led
    TRISD0 = 0;
    TRISD1 = 0;
    TRISD2 = 0;
    while(1)
    {
      if(RB0 == 0) 
      {
          while(RB0==0);
          RD0 = !RD0;
      }
    }
    return;
}