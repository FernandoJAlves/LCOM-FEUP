#ifndef _MOUSE_H_
#define _MOUSE_H_

#include <limits.h>
#include <string.h>
#include <errno.h>
#include <minix/drivers.h>
#include <minix/driver.h>
#include "i8042.h"


typedef enum {INIT, DRAW, COMP} state_t; /**< @brief The state of the drawing */
typedef enum {RDOW, RUP} ev_type_t; /**< @brief Tells if the right mouse button if pressed */
typedef enum {PSLOPE,NSLOPE} slope_t; /**< @brief Tells if the slope is positive or negative */

typedef struct {
	slope_t slope; /**< @brief The state of the slope */
	ev_type_t type; /**< @brief Tells if the right mouse button if pressed */
	signed short x_delta; /**< @brief The x variation of the mouse movement */
	signed short y_delta; /**< @brief The y variation of the mouse movement */
	short length; /**< @brief Length needed */
}event_t;

/**
 * @brief      Clears the output buffer
 *
 * @return     0 if no errors have occurred, otherwise 1
 */
int clean_out();

/**
 * @brief      Subscribes to the mouse interrupts
 *
 * @param      mouse_id  The mouse identifier
 *
 * @return     0 if no errors have occurred, otherwise 1
 */
int mouse_subscribe_int(int * mouse_id);

/**
 * @brief      Unsubscribes to the mouse interrupts
 *
 * @param      mouse_id  The mouse identifier
 *
 * @return     0 if no errors have occurred, otherwise 1
 */
int mouse_unsubscribe_int(int * mouse_id);

/**
 * @brief      Disables the mouse interrupts
 *
 * @return     0 if no errors have occurred, otherwise 1
 */
int disable_mouse_interrupt();

/**
 * @brief      Enables the mouse interrupts
 *
 * @return     0 if no errors have occurred, otherwise 1
 */
int enable_mouse_interrupt();

/**
 * @brief      Handles the mouse interrupts
 *
 * @param      mouse_packet  The mouse packet
 *
 * @return     0 if no errors have occurred, otherwise 1
 */
int mouse_handler(unsigned long *mouse_packet);

/**
 * @brief      Handles the mouse interrupts in remote mode
 *
 * @param      mouse_packet  The mouse packet
 *
 * @return     0 if no errors have occurred, otherwise 1
 */
int mouse_handler_remote(unsigned long *mouse_packet);

/**
 * @brief      Prints the mouse packets in the correct format
 *
 * @param      mouse_packet  The mouse packet
 *
 * @return     0 if no errors have occurred, otherwise 1
 */
int mouse_packet_printer(unsigned long *mouse_packet);

/**
 * @brief      Writes a kbc command
 *
 * @param[in]  cmd_byte  The command byte
 *
 * @return     0 if no errors have occurred, otherwise 1
 */
int write_kbc_command(unsigned long cmd_byte);

/**
 * @brief      Enables the mouse
 *
 * @return     0 if no errors have occurred, otherwise 1
 */
int enable_mouse();

/**
 * @brief      Disables the mouse
 *
 * @return     0 if no errors have occurred, otherwise 1
 */
int disable_mouse();

/**
 * @brief      Sets the mouse remote
 *
 * @return     0 if no errors have occurred, otherwise 1
 */
int set_mouse_remote();

/**
 * @brief      Sets the mouse stream
 *
 * @return     0 if no errors have occurred, otherwise 1
 */
int set_mouse_stream();

/**
 * @brief      Gets the configuration
 *
 * @return     The configuration
 */
long get_conf();

/**
 * @brief      Resets the configuration to the given byte
 *
 * @param[in]  _byte  The byte
 *
 * @return     0 if no errors have occurred, otherwise 1
 */
int reset_conf(unsigned long _byte);

/**
 * @brief      Updates the state depending on the mouse_event
 *
 * @param      mouse_event  The mouse event
 * @param[in]  state        The state
 *
 * @return     The updated state
 */
state_t gesture_handler(event_t* mouse_event, state_t state);

/**
 * @brief      Converts a 1 byte value to its 2's complement format
 *
 * @param[in]  h_value  The h value
 *
 * @return     The complement value
 */
long complement(unsigned long h_value);

#endif
