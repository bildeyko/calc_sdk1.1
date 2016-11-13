#ifndef _MAX_H
#define _MAX_H

/*----------------------------------------------------------------------------
        Заголовочный файл модуля для работы с портами ПЛИС MAX3064(3128)
-----------------------------------------------------------------------------*/
extern void WriteMax(unsigned char xdata *regnum, unsigned char val);
extern unsigned char ReadMax(unsigned char xdata *regnum);

//Названия регистров
#define KB          0x0
#define DATA_IND    0x1
#define EXT_LO      0x2
#define EXT_HI      0x3
#define ENA         0x4
#define C_IND       0x6
#define LEDLINE     0x7

#endif //_MAX_H
