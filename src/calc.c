#include "calc.h"
#include "mem_ops.h"
#include "fixedPoint.h"
#include "kb.h"
#include "lcd.h"

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
				write_data(first_num+state->position, ch);				
				LCD_print(first_num, 0, state->last_position_1);
				
				state->name = FIRST;
				state->position += 1;
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
			if(is_numeric(ch) && state->position < NUMBER_LEN)
			{
				write_data(first_num+state->position, ch);
				LCD_print(first_num, 0, state->last_position_1);
				
				state->position += 1;
				state->last_position_1 += 1;
			}
			
			if(state->position == NUMBER_LEN-2)
				ch = '+';
			
			if(is_operation(ch))
			{
				state->operation = ch;
				state->position = 0;
				state->name = THIRD;
				
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
			if(is_numeric(ch) && state->position < NUMBER_LEN)
			{
				write_data(second_num+state->position, ch);				
				LCD_print(second_num, 1, state->last_position_2);				
				
				state->position += 1;
				state->last_position_2 += 1;
			}
				
			//if(state->position == NUMBER_LEN)
			//		ch = '=';
			
			if(is_equal(ch))
			{
				state->position = 0;
				state->name = FOURTH;
				
				loop = 0;
			}
		}
	}
}

void do_state_4(state_t * state) 
{
	unsigned char ch;		
	char loop;
	
	loop = 1;
	while(loop == 1)
	{
		if(ScanKBOnce(&ch))
		{
			if(is_numeric(ch) && state->position < NUMBER_LEN)
			{
				write_data(second_num+state->position, ch);				
				state->position += 1;
				state->name = FIRST;
				
				loop = 0;
			}
			
			if(is_operation(ch))
			{
				state->operation = ch;
				state->position = 0;
				state->name = THIRD;
				
				// move result into the first operand 
			}
		}
	}
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