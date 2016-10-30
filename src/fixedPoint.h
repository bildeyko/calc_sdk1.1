#include "mem_ops.h"

#ifndef __FIXED_POINT_H__
#define __FIXED_POINT_H__

typedef unsigned char byte;

byte xdata * add(byte xdata *first_num, byte xdata *second_num, byte xdata *res);

byte xdata * sub(byte xdata *first_num, byte xdata *second_num, byte xdata *res);

#endif