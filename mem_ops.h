#include <aduc812.h>

#ifndef __MEM_OPS_H__
#define __MEM_OPS_H__

void write_data(unsigned char xdata *ptr, unsigned char val);

unsigned char read_data(unsigned char xdata *ptr);

#endif