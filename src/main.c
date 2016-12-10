#include "fixedPoint.h"
#include "mem_ops.h"
#include "fixed_point_test.h"
#include "calc.h"
#include "lcd.h"
#include "sio.h"
#include "max.h"

#include "timer.h"
#include "aduc812.h"

//unsigned char ledss = 0x80; 

void calc();

/*void WriteLED(unsigned char value)
{
	WriteMax(7, value);
}*/

// Init timer 0 with 1000Hz
/*void init_timer_0()
{	
	//TCON = 0x00;
	TMOD = (TMOD & 0xF0) | 0x01;
	TH0 = 0xFC;		// init timer 0
	TL0 = 0x67;	
	//TCON = 0x10;
	TR0 = 1; 
} */

/*void T0_ISR(void) interrupt 1
{
	//global_time++;
	TH0 = 0xFC;
	TL0 = 0x67;

	WriteLED(ledss);
	ledss = ledss >> 1;
	if(ledss == 0x00)
		ledss = 0x80;
	
	//TH0 = 0xDC;
	//TL0 = 0x00;
}*/

void main(){	
	InitSIO(S9600, 0);
  Type("Hello!\r\n");

	//begin_test();
	calc();
}

void calc() {
	state_t state;
	unsigned long time;
	
	Type("Calc()\r\n");
	
	state.name = INITIAL;
	state.length = 0;
	state.last_position_1 = 0;
	state.last_position_2 = 0;
	
	InitLCD();
	
	init_timer_2();
	set_vector(0x200B, (void *) T0_ISR); // wait interrupt of Timer 0 overflow
	set_vector(0x202B, (void *) T2_ISR); // wait interrupt of Timer 2 overflow
	EA = 1;
	
	Type("After init_timer_0\r\n");
	
	while(1) {
		//WriteLED(ledss);
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