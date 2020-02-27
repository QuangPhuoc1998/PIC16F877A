#ifndef _DS1307_H
#define _DS1307_H

int DECIMALtoBCD(int DEC);
int BCDtoDECIMAL(int BCD);
void DS1307_Init(uint8_t hour, uint8_t min, uint8_t date, uint8_t month, uint8_t year);

#endif