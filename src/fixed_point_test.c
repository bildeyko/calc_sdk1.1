#include "fixed_point_test.h"

	byte xdata *first = 0x0010;
	byte xdata *second = 0x0030;
	byte xdata *result = 0x0050;
	byte xdata *str = 0x0100;

//simple test "add two numbers", returns true if passed successfully
char test_add(){
	byte a;
	byte b;
	
	byte_to_number(first, 123, 0);
	byte_to_number(second, 234, 0);

	add(first, second, result);	//must be 357 or 0x165 or 0x6501 (this is in little endian) 
	a = read_data(result+point_pos);
	b = read_data(result+1+point_pos);
	return a==0x65 && b==0x01;
}

//simple test "add two numbers", returns true if passed successfully
char test_sub(){
	byte a;
	byte b;
	
	byte_to_number(first, 0x65, 0);
	write_data(first+point_pos+1, 0x01);
	byte_to_number(second, 234, 0);
	byte_to_number(result, 0, 0);
	
	sub(first, second, result);	//must be 357 or 0x165 or 0x6501 (this is in little endian) 
	a = read_data(result+point_pos);
	b = read_data(result+1+point_pos);
	return a==123 && b==0x00;
}

//simple test "mul two numbers", returns true if passed successfully
char test_mul(){
	byte a;
	byte b;
	
	byte_to_number(first, 100, 0);
	byte_to_number(second, 234, 0);
	byte_to_number(result, 0, 0);
	
	mul(first, second, result);	//must be 357 or 0x165 or 0x6501 (this is in little endian) 
	a = read_data(result+point_pos);
	b = read_data(result+1+point_pos);
	return a==0x68 && b==0x5b;
}

//simple test "mul two numbers", returns true if passed successfully
char test_mul_neg(){
	byte a;
	byte b;
	
	byte_to_number(first, 5, 1);
	byte_to_number(second, 234, 0);
	byte_to_number(result, 0, 0);
	
	mul(first, second, result);	//must be 357 or 0x165 or 0x6501 (this is in little endian) 
	a = read_data(result+point_pos);
	b = read_data(result+1+point_pos);
	return a==0x6E && b==0xFB;
}

char test_div(){
	byte a;
	byte b;
	
	byte_to_number(first, 11, 0);
	write_data(first+point_pos-1, 0x40);
	byte_to_number(second, 2, 0);
	write_data(second+point_pos-1, 0x40);
	byte_to_number(result, 0, 0);
	
	div(first, second, result);	//must be 357 or 0x165 or 0x6501 (this is in little endian) 
	a = read_data(result+point_pos);
	b = read_data(result+1+point_pos);
	return a==0x05 && b==0;
}

char test_div_2(){
	byte a;
	byte b;
	
	byte_to_number(first, 0x0D , 0);
	write_data(first+point_pos+1, 0x02);			//525
	byte_to_number(second, 50, 0);
	byte_to_number(result, 0, 0);
	
	div(first, second, result);	//must be 357 or 0x165 or 0x6501 (this is in little endian) 
	a = read_data(result+point_pos);
	b = read_data(result-1+point_pos);
	return a==0x0A && b==0x80;
}

char test_number_from_string(){
	byte a;
	byte b;
	
	write_data(str, '1');
	write_data(str+1, '2');
	write_data(str+2, '3');
	write_data(str+3, '4');

	byte_to_number(result, 0, 0);
	number_from_string(result, first, second, str, 4);
	a = read_data(result+point_pos);
	b = read_data(result+point_pos+1);
	return a==0xD2 && b==0x04;
}

char test_number_from_string2(){
	byte a;
	byte b;
	
	write_data(str, '5');
	write_data(str+1, '6');
	write_data(str+2, '7');
	write_data(str+3, '1');
	write_data(str+4, '.');
	write_data(str+5, '5');

	byte_to_number(result, 0, 0);
	number_from_string(result, first, second, str, 6);
	a = read_data(result+point_pos);
	b = read_data(result+point_pos+1);
	return a==0xD2 && b==0x04;
}


char begin_test(){
	char res = 0xFF;
	
	res = res && test_add();
	res = res && test_sub();
	res = res && test_mul();
	res = res && test_mul_neg();
	res = res && test_div();
	res = res && test_div_2();
	res = res && test_number_from_string();
	res = res && test_number_from_string2();
	
	return res;
}