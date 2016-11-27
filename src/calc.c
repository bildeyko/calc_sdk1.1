#include "calc.h"
#include "mem_ops.h"
#include "fixedPoint.h"
#include "kb.h"
#include "lcd.h"
#include "din.h"

#define NUMBER_LEN 4

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
		if(ScanKBOnce(&ch))
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
		if(ScanKBOnce(&ch))
		{
			if(is_numeric(ch) && state->length < NUMBER_LEN)
			{
				write_data(first_num+state->length, ch);
				LCD_Print(first_num, 0, state->last_position_1);
				
				state->length += 1;
				state->last_position_1 += 1;
			}
			
			if(state->length == NUMBER_LEN-2)
				ch = '+';
			
			if(is_operation(ch))
			{
				state->operation = ch;
				state->length = 0;
				state->name = INPUT_SECOND;
				
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
		if(ScanKBOnce(&ch))
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
				state->length = 0;
				state->name = CALCULATE;
				
				loop = 0;
			}
		}
	}
}

void do_state_4(state_t * state) 
{
	unsigned char ch;		
	char loop;
	
	// calculate result
	
	
	
	loop = 1;
	while(loop == 1)
	{
		if(ScanKBOnce(&ch))
		{
			if(is_numeric(ch) && state->length < NUMBER_LEN)
			{
				write_data(second_num+state->length, ch);				
				state->length += 1;
				state->name = INPUT_FIRST;
				
				loop = 0;
			}
			
			if(is_operation(ch))
			{
				state->operation = ch;
				state->length = 0;
				state->name = INPUT_SECOND;
				
				// 1. move result into first_num 
				// 2. clean LCD
				// 3. print first_num on 0 line
			}
		}
	}
}

bit scanInput(char *ch)
{
	if(get_din(8))
		Activate_2_kb();
	else
		Activate_1_kb();
	
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