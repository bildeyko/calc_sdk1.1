#include "aduc812.h"
#include "timer.h"
#include "sio.h"
#include "max.h"
#include "din.h"

unsigned long global_time = 0; 

void set_vector(unsigned char xdata * address, void * vector)
{
	unsigned char xdata * tmpVector;
	
	*address = 0x02;
	tmpVector = (unsigned char xdata *)(address + 1);
	*tmpVector = (unsigned char)((unsigned short)vector >> 8);
	++tmpVector;
	*tmpVector = (unsigned char) vector;
}

// Init timer 0 with 1000Hz
void init_timer_0()
{	
	TMOD = (TMOD & 0xF0) | 0x01; 		// init timer 0
	TH0 = 0xFC;
	TL0 = 0x67;	
	TR0 = 1; // enable timer 0
} 

void disable_timer_0()
{
	TR0 = 0;
}

void T0_ISR(void) interrupt 1
{
	global_time++;
	TH0 = 0xFC;
	TL0 = 0x67;
}

void init_timer_2()
{	
	RCLK = 0;
	TCLK = 0;
	CAP2 = 1;
	TR2 = 1; // enable timer 1
	
} 

void disable_timer_2()
{
	TR2 = 0;
}

void T2_ISR(void) interrupt 2
{
	TF2 = 0;
	write_led(ledss);
	ledss = ledss >> 1;
	if(ledss == 0x00)
		ledss = 0x80;
}

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