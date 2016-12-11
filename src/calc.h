#ifndef _CALC_H
#define _CALC_H

struct state;
//typedef void (*state_func_t)(struct state *);

typedef enum {
  INITIAL = 0,
	INPUT_FIRST,
	INPUT_SECOND,
	CALCULATE
} state_name_t;

typedef struct state
{
	state_name_t name;
	unsigned char length; // length of current input string
	unsigned char length_1; // temporary length of 1st number
	unsigned char length_2; // temporary length of 2nd number
	unsigned char operation; // operation char
	char point;
	
	char last_position_1; // index of last printed digital in 1st number
	char last_position_2; // index of last printed digital in 2nd number
} state_t;

void hello();

void do_state_initial(state_t *);
void do_state_1(state_t *);
void do_state_3(state_t *);
void do_state_4(state_t *);

bit scan_input(char *ch);
char is_numeric(unsigned char);
char is_operation(unsigned char);
char is_equal(unsigned char);
unsigned char number_len(unsigned char xdata *s);

void memory_add(unsigned char xdata *n);
void memory_sub(unsigned char xdata *n);

#endif //_CALC_H
