#include "fixedPoint.h"
#include "mem_ops.h"

//DOC
//Low bytes first
//Negative numbers are represented in twos-complement (inversed positive and +1)

#define BYTES_CNT 16
#define POINT_POS 2

byte bytes_cnt = BYTES_CNT; //count of bytes for number
byte point_pos = POINT_POS; //point position in number

byte xdata first_num[BYTES_CNT];
byte xdata second_num[BYTES_CNT];
byte xdata result_num[BYTES_CNT];

void to_negative(byte xdata *number){
	byte carry = 1;								//initial +1
	byte x;
	byte i;
	
	for (i = 0; i < bytes_cnt; i++){
		x = read_data(number+i);
		x = ~x + carry;							
		carry = (x == 0) ? 1 : 0;					//if +1 gain 0 than overflow detected
		write_data(number+i, x);
	}
}

byte xdata * add(byte xdata *first_number, byte xdata *second_number, byte xdata *res){
	char carry = 0;
	byte i;
	byte r;
	byte first, second;

	for (i = 0; i<bytes_cnt; i++){
		first = read_data(first_number+i);
		second = read_data(second_number+i); 
		
		//if (!(carry | first | second))							//if carry and numbers is 0 return result to prevent unnecessary computations
			//return res;
	  r = carry ? first + second + 1 : first + second;			//if carry flag true, add 1
		if (r < first || r < second)													//set carry flag 
			carry = 1;
		else 
			carry = 0;
		write_data(res+i, r);
	}
	return res;
}

byte xdata * sub(byte xdata *first_number, byte xdata *second_number, byte xdata *res){
	to_negative(second_number);
	return add(first_number, second_number, res);
}