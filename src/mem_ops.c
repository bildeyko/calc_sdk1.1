#include "mem_ops.h"
#include "aduc812.h"

#define MAXBASE_MEM_OPS 1 
//#define MAXBASE 8

void write_data (unsigned char xdata *ptr, unsigned char val){
	unsigned char oldDPP = DPP;
	DPP = MAXBASE_MEM_OPS;
	*ptr = val;
	DPP = oldDPP;
} 

unsigned char read_data(unsigned char xdata *ptr){
	unsigned char oldDPP = DPP;
	unsigned char val = 0;
	DPP = MAXBASE_MEM_OPS;
	val = *ptr;
	DPP = oldDPP;
	return val;
} 

void mem_set(unsigned char xdata *ptr, unsigned char val, unsigned char count){
	unsigned char oldDPP = DPP;
	DPP = MAXBASE_MEM_OPS;
	while(count--){
		*(ptr+count) = val;
	}
	DPP = oldDPP;
}

void mem_cpy(unsigned char xdata *dest, unsigned char xdata *src, unsigned char count){
		unsigned char oldDPP = DPP;
	DPP = MAXBASE_MEM_OPS;
	while(count--){
		*(dest+count) = *(src+count);
	}
	DPP = oldDPP;
}