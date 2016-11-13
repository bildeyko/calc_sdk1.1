#include "fixedPoint.h"
#include "mem_ops.h"

//DOC
//Low bytes first
//Negative numbers are represented in twos-complement (inversed positive and +1)

#define BYTES_CNT 32
#define POINT_POS 6

byte bytes_cnt = BYTES_CNT; //count of bytes for number, must be not bigger than 127!!! (if it is, left shift funtion must be rewrited)
byte point_pos = POINT_POS; //point position in number

void to_negative(byte xdata *number){
	byte carry = 1;								//initial +1
	byte x;
	byte i;
	
	for (i = 0; i < bytes_cnt; i++){
		x = read_data(number+i);
		x = ~x + carry;							
		carry = (x == 0 && carry == 1) ? 1 : 0;					//if +1 gain 0 than overflow detected
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

void sub(byte xdata *first_number, byte xdata *second_number, byte xdata *res){
	to_negative(second_number);
	add(first_number, second_number, res);
	to_negative(second_number);
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

void shift_left(byte xdata *number, byte shift){
	byte carry = 0, val;
	char i, read_pos;
	byte byte_part, bit_part;
	
	byte_part = shift>>3;																								//if shift > than 8 set byte_part
	bit_part = shift & 0x07;																						// 0..7 bit value
	for(i = bytes_cnt-1; i >= 0; i--){																	//INFO this loop(char i) restrict bytes_cnt value to 127
		read_pos = i - byte_part;
		if (read_pos >= 0) {																							//if address lower than bytes count of number, fill 0 to rest of the number
			val = read_data(number + read_pos);															//value from memory
			read_pos -= 1;
			carry = read_pos < 0 ? 0 : read_data(number + read_pos);
			write_data(number + i, val << bit_part | (carry >> (8-bit_part)));			//write to i(current_byte) - byte_part
		}
		else write_data(number+i, 0);
	}
	write_data(number, read_data(number+bytes_cnt-1)&0x8F);							//forse set negative bit of number to 0
}

void shift_right(byte xdata *number, byte shift){
	byte carry = 0, val, read_pos;
	char i;
	byte byte_part, bit_part;
	
	byte_part = shift>>3;																								
	bit_part = shift & 0x07;																						
	for(i = 0; i< bytes_cnt; i++){
		read_pos = i + byte_part;
		if (read_pos < bytes_cnt){
			val = read_data(number + read_pos);
			carry = read_pos >= (bytes_cnt - 1) ? 0 : read_data(number + read_pos + 1);
			write_data(number + i, val >> bit_part | (carry << (8-bit_part)));																				
		}
		else write_data(number+i, 0);
	}
	write_data(number, read_data(number+bytes_cnt-1)&0x8F);							//forse set negative bit of number to 0
}

//byte_pos * 8 + bit_pos - position of highest bit to compare two numbers
char compare_numbers(byte xdata *first_number, byte xdata *second_number, byte byte_pos, byte bit_pos, int len){
	byte val1, val2;
	byte i;
	
	bit_pos += 1;
	val1 = read_data(first_number + byte_pos)&(~(0xFF << bit_pos));
	val2 = read_data(second_number + byte_pos)&(~(0xFF << bit_pos));
	len -= bit_pos;
	if (len < 0){																						//compare only len count of bits
		val1 = val1 & (0xFF<<(-len));		
		val2 = val2 & (0xFF<<(-len));		
	}
	if (val1 < val2)
		return -1;
	if (val1 > val2)
		return 1;

	
	for(i = byte_pos; i > 0; i--){
		if (len < 0) 
			return 0;
		val1 = read_data(first_number + i - 1);
		val2 = read_data(second_number + i - 1);
		len -= 8;
		if (len < 0){																						//compare only len count of bits
			val1 = val1 & (0xFF<<(-len));		
			val1 = val1 & (0xFF<<(-len));		
		}
		if (val1 < val2)
			return -1;
		if (val1 > val2)
			return 1;
	}
	return 0;
}

char pos_div(byte xdata *first_number, byte xdata *second_number, byte xdata *res){
	byte i;
	int j, comp_start;
	byte first_byte_pos=0, second_byte_pos=0, first_bit_pos = 0, second_bit_pos = 0, tmp, tmp2;
	
	//this two "for" cycles finds start positions for div operation
	for(i=0; i<bytes_cnt; i++){												
		if (read_data(first_number+i)){
			first_byte_pos=i;
		}
		if (read_data(second_number+i)){
			second_byte_pos=i;
		}
	}
	tmp = read_data(second_number+second_byte_pos);
	tmp2 = read_data(first_number+first_byte_pos);
	for(i=0; i<8; i++){
		if (tmp & 0x01){
			second_bit_pos = i;
		}
		if (tmp2 & 0x01){
			first_bit_pos = i;
		}
		tmp = tmp >> 1;
		tmp2 = tmp2 >> 1;
	}
	
	if (second_byte_pos == 0) return 1;						//INVALID, division to 0
	j = (first_byte_pos-second_byte_pos) * 8 + first_bit_pos - second_bit_pos;
	if (j < 0) 
		return 0;																		//second number bigger than first, division result is 0
	for (i=0; i<=(byte)(j>>8); i++){							//shift divider first '1' byte to dividend first '1' byte
		shift_left(second_number, (byte)j);
	}
	j = first_byte_pos*8+first_bit_pos;
	comp_start = j;
	for(; j>=0; j--){
		char cmp;
		cmp = compare_numbers(first_number, second_number, (byte)(comp_start>>3), (byte)comp_start&0x07, (((int)second_byte_pos)<<3)+second_bit_pos);
		//if divider bigger than dividend write 1 and sub second number from first
		if (cmp >= 0){				
			int write_offset = (j-second_bit_pos+(second_byte_pos-point_pos)*8)>>3;
			sub(first_number, second_number, first_number);
			tmp = (j - second_bit_pos) & 0x07;														//set bit to 1
			tmp = 1 << tmp;
			tmp = read_data(res + write_offset) | tmp;			//value to write
			write_data(res + write_offset, tmp);	
			if (cmp == 0)															//first number is 0 now, return
				return 0;
			comp_start = j-1;
		}	
		shift_right(second_number, 1);
	}
	return 0;
}

//The div function can change input numbers
//Invert number to positive value, if it is negative
//Convert result to negative value, if only one input number is negative
byte xdata * div(byte xdata *first_number, byte xdata *second_number, byte xdata * res){
	byte neg_res = 0;
	
	if (first_number[bytes_cnt-1]&0x7F){ 
		neg_res = ~neg_res;
		to_negative(first_number);
	}
	if (second_number[bytes_cnt-1]&0x7F){ 
		neg_res = ~neg_res;
		to_negative(second_number);
	}
	pos_div(first_number, second_number, res);
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

void number_from_string(byte xdata * res, byte xdata * tmp1, byte xdata *tmp2, char xdata * str, byte len){
	byte i=0, val, str_point_pos;
	char is_negative = 0;
	
	if (read_data(str) == '-') {								//if first symbol is 0, set is_negative = true
		is_negative = 1;
		i++;
	}
	byte_to_number(tmp1, str[i]-48, 0); 				//initialize number with first numeric symbol of the string
	byte_to_number(tmp2, 10, 0);							  //initialize tmp2 with 10
	
	for (i=i+1; i<len; i++){										//parse integer part of number
		val = read_data(str+i);
		if (val == '.'){													//if symbol is '.' store position and break operation
			str_point_pos = i;												
		}
		mul(tmp1, tmp2, res);											//multiply to 10, store result to res
		add_byte(res, 0, read_data(str+i)-48);		//add next symbol value to res
	}
	
	for (i = point_pos; i<len; i++){						//parse fractional part of number
			//pos_div(res, 
	}
	
	if (is_negative)
		to_negative(res);
}