#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_


#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/driver.h>
#include <minix/com.h>
#include <minix/sysutil.h>
#include "i8042.h"

/**
 * @brief      Reads the status register.
 *
 * @param      _byte  The status byte
 *
 * @return     0 is no errors, otherwise 1
 */
int read_statReg(unsigned long *_byte);

/**
 * @brief      Writes in the control register.
 *
 * @param[in]  _byte  The control byte
 *
 * @return     0 is no errors, otherwise 1
 */
int write_ctrlReg(unsigned long _byte);

/**
 * @brief      Writes in  the output buffer.
 *
 * @param[in]  _byte  The byte
 *
 * @return     0 is no errors, otherwise 1
 */
int write_outputBuffer(unsigned long _byte);

/**
 * @brief      A regular sys_inb() but with a call counter
 *
 * @param[in]  port  The port
 * @param      byte  The byte
 *
 * @return     0 is no errors, otherwise 1
 */
int sys_inb_count(port_t port, unsigned long *byte);

/**
 * @brief      Reads from input buffer.
 *
 * @param      _byte  The byte
 *
 * @return     0 is no errors, otherwise 1
 */
int read_inputBuffer(unsigned long *_byte);

/**
 * @brief      Subscribes to the keyboard interrupts
 *
 * @param      keyboard_id  The keyboard identifier
 *
 * @return     0 is no errors, otherwise 1
 */
int keyboard_subscribe_int(int * keyboard_id);

/**
 * @brief      Unubscribes to the keyboard interrupts
 *
 * @param      keyboard_id  The keyboard identifier
 *
 * @return     0 is no errors, otherwise 1
 */
int keyboard_unsubscribe_int(int * keyboard_id);

/**
 * @brief      Handles the keyboard interrupts
 *
 * @param      scancode  The scancode
 *
 * @return     0 is no errors, otherwise 1
 */
int keyboard_handler(unsigned long * scancode);

/**
 * @brief      Disables the interrupts.
 *
 * @return     0 is no errors, otherwise 1
 */
int disable_interrupts();

/**
 * @brief      Enables the interrupts.
 *
 * @return     0 is no errors, otherwise 1
 */
int enable_interrupts();

extern unsigned int counter;

#endif
