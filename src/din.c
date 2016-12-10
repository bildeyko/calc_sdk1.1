#include "max.h"
#include "din.h"

unsigned char get_din(unsigned char n)
{
	unsigned char mask = 1;
	if(n > 7) return 0;
    
	mask = mask << n;
	if(get_dins() & mask) 
		return 1;
	else
		return 0;
}

unsigned char get_dins()
{
	unsigned short res;	
	res = ReadMax(EXT_LO);	
	return res;
}

void write_led(unsigned char value)
{
	WriteMax(7, value);
}