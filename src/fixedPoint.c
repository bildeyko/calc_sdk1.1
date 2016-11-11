#include "fixedPoint.h"
#include "mem_ops.h"

//DOC
//Low bytes first
//Negative numbers are represented in twos-complement (inversed positive and +1)

#define BYTES_CNT 32
#define POINT_POS 6

byte bytes_cnt = BYTES_CNT; //count of bytes for number
byte point_pos = POINT_POS; //point position in number

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

void add_byte(byte xdata *number, byte pos, byte val){
	byte i, num, r;
	byte carry = 0;
	
	if (pos >= bytes_cnt) return;
	for (i = pos; i < bytes_cnt; i++){
		if (val == 0 && carry == 0) break;
		num = read_data(number+i);
		r = num + val + carry;										//if carry flag true, add 1
		if (r < num || r < val)									//set carry flag 
			carry = 1;
		else 
			carry = 0;
		val = 0;
		write_data(number+i, r);
	}
}

byte xdata * add(byte xdata *first_number, byte xdata *second_number, byte xdata *res){
	byte carry = 0;
	byte i;
	byte r;
	byte first, second;

	for (i = 0; i<bytes_cnt; i++){
		first = read_data(first_number+i);
		second = read_data(second_number+i); 
		
		//if (!(carry | first | second))							//if carry and numbers is 0 return result to prevent unnecessary computations
			//return res;
		r = first + second + carry;										//if carry flag true, add 1
		if (r < first || r < second)									//set carry flag 
			carry = 1;
		else 
			carry = 0;
		write_data(res+i, r);
	}
	return res;
}

//The sub function change second number
byte xdata * sub(byte xdata *first_number, byte xdata *second_number, byte xdata *res){
	to_negative(second_number);
	return add(first_number, second_number, res);
}


byte xdata * pos_mul(byte xdata *first_number, byte xdata *second_number, byte xdata * res){
	byte i, j;
	unsigned int r;
	byte first, second;
	
	for (i = 0; i < bytes_cnt; i++){
		for (j = 0; j < bytes_cnt; j++){
			first = read_data(first_number+i);
			second = read_data(second_number+j);
			r = first * second;
			if (i+j >= point_pos) 																//to avoid shift at the end of operation
				add_byte(res, i+j-point_pos, (byte) r);						//add low byte of mul to res
			if (i+j >= point_pos - 1)															//to avoid shift at the end of operation
				add_byte(res, i+j+1-point_pos, (byte)(r>>8));			//add high byte of mul to res
		}
	}
	return res;
}

//The mul function can change input numbers
//Invert number to positive value, if it is negative
//Convert result to negative value, if only one input number is negative
byte xdata * mul(byte xdata *first_number, byte xdata *second_number, byte xdata * res){
	byte neg_res = 0;
	
	if (first_number[bytes_cnt-1]&0x7F){ 
		neg_res = ~neg_res;
		to_negative(first_number);
	}
	if (second_number[bytes_cnt-1]&0x7F){ 
		neg_res = ~neg_res;
		to_negative(second_number);
	}
	pos_mul(first_number, second_number, res);
	if (neg_res)
		to_negative(res);
	return res;
}

//set byte value "val" to number at pointer "ptr", set other number bytes to 0
//if is negative true, inverse number to negative
void byte_to_number(byte xdata *ptr, byte val, byte negative){
	byte i;
	
	for (i = 0; i < bytes_cnt; i++){
		write_data(ptr+i, 0);
	}
	write_data(ptr + point_pos, val);
	if (negative) to_negative(ptr);
}	