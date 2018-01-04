#ifndef _UART_MACROS_H_
#define _UART_MACROS_H_

#define BIT(n)      (0x01<<(n)) /**< @brief Set the bit of index n to one */

#define SP_DELAY    10000 /**< @brief Small tick delay */

#define COM1              0x3f8 /**< @brief The base address of COM1*/

#define COM1_IRQ              4

#define RBR               0x3F8 /**< @brief The address of the Receiver Buffer Register */
#define THR               0x3F8 /**< @brief The address of the Transmitter Holding Register */
#define IER               0x3F9 /**< @brief The address of the Interrupt Enable Register */
#define IIR               0x3FA /**< @brief The address of the Interrupt Identification Reg. */
#define LSR               0x3FD /**< @brief The address of the Line Status Register */

//LSR
#define RECEIVER_DATA    BIT(0) /**< @brief Set to 1 when there is data for receiving */
#define OVERRUN_ERROR    BIT(1) /**< @brief Set to 1 when a characters received is overwritten by another one */
#define PARITY_ERROR     BIT(2) /**< @brief Set to 1 when a character with a parity error is received */
#define FRAMING_ERROR    BIT(3) /**< @brief Set to 1 when a received character does not have a valid Stop bit */
#define THR_EMP          BIT(5) /**< @brief When set, means that the UART is ready to accept a new character for transmitting */

//IER
#define RD_EN            BIT(0) /**< @brief Enables the Received Data Available Interrupt */
#define THR_EN           BIT(1) /**< @brief Enables the Transmitter Holding Register Empty Interrupt */
#define RLS_EN           BIT(2) /**< @brief Enables the Receiver Line Status Interrupt This event is generated when there is a change in the state of bits 1 to 4, i.e. the error bits, of the LSR */

//IIR
#define RLS     (BIT(1)|BIT(2)) /**< @brief Receiver Line Status Interrupt pending prioritized */
#define RD               BIT(2) /**< @brief Recived Data Available Interrupt pending prioritized */
#define IIR_THR          BIT(1) /**< @brief Transmitter Holding Register Empty Interrupt pending prioritized */


#endif
