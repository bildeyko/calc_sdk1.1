#include "mem_ops.h"

#ifndef __FIXED_POINT_H__
#define __FIXED_POINT_H__

typedef unsigned char byte;

extern byte bytes_cnt;
extern byte point_pos;

byte xdata * add(byte xdata *first_num, byte xdata *second_num, byte xdata *res);
void sub(byte xdata *first_number, byte xdata *second_number, byte xdata *res);
byte xdata * mul(byte xdata *first_num, byte xdata *second_num, byte xdata *res);

void byte_to_number(byte xdata *ptr, byte val, byte to_negative);

#endif