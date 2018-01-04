#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_


#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/driver.h>
#include <minix/com.h>
#include <minix/sysutil.h>
#include "macros.h"
#include "timer.h"

int read_statReg(unsigned long *_byte);
int write_ctrlReg(unsigned long _byte);
int write_outputBuffer(unsigned long _byte);
int sys_inb_count(port_t port, unsigned long *byte);
int read_inputBuffer(unsigned long *_byte);
int keyboard_subscribe_int(int * keyboard_id);
int keyboard_unsubscribe_int(int * keyboard_id);
int keyboard_handler(unsigned long * scancode);
int disable_interrupts();
int enable_interrupts();

extern unsigned int counter;

#endif
