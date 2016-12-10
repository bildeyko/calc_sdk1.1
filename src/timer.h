#ifndef _TIMER_H
#define _TIMER_H

unsigned char ledss = 0x80; 

void set_vector(unsigned char xdata * address, void * vector);
void init_timer_0();
void disable_timer_0();
void T0_ISR(void) interrupt 1;

void init_timer_2();
void disable_timer_2();
void T2_ISR(void) interrupt 2;

unsigned long get_ms_counter();
void clear_ms_counter();

#endif //_TIMER_H