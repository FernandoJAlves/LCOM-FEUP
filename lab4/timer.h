#ifndef __TIMER_H
#define __TIMER_H


int timer_set_frequency(unsigned char timer, unsigned long freq);


int timer_subscribe_int(void );


int timer_unsubscribe_int();


void timer_int_handler();


int timer_get_conf(unsigned char timer, unsigned char *st);


int timer_display_conf(unsigned char conf);


int timer_test_time_base(unsigned long freq);

int timer_test_config(unsigned char timer);

//Global variables
unsigned int timer_counter;
int timer_id;

#endif /* __TIMER_H */
