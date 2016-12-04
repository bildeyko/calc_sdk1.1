#include "aduc812.h"
#include "timer.h"
#include "sio.h"

unsigned long global_time = 0; 


// Init timer 0 with 1000Hz
void init_timer_0()
{
	/*TCON = 0x00;	// disable timers 0 and 1
	TMOD = 0x01;	// set 16-bit mode for timer
	TH0 = 0xFC;		// init timer 0
	TL0 = 0x67;		//		with 1000Hz (Counts = 921, T = 64615)
	TCON = 0x10;	// enable timer 0*/
	
	TH0 = 0xFF; // 
	TL0 = 0xF0; //
	TMOD = 0x01; //
	TCON = 0x10; //
} 

/*void T0_ISR(void) __interrupt 1
{
	//global_time++;
	//TH0 = 0xFC;
	//TL0 = 0x67;

	ledss = ledss << 1;
	if(ledss == 0x00)
		ledss = 0x01;
	
	//TH0 = 0xDC;
	//TL0 = 0x00;
}*/

unsigned long get_ms_counter()
{
	unsigned long res;
	ET0 = 0;
	res = global_time;
	ET0 = 1;
	return res;
} 

void clear_ms_counter()
{
	ET0 = 0;
	global_time = 0;
	ET0 = 1;
}