#include "calc.h"
#include "mem_ops.h"
#include "fixedPoint.h"
#include "kb.h"
#include "lcd.h"
#include "din.h"
#include "sio.h"

#define NUMBER_LEN 20

byte xdata *first_tmp = 0x3000;
byte xdata *second_tmp = 0x3100;
byte xdata *result_tmp = 0x3200;
byte xdata *str_tmp = 0x3300;

byte xdata *first_num_num = 0x3400;
byte xdata *second_num_num = 0x3500;

unsigned char xdata first_num[NUMBER_LEN];
unsigned char xdata second_num[NUMBER_LEN];

int ScanKBOnce_test(unsigned char * ch)
{
	*ch = '1';
	return 1;
}

void do_state_initial(state_t * state) 
{
	unsigned char ch;		
	char loop;
	
	loop = 1;
	while(loop == 1)
	{
		if(scan_input(&ch))
		{
			if(is_numeric(ch))
			{
				write_data(first_num+state->length, ch);				
				LCD_Print(first_num, 0, state->last_position_1);
				
				state->name = INPUT_FIRST;
				state->length += 1;
				state->last_position_1 += 1;
				
				loop = 0;
			}
		}
	}
}

/*
Input first operand. Waiting for operation.
*/
void do_state_1(state_t * state) 
{
	unsigned char ch;		
	char loop;
	
	loop = 1;
	while(loop == 1)
	{
		if(scan_input(&ch))
		{
			if(is_numeric(ch) && state->length < NUMBER_LEN)
			{
				write_data(first_num+state->length, ch);
				LCD_Print(first_num, 0, state->last_position_1);
				
				state->length += 1;
				state->last_position_1 += 1;
			}
			
			//if(state->length == NUMBER_LEN-2)
				//ch = '+';
			
			if(is_operation(ch))
			{
				byte_to_number(first_num_num, 0, 0);
				number_from_string(first_num_num, first_tmp, second_tmp, first_num, state->length);
				
				state->operation = ch;
				state->length = 0;
				//state->last_position_2 = 0; // ??? 
				state->name = INPUT_SECOND;
				
				LCD_Print_char(ch,0,1);
				
				loop = 0;
			}
		}
	}
}

/*
Input second operand. Waiting for equal sign.
*/
void do_state_3(state_t * state) 
{
	unsigned char ch;		
	char loop;
	
	loop = 1;
	while(loop == 1)
	{
		if(scan_input(&ch))
		{
			if(is_numeric(ch) && state->length < NUMBER_LEN)
			{
				write_data(second_num+state->length, ch);				
				LCD_Print(second_num, 1, state->last_position_2);				
				
				state->length += 1;
				state->last_position_2 += 1;
			}
				
			//if(state->length == NUMBER_LEN)
			//		ch = '=';
			
			if(is_equal(ch))
			{
				byte_to_number(second_num_num, 0, 0);
				number_from_string(second_num_num, first_tmp, second_tmp, second_num, state->length);
				
				Type("Equel\r\n");
				state->length = 0;
				state->name = CALCULATE;
				
				LCD_Print_char(ch,0,1);
				
				loop = 0;
			}
		}
	}
}

void do_state_4(state_t * state) 
{
	unsigned char ch;		
	char loop;
	//char tmp_123;
	
	//tmp_123 = 5+6;
	
	// calculate result
	if(state->length == '+')
	{
		byte_to_number(result_tmp, 0, 0);
		add(first_num_num, second_num_num, result_tmp);
	}
	
	LCD_clean_data();
	
	loop = 1;
	while(loop == 1)
	{
		if(scan_input(&ch))
		{
			if(is_numeric(ch) && state->length < NUMBER_LEN)
			{
				state->length = 0;
				state->last_position_1 = 0;
				
				
				write_data(first_num+state->length, ch);	
				LCD_Print(first_num, 0, state->last_position_1);
				state->length += 1;
				state->last_position_1 += 1;
				state->last_position_2 = 0;
				state->name = INPUT_FIRST;
				
				loop = 0;
			}
			
			if(is_operation(ch))
			{
				state->operation = ch;
				state->length = 0;
				//state->last_position_2 = 0;
				state->name = INPUT_SECOND;
				//state->last_position_2 = 
				
				// 1. move result into first_num 
				// 2. clean LCD
				// 3. print first_num on 0 line
			}
		}
	}
}

bit scan_input(char *ch)
{
	if(!get_din(7))
	{
		Activate_2_kb();
	}
	else
	{
		Activate_1_kb();
	}
	
	return ScanKBOnce(ch);
}

char is_numeric(unsigned char ch)
{
	if ((ch >= '0' && ch <= '9') || ch == '.')
		return 1;
	else
		return 0;
}

char is_operation(unsigned char ch)
{
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
		return 1;
	else
		return 0;
}

char is_equal(unsigned char ch)
{
	if (ch == '=')
		return 1;
	else
		return 0;
}