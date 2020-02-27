#include "lcd4.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

char max[]="MAX";

void LCD_Cmd(char select, char cmd) {
    LCD_RS_TRIS = 0;
    LCD_RW_TRIS = 0;
    LCD_EN_TRIS = 0;

    LCD_D7_TRIS = 0;
    LCD_D6_TRIS = 0;
    LCD_D5_TRIS = 0;
    LCD_D4_TRIS = 0;
    LCD_D3_TRIS = 0;
    LCD_D2_TRIS = 0;
    LCD_D1_TRIS = 0;
    LCD_D0_TRIS = 0;

    LCD_D7 = 0;
    LCD_D6 = 0;
    LCD_D5 = 0;
    LCD_D4 = 0;
    LCD_D3 = 0;
    LCD_D2 = 0;
    LCD_D1 = 0;
    LCD_D0 = 0;

    LCD_RS = select;
    LCD_RW = 0;

    char cmd1 = (cmd & 0xF0) >> 4;

    LCD_D4 = (cmd1 >> 0) & 0x01;
    LCD_D5 = (cmd1 >> 1) & 0x01;
    LCD_D6 = (cmd1 >> 2) & 0x01;
    LCD_D7 = (cmd1 >> 3) & 0x01;

    LCD_EN = 1;
    __delay_us(5);
    LCD_EN = 0;

    cmd1 = (cmd & 0x0F);

    LCD_D4 = (cmd1 >> 0) & 0x01;
    LCD_D5 = (cmd1 >> 1) & 0x01;
    LCD_D6 = (cmd1 >> 2) & 0x01;
    LCD_D7 = (cmd1 >> 3) & 0x01;

    LCD_EN = 1;
    __delay_us(5);
    LCD_EN = 0;

    __delay_ms(10);
}

void LCD_8_Cmd(char select, char cmd) {
    LCD_RS_TRIS = 0;
    LCD_RW_TRIS = 0;
    LCD_EN_TRIS = 0;

    LCD_D7_TRIS = 0;
    LCD_D6_TRIS = 0;
    LCD_D5_TRIS = 0;
    LCD_D4_TRIS = 0;
    LCD_D3_TRIS = 0;
    LCD_D2_TRIS = 0;
    LCD_D1_TRIS = 0;
    LCD_D0_TRIS = 0;

    LCD_D7 = 0;
    LCD_D6 = 0;
    LCD_D5 = 0;
    LCD_D4 = 0;
    LCD_D3 = 0;
    LCD_D2 = 0;
    LCD_D1 = 0;
    LCD_D0 = 0;

    LCD_RS = select;
    LCD_RW = 0;

    LCD_D0 = (cmd >> 0) & 0x01;
    LCD_D1 = (cmd >> 1) & 0x01;
    LCD_D2 = (cmd >> 2) & 0x01;
    LCD_D3 = (cmd >> 3) & 0x01;
    LCD_D4 = (cmd >> 4) & 0x01;
    LCD_D5 = (cmd >> 5) & 0x01;
    LCD_D6 = (cmd >> 6) & 0x01;
    LCD_D7 = (cmd >> 7) & 0x01;

    LCD_EN = 1;
    __delay_us(5);
    LCD_EN = 0;
    __delay_ms(10);
}

void LCD_8_Init() {
    LCD_8_Cmd(0, 0x38);
    LCD_Cmd(0, LCD_CURSOR_OFF);
    LCD_Cmd(0, LCD_UP_NOSHIFT);
    LCD_Cmd(0, LCD_CLEAR_DISPLAY);
}

void LCD_Init() {
    LCD_8_Cmd(0, 0x20);
    LCD_Cmd(0, 0x28);
    LCD_Cmd(0, LCD_CURSOR_OFF);
    LCD_Cmd(0, LCD_UP_NOSHIFT);
    LCD_Cmd(0, LCD_CLEAR_DISPLAY);
    LCD_Cmd(0,0x02);
}

void LCD_Out_Str(char str[]) {
    for (int i = 0; i < strlen(str); i++) {
        if (i == 15) {
            LCD_Cmd(0, 0xC0);
        }
        LCD_Cmd(1, str[i]);
    }
}

void LCD_Out_Int(signed int value) {
    int doDai = 0, t1, t2, i;
    if (value < 0) {
        LCD_Cmd(1, ' ');
        LCD_Cmd(1, '<');
        LCD_Cmd(1, (char) (0 + 48));
        return;
    }  else if (value >= 0 && value < 10) {
        LCD_Cmd(1, ' ');
        LCD_Cmd(1, ' ');
        LCD_Cmd(1, (char) (value + 48));
        return;
    } else if (value >= 10 && value < 100) {
        doDai = 2;
    } else if (value >= 100 && value < 1000) {
        doDai = 3;
    }/*
        else if (value >= 1000 && value < 10000) {
            doDai = 4;
        } else if (value >= 10000 && value <= 32767) {
            doDai = 5;
        }
         */
        //Vi de bai yeu cau dai do <1000 nen chi can xet value co 3 chu so
    else if (value >= 1000) {
        LCD_Out_Str(max);
        return;
    }
    for (i = 0; i < 3 - doDai; i++) {
        LCD_Cmd(1, ' ');
    }
    if (doDai >= 2) {
        do {
            t1 = pow((double) 10, (double) (doDai - 1));
            t2 = value / t1;
            LCD_Cmd(1, (char) (t2 + 48));
            value %= t1;
            doDai--;
        } while (doDai != 0);
    }
}

void LCD_Out_Double(double value) {
    int t1, t2;
    t1 = floor(value);
    t2 = (int) ((value - t1)*1000);
    LCD_Out_Int(t1);
    LCD_Cmd(1, '.');
    LCD_Out_Int(t2);
}

void LCD_GotoXy(unsigned char col, unsigned char row) {
    // Khai bao bien.
    unsigned char address;

    // Dinh nghia ham.
    if (row != 0) // Kiem tra hang hien thi de tao dia chi hien thi hang.
        address = 0x40; // Ma dieu khien hien thi hang 2.
    else
        address = 0x00; // Ma dieu khien hien thi hang 1.

    address += col; // Ket hop gia tri hang va cot de tao ra dia chi hien thi.

    LCD_Cmd(0, 0x80 | address); // Gui lenh xac dinh toa do hien thi tren LCD.

    while (LCD_IsBusy()); // Kiem tra LCD bao ban.
}

unsigned char LCD_IsBusy() {
    // Khai bao bien.
    unsigned char busy;

    // Dinh nghia ham.
    LCD_D4_TRIS = 1; // Cau hinh ngo vao cho cac duong du lieu.
    LCD_D5_TRIS = 1;
    LCD_D5_TRIS = 1;
    LCD_D7_TRIS = 1;

    LCD_RW = 1; // RW = 1 - Read.
    LCD_RS = 0; // RS = 0 - Command.
    __delay_us(20);
    LCD_EN = 1; // EN = 1 - Enable.
    __delay_us(20);

    busy = LCD_D7; // Doc gia tri co bao ban tu LCD.

    LCD_EN = 0; // EN = 0 - Disable.
    __delay_us(20);
    LCD_EN = 1; // EN = 1 - Enable. Tao xung truyen thong tin.
    __delay_us(20);
    LCD_EN = 0; // EN = 0 - Disable.

    return busy; // Tra ve gia tri bao LCD ban hay khong (1: Busy).
}