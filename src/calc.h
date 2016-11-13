#ifndef _CALC_H
#define _CALC_H

struct state;
//typedef void (*state_func_t)(struct state *);

typedef enum {
  INITIAL = 0,
	FIRST,
	SECOND,
	THIRD,
	FOURTH
} state_name_t;

typedef struct state
{
	//state_func_t * func;
	state_name_t name;
	unsigned char position;
	unsigned char operation;
	
	char last_position_1;
	char last_position_2;
	// data
} state_t;

//void run_state(state_t *);

void do_state_initial(state_t *);
void do_state_1(state_t *);
void do_state_2(state_t *);
void do_state_3(state_t *);
void do_state_4(state_t *);

char is_numeric(unsigned char);
char is_operation(unsigned char);
char is_equal(unsigned char);

#endif //_CALC_H
