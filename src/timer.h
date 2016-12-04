#ifndef _TIMER_H
#define _TIMER_H

extern void init_timer_0();
extern void T0_INT(void);

unsigned long get_ms_counter();
void clear_ms_counter();

#endif //_TIMER_H