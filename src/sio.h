#ifndef _SIO_H
#define _SIO_H

#define BUFFERLEN 16
//Константы скорости
#define S9600   0xFD
#define S4800   0xFA
#define S2400   0xF4
#define S1200   0xE8

extern void Type(char * Str);
extern void InitSIO(char speed, bit sdouble);
extern void WSio(unsigned char c);
extern unsigned char RSio(void);
extern bit RSioStat(void);

#endif //_SIO_H
