#include "mem_ops.h"

#define MAXBASE 8 

void write_data (unsigned char xdata *ptr, unsigned char val){
	unsigned char oldDPP = DPP;
	DPP = MAXBASE;
	*ptr = val;
	DPP = oldDPP;
} 

unsigned char read_data(unsigned char xdata *ptr){
	unsigned char oldDPP = DPP;
	unsigned char val = 0;
	DPP = MAXBASE;
	val = *ptr;
	DPP = oldDPP;
	return val;
} 