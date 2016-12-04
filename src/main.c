#include "fixedPoint.h"
#include "mem_ops.h"
#include "fixed_point_test.h"
#include "calc.h"
#include "lcd.h"
#include "sio.h"
#include "max.h"

#include "timer.h"
#include "aduc812.h"

void calc();

void WriteLED(unsigned char value)
{
	WriteMax(7, value);
}

void setVector(unsigned char xdata * address, void * vector)
{
	unsigned char xdata * tmpVector;
	
	*address = 0x02;
	tmpVector = (unsigned char xdata *)(address + 1);
	*tmpVector = (unsigned char)((unsigned short)vector >> 8);
	++tmpVector;
	*tmpVector = (unsigned char) vector;
}

/*void T0_ISR(void) __interrupt 1
{
	//global_time++;
	//TH0 = 0xFC;
	//TL0 = 0x67;
	
	//WriteLED(ledss);
	ledss = ledss << 1;
	if(ledss == 0x00)
		ledss = 0x01;
	
	//Type("T0_ISR\r\n");
	
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
	//unsigned long time;
	
	Type("Calc()\r\n");
	
	state.name = INITIAL;
	state.length = 0;
	state.last_position_1 = 0;
	state.last_position_2 = 0;
	
	InitLCD();
	
	//init_timer_0();
	//setVector(0x200B, (void *) T0_ISR); // wait interrupt of Timer 0 overflow
	//ET0 = 1; 
	//EA = 1;
	
	/*while(1)
	{
		WriteLED(ledss);
	}*/
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
			case ADD_SUB_MEM:
				do_state_2(&state);
				break;
			default:
				break;
		}
	}
}