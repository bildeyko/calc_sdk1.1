
#ifndef __MEM_OPS_H__
#define __MEM_OPS_H__

#include "aduc812.h"

void write_data(unsigned char xdata *ptr, unsigned char val);
unsigned char read_data(unsigned char xdata *ptr);

void mem_set(unsigned char xdata *ptr, unsigned char val, unsigned char count);
void mem_cpy(unsigned char xdata *dest, unsigned char xdata *src, unsigned char count);


#endif