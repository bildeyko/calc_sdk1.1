#include "fixedPoint.h"
#include "mem_ops.h"

typedef unsigned char byte;


//DOC
//Low bytes first

byte bytes_cnt; //count of bytes for number
byte point_pos; //point position in number

#define BYTES_CNT 16
#define POINT_POS 2

byte xdata first_num[BYTES_CNT];
byte xdata second_num[BYTES_CNT];
byte xdata result_num[BYTES_CNT];


char xdata * add(char xdata *first_number, char xdata *second_number){
	char carry = 0;
	char i;
	byte r;
	char xdata *res = result_num;

	for (i = 0; i<bytes_cnt-1; i--){
		char first = read_data(first_number+i);
		char second = read_data(second_number+i);
	
	  r = carry ? first + second + 1 : first + second;			//if carry flag true, add 1
		if (r < first || r < second)
			carry = 1;
		else 
			carry = 0;
		write_data(res+i, r);
	}
	return res;
}