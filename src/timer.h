#ifndef _TIMER_H
#define _TIMER_H

unsigned char ledss = 0x01; 

void init_timer_0();
//void T0_ISR(void) __interrupt 1;

unsigned long get_ms_counter();
void clear_ms_counter();

#endif //_TIMER_H