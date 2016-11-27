#include "fixedPoint.h"
#include "mem_ops.h"
#include "fixed_point_test.h"
#include "calc.h"
#include "lcd.h"

void calc();

void main(){
	//begin_test();
	calc();
}

void calc() {
	state_t state;
	
	state.name = INITIAL;
	state.length = 0;
	state.last_position_1 = 0;
	state.last_position_2 = 0;
	
	InitLCD(); 
	
	while(1) {
		switch(state.name) {
			case INITIAL:
				do_state_initial(&state);
				break;
			case INPUT_FIRST:
				do_state_1(&state);
				break;
			case INPUT_SECOND:
				do_state_3(&state);
				break;
			case CALCULATE:
				do_state_4(&state);
				break;
			default:
				break;
		}
	}
}