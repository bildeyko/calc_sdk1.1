#include "fixed_point_test.h"
#include "SIO.h"

	byte xdata *first = 0x3000;
	byte xdata *second = 0x3100;
	byte xdata *result = 0x3200;
	byte xdata *str = 0x3300;

//simple test "add two numbers", returns true if passed successfully
char test_add(){
	byte a;
	byte b;
	
		Type("test add started\n");
	
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
	Type("123");
	a = read_data(result+point_pos);
	Type("123");
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
	byte c;
	
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
	c = read_data(result+point_pos-1);
	return a==0x27 && b==0x16 && c==0x80;
}

char test_number_to_string(){
	byte a, b, c, d;
	mem_set(result, 0, bytes_cnt);
	byte_to_number(result, 178, 0);
	//write_data(result+point_pos+1, 0xAA);
	number_to_string(result, first, second, str);
	a = read_data(str);
	b = read_data(str+1);
	c = read_data(str+2);
	d = read_data(str+3);
	return a=='1' && b=='7' && c=='8' && d=='.';
}

char test_number_to_string2(){
	byte a, b, c, d;
	mem_set(result, 0, bytes_cnt);
	byte_to_number(result, 52, 0);
	write_data(result+point_pos-1, 0x80);
	number_to_string(result, first, second, str);
	a = read_data(str);
	b = read_data(str+1);
	c = read_data(str+2);
	d = read_data(str+3);
	return a=='5' && b=='2' && c=='.' && d=='5';
}

char test_number_to_string3(){
	byte a, b, c, d;
	mem_set(result, 0, bytes_cnt);
	byte_to_number(result, 67, 0);
	write_data(result+point_pos-1, 0xA0);
	number_to_string(result, first, second, str);
	a = read_data(str);
	b = read_data(str+1);
	c = read_data(str+2);
	d = read_data(str+3);
	return a=='6' && b=='7' && c=='.' && d=='6';
}


char begin_test(){
	char res = 0xFF;
	
	Type("tests started\n");
	res = res && test_add();
	if (res) Type("test_add() success\r\n");
	res = res && test_sub();
		if (res) Type("test_sub() success\r\n");
	res = res && test_mul();
		if (res) Type("test_mul() success\r\n");
	res = res && test_mul_neg();
		if (res) Type("test_mul_neg() success\r\n");
	res = res && test_div();
	if (res) Type("test_div() success\r\n");
	res = res && test_div_2();
	if (res) Type("test_div_2() success\r\n");
	res = res && test_number_from_string();
	if (res) Type("test_number_from_string() success\r\n");
	res = res && test_number_from_string2();
	if (res) Type("test_number_from_string2() success\r\n");
	res = res && test_number_to_string();
	if (res) Type("test_number_to_string() success\r\n");
	res = res && test_number_to_string2();
	if (res) Type("test_number_to_string2() success\r\n");
	res = res && test_number_to_string3();
	if (res) Type("test_number_to_string3() success\r\n");
	return res;
}