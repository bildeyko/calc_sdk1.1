#include "fixed_point_test.h"

//simple test "add two numbers", returns true if passed successfully
char test_add(){
	byte xdata *first = 0x0010;
	byte xdata *second = 0x0020;
	byte xdata *result = 0x0030;
	byte a;
	byte b;
	
	byte_to_number(first, 123, 0);
	byte_to_number(second, 234, 0);

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
	
	byte_to_number(first, 0x65, 0);
	write_data(first+1, 0x01);
	byte_to_number(second, 234, 0);
	byte_to_number(result, 0, 0);
	
	sub(first, second, result);	//must be 357 or 0x165 or 0x6501 (this is in little endian) 
	a = read_data(result);
	b = read_data(result+1);
	return a==123 && b==0x00;
}

//simple test "mul two numbers", returns true if passed successfully
char test_mul(){
	byte xdata *first = 0x0010;
	byte xdata *second = 0x0020;
	byte xdata *result = 0x0030;
	byte a;
	byte b;
	
	byte_to_number(first, 100, 0);
	byte_to_number(second, 234, 0);
	byte_to_number(result, 0, 0);
	
	mul(first, second, result);	//must be 357 or 0x165 or 0x6501 (this is in little endian) 
	a = read_data(result);
	b = read_data(result+1);
	return a==0x68 && b==0x5b;
}

//simple test "mul two numbers", returns true if passed successfully
char test_mul_neg(){
	byte xdata *first = 0x0010;
	byte xdata *second = 0x0020;
	byte xdata *result = 0x0030;
	byte a;
	byte b;
	
	byte_to_number(first, 5, 1);
	byte_to_number(second, 234, 0);
	byte_to_number(result, 0, 0);
	
	mul(first, second, result);	//must be 357 or 0x165 or 0x6501 (this is in little endian) 
	a = read_data(result);
	b = read_data(result+1);
	return a==0x6E && b==0xFB;
}

char begin_test(){
	char res = 0xFF;
	res = res && test_add();
	res = res && test_sub();
	res = res && test_mul();
	res = res && test_mul_neg();
	return res;
}