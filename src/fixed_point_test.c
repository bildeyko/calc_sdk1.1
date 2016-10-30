#include "fixed_point_test.h"

//simple test "add two numbers", returns true if passed successfully
char test_add(){
	byte xdata *first = 0x0010;
	byte xdata *second = 0x0020;
	byte xdata *result = 0x0030;
	byte a;
	byte b;
	
	write_data(first, 123);
	write_data(second, 234);
	add(first, second, result);	//must be 357 or 0x165 or 0x6501 (this is in little endian) 
	a = read_data(result);
	b = read_data(result+1);
	return a==0x65 && b==0x01;
}

//simple test "add two numbers", returns true if passed successfully
char test_sub(){
	byte xdata *first = 0x0010;
	byte xdata *second = 0x0020;
	byte xdata *result = 0x0030;
	byte a;
	byte b;
	
	write_data(first, 0x65);
	write_data(first+1, 0x01);
	write_data(second, 234);
	sub(first, second, result);	//must be 357 or 0x165 or 0x6501 (this is in little endian) 
	a = read_data(result);
	b = read_data(result+1);
	return a==123 && b==0x00;
}

char begin_test(){
	char res = 0xFF;
	res = res || test_add();
	res = res || test_sub();
	return res;
}