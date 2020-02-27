#include "main.h"
#include "KeyPad4x4.h"

#define Col1 RD0
#define Col2 RD1
#define Col3 RD2
#define Col4 RD3

#define Cow1 RD4
#define Cow2 RD5
#define Cow3 RD6
#define Cow4 RD7

unsigned char Key_press()
{
    unsigned char key = 0;
    Col1 = 0;
    if(Cow1 == 0) key = 1;
    if(Cow2 == 0) key = 2;
    if(Cow3 == 0) key = 3;
    if(Cow4 == 0) key = 4;
    Col1 = 1;
    Col2 = 0;
    if(Cow1 == 0) key = 5;
    if(Cow2 == 0) key = 6;
    if(Cow3 == 0) key = 7;
    if(Cow4 == 0) key = 8;
    Col2 = 1;
    Col3 = 0;
    if(Cow1 == 0) key = 9;
    if(Cow2 == 0) key = 10;
    if(Cow3 == 0) key = 11;
    if(Cow4 == 0) key = 12;
    Col3 = 1;
    Col4 = 0;
    if(Cow1 == 0) key = 13;
    if(Cow2 == 0) key = 14;
    if(Cow3 == 0) key = 15;
    if(Cow4 == 0) key = 16;
    Col4 = 1;
    return key;
}