#ifndef _MOUSE_H_
#define _MOUSE_H_

#include <limits.h>
#include <string.h>
#include <errno.h>
#include <minix/drivers.h>
#include <minix/driver.h>
#include "i8042.h"

typedef enum {INIT, DRAW, COMP} state_t;
typedef enum {RDOW, RUP} ev_type_t;
typedef enum {PSLOPE,NSLOPE} slope_t;

typedef struct {
	slope_t slope;
	ev_type_t type;
	signed short x_delta;
	signed short y_delta;
	short length;
}event_t;

int clean_out();
int mouse_subscribe_int(int * mouse_id);
int mouse_unsubscribe_int(int * mouse_id);
int disable_mouse_interrupt();
int enable_mouse_interrupt();
int mouse_handler(unsigned long *mouse_packet);
int mouse_handler_remote(unsigned long *mouse_packet);
int mouse_packet_printer(unsigned long *mouse_packet);
int write_kbc_command(unsigned long cmd_byte);
int enable_mouse();
int disable_mouse();
int set_mouse_remote();
int set_mouse_stream();
long get_conf();
int reset_conf(unsigned long _byte);
state_t gesture_handler(event_t* mouse_event, state_t state);



#endif
