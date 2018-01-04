#ifndef _SERIAL_PORT_H_
#define _SERIAL_PORT_H_

/**
 * @brief      Subscribes to the uart interrupts
 *
 * @param      uart_id  The uart identifier
 *
 * @return     0 if no errors occurred during execution
 */
int serial_port_subscribe_int(int * uart_id);

/**
 * @brief      Unsubscribes to the uart interrupts
 *
 * @param      uart_id  The uart identifier
 *
 * @return     0 if no errors occurred during execution
 */
int serial_port_unsubscribe_int(int * uart_id);

/**
 * @brief      Reads the Interrupt Identification Reg
 *
 * @param      iir_byte  The iir byte
 *
 * @return     0 if no errors occurred during execution
 */
int read_IIR(unsigned long * iir_byte);

/**
 * @brief      Reads the Line Status Register
 *
 * @param      lsr_byte  The lsr byte
 *
 * @return     0 if no errors occurred during execution
 */
int read_LSR(unsigned long * lsr_byte);

/**
 * @brief      Reads the Receiver Buffer Register
 *
 * @param      _byte  The byte
 *
 * @return     0 if no errors occurred during execution
 */
int read_RBR(unsigned long *_byte);

/**
 * @brief      Writes to the Transmitter Holding Register
 *
 * @param[in]  _byte  The byte
 *
 * @return     0 if no errors occurred during execution
 */
int write_THR(unsigned long _byte);

/**
 * @brief      Handles the uart interrupts
 *
 * @param      _byte  The byte
 *
 * @return     0 if no errors occurred during execution
 */
int uart_handler(unsigned long *_byte);

/**
 * @brief      Cleans the Receiver Buffer Register
 *
 * @return     0 if no errors occurred during execution
 */
int clean_RBR();

/**
 * @brief      Waits for a hunter
 *
 * @return     0 if no errors occurred during execution
 */
int duck_sync_prepare();

/**
 * @brief      Waits for a duck
 *
 * @return     0 if no errors occurred during execution
 */
int hunter_sync_prepare();

#endif
