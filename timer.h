#ifndef _TIMER_H_
#define _TIMER_H_

char TIMER1_register(unsigned int interval, void (*callback)(void));
void TIMER1_unregister(void);

#endif  // _TIMER_H_
