#include "calc.h"
#include "mem_ops.h"
#include "fixedPoint.h"
#include "kb.h"
#include "lcd.h"
#include "din.h"
#include "sio.h"

#define NUMBER_LEN 32

byte xdata *first_tmp = 0x3000;
byte xdata *second_tmp = 0x3100;
byte xdata *result_tmp = 0x3200;
byte xdata *memory = 0x3300;
byte xdata *memory_tmp = 0x3400;

byte xdata *first_str_num = 0x3500;
byte xdata *second_str_num = 0x3600;

byte xdata *first_num = 0x3700;
byte xdata *second_num = 0x3800;
byte xdata *result_str = 0x3900;

//unsigned char xdata first_str_num[NUMBER_LEN];
//unsigned char xdata second_str_num[NUMBER_LEN];

int ScanKBOnce_test(unsigned char * ch)
{
	*ch = '1';
	return 1;
}

void do_state_initial(state_t * state) 
{
	unsigned char ch;		
	char loop;
	
	Type("STATE_INITIAL\r\n");
	
	mem_set(first_str_num, 0, NUMBER_LEN);
	mem_set(second_str_num, 0, NUMBER_LEN);
	mem_set(memory, 0, NUMBER_LEN);
	
	loop = 1;
	while(loop == 1)
	{
		if(scan_input(&ch))
		{
			if(is_numeric(ch))
			{
				write_data(first_str_num+state->length, ch);					
				LCD_Print(first_str_num, 0, state->last_position_1);
				
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
	bit is_mem = 0;
	
	Type("STATE_1\r\n");
	loop = 1;
	while(loop == 1)
	{
		if(scan_input(&ch))
		{
			if(is_numeric(ch) && state->length < NUMBER_LEN)
			{
				if(is_mem)
				{					
					state->length = 0;
					state->last_position_1 = 0;
					
					LCD_clean_data(0);
					is_mem = 0;
				}
				
				write_data(first_str_num+state->length, ch);
				LCD_Print(first_str_num, 0, state->last_position_1);
				
				state->length += 1;
				state->last_position_1 += 1;
			}
			
			if(is_operation(ch))
			{				
				byte_to_number(first_num, 0, 0);
				number_from_string(first_num, first_tmp, second_tmp, first_str_num, state->length);
				
				state->operation = ch;
				state->length = 0;
				//state->last_position_2 = 0; // ??? 
				state->name = INPUT_SECOND;
				
				LCD_Print_char(ch,0,1);
				
				loop = 0;
			}
			
			// save into the memory
			if(ch == 'M' || ch == 'N')
			{
				Type("M+ or M-\r\n");
				
				mem_set(first_num, 0, NUMBER_LEN);
				number_from_string(first_num, first_tmp, second_tmp, first_str_num, state->length);
				if(ch == 'M')
				{
					Type("M+\r\n");
					memory_add(first_num);
				}
				
				if(ch == 'N')
				{
					Type("M-\r\n");
					memory_sub(first_num);
				}
				
				LCD_Print_char('M',0,0);
				
				is_mem = 1;
			}
			
			// print number from the memory
			if(ch == 'A')
			{
				Type("MR\r\n");
				
				mem_set(first_str_num, 0, NUMBER_LEN);
				mem_cpy(memory_tmp, memory, NUMBER_LEN);
				number_to_string(memory_tmp, first_tmp, second_tmp, first_str_num, 100);
				LCD_Print(first_str_num, 0, number_len(first_str_num)-1);				
				
				state->length = number_len(first_str_num);
				state->last_position_1 = state->length - 1;
				
				is_mem = 1;
			}
			
			if(ch == 'B')
			{
				Type("MC\r\n");
				
				mem_set(memory, 0, NUMBER_LEN);
				LCD_Print_char(' ',0,0);
			}
			
			if(ch == 'C')
			{
				Type("C\r\n");
				
				LCD_clean_data(0);
				
				state->last_position_1 = 0;
				state->length = 0;
				state->name = INPUT_FIRST;
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
	bit is_mem = 0;
	Type("STATE_3\r\n");
	
	loop = 1;
	while(loop == 1)
	{
		if(scan_input(&ch))
		{
			if(is_numeric(ch) && state->length < NUMBER_LEN)
			{
				if(is_mem)
				{					
					state->length = 0;
					state->last_position_2 = 0;
					
					LCD_clean_data(1);
					is_mem = 0;
				}				
				
				write_data(second_str_num + state->length, ch);				
				LCD_Print(second_str_num, 1, state->last_position_2);				
				
				state->length += 1;
				state->last_position_2 += 1;
			}
			
			if(is_equal(ch))
			{
				byte_to_number(second_num, 0, 0);
				number_from_string(second_num, first_tmp, second_tmp, second_str_num, state->length);
				
				Type("Equel\r\n");
				//state->length = 0;
				state->name = CALCULATE;
				
				LCD_Print_char(ch, 0, 1);
				
				loop = 0;
			}
			
			// print number from the memory
			if(ch == 'A')
			{
				Type("MR\r\n");
				
				mem_set(second_str_num, 0, NUMBER_LEN);
				mem_cpy(memory_tmp, memory, NUMBER_LEN);
				number_to_string(memory_tmp, first_tmp, second_tmp, second_str_num, 100);
				LCD_Print(second_str_num, 1, number_len(first_str_num)-1);				
				
				state->length = number_len(second_str_num);
				state->last_position_2 = state->length - 1;
				
				is_mem = 1;
			}
			
			if(ch == 'C')
			{
				Type("C\r\n");
				
				LCD_clean_data(1);
				
				state->last_position_2 = 0;
				state->length = 0;
				state->name = INPUT_SECOND;
				loop = 0;
			}
		}
	}
}

void do_state_4(state_t * state) 
{
	unsigned char ch;		
	char loop;
	Type("STATE_4\r\n");
	
	// calculate result
	byte_to_number(result_tmp, 0, 0);
	if(state->operation == '+')	
		add(first_num, second_num, result_tmp);
	if(state->operation == '-')
		sub(first_num, second_num, result_tmp);
	if(state->operation == '*')
		mul(first_num, second_num, result_tmp);
	if(state->operation == '/')
		div(first_num, second_num, result_tmp);
	number_to_string(result_tmp, first_tmp, second_tmp, result_str, 100);
	LCD_Print(result_str, 0, number_len(result_str)-1);
	
	//LCD_clean_data(0);
	LCD_clean_data(1);	
	
	loop = 1;
	while(loop == 1)
	{
		if(scan_input(&ch))
		{
			if(is_numeric(ch) && state->length < NUMBER_LEN)
			{
				state->length = 0;
				state->last_position_1 = 0;				
				
				write_data(first_str_num+state->length, ch);	
				LCD_Print(first_str_num, 0, state->last_position_1);
				state->length += 1;
				state->last_position_1 += 1;
				state->last_position_2 = 0;
				state->name = INPUT_FIRST;
				
				LCD_Print_char(' ',0,1);
				
				loop = 0;
			}
			
			if(is_operation(ch))
			{
				mem_cpy(first_str_num, result_str, NUMBER_LEN);
				mem_set(first_num, 0, NUMBER_LEN);
				state->length = number_len(first_str_num);
				number_from_string(first_num, first_tmp, second_tmp, first_str_num, state->length);				
				state->last_position_1 = state->length - 1;
				
				state->operation = ch;
				state->length = 0;
				state->last_position_2 = 0;
				state->name = INPUT_SECOND;
				
				LCD_Print_char(ch,0,1);
				
				loop = 0;
			}
			
			if(ch == 'M' || ch == 'N')
			{
				Type("M+ or M-\r\n");
				
				// save result into the memory
				mem_set(first_num, 0, NUMBER_LEN);
				number_from_string(first_num, first_tmp, second_tmp, result_str, number_len(result_str));
				if(ch == 'M')
				{
					Type("M+\r\n");
					memory_add(first_num);
				}
				
				if(ch == 'N')
				{
					Type("M-\r\n");
					memory_sub(first_num);
				}
				
				LCD_Print_char('M',0,0);
			}
		}
	}
}

void do_state_2(state_t * state) 
{
	unsigned char ch;		
	char loop;
	bit is_mem = 1;
	
	Type("STATE_2\r\n");
	
	loop = 1;
	while(loop == 1)
	{
		if(scan_input(&ch))
		{
			if(is_numeric(ch) && state->length < NUMBER_LEN)
			{
				if(is_mem)
				{					
					state->length = 0;
					state->last_position_1 = 0;
					
					LCD_clean_data(0);
					is_mem = 0;
				}
				write_data(first_str_num+state->length, ch);
				LCD_Print(first_str_num, 0, state->last_position_1);
				
				state->length += 1;
				state->last_position_1 += 1;
			}
			
			if(is_operation(ch))
			{
				if(!is_mem)
				{
					byte_to_number(first_num, 0, 0);
					number_from_string(first_num, first_tmp, second_tmp, first_str_num, state->length);
				}
				
				state->operation = ch;
				state->length = 0;
				state->last_position_2 = 0;
				state->name = INPUT_SECOND;
				
				LCD_Print_char(ch,0,1);
				
				loop = 0;
			}
			
			// print number from memory
			if(ch == 'A')
			{
				Type("MR\r\n");
				
				number_to_string(memory, first_tmp, second_tmp, result_str, 100);
				LCD_Print(result_str, 0, number_len(result_str)-1);				
				
				state->length = number_len(result_str);
				state->last_position_1 = state->length - 1;
				
				byte_to_number(first_num, 0, 0);
				mem_cpy(first_num, memory, state->length);
				
				is_mem = 1;
			}
			
			if(ch == 'M' || ch == 'N')
			{
				Type("M+ or M-\r\n");
				
				LCD_Print_char('M',0,0);
				
				state->last_position_1 = 0;
				state->length = 0;
				
				is_mem = 1;
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

unsigned char number_len(unsigned char xdata *s)
{
	unsigned char i, ch, len;
	len = 0;
	for(i = 0; i < NUMBER_LEN; i++)
	{
		ch = read_data(s+i);
		if ((ch >= '0' && ch <= '9') || ch == '.' || ch == '-')
			len++;
	}
	return len;
}

void memory_add(byte xdata *n)
{
	mem_set(memory_tmp, 0, NUMBER_LEN);
	mem_cpy(memory_tmp, memory, NUMBER_LEN);
	mem_set(memory, 0, NUMBER_LEN);
	add(n, memory_tmp, memory);	
}

void memory_sub(byte xdata *n)
{
	mem_set(memory_tmp, 0, NUMBER_LEN);
	mem_cpy(memory_tmp, memory, NUMBER_LEN);
	mem_set(memory, 0, NUMBER_LEN);
	sub(n, memory_tmp, memory);	
}