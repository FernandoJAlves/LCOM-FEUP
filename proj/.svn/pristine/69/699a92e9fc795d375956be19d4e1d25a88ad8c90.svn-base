#ifndef _LCOM_MACROS_H_
#define _LCOM_MACROS_H_

#define BIT(n)    (0x01<<(n)) /**< @brief Sets the bit number n to 1*/

#define KEYBOARD_IRQ         	1		/**< @brief Keyboard IRQ */
#define MOUSE_IRQ           	12		/**< @brief Mouse IRQ */
#define STAT_REG             	0x64 	/**< @brief Status Register */
#define CTRL_REG             	0x64 	/**< @brief Control Register */
#define KBC_CMD_REG          	0x64 	/**< @brief Keyboard command register */
#define CMD_ARGS			 	0x60 	/**< @brief Arguments to commands address */
#define CMD_READ			 	0X20 	/**< @brief Read command byte */
#define CMD_WRITE			 	0x60 	/**< @brief Write to the command byte */
#define KBC_CMD_INIT         	0xd4 	/**< @brief Write byte do mouse */
#define OUT_BUFF             	0x60 	/**< @brief Output Buffer */
#define IN_BUFF              	0x60 	/**< @brief Input Buffer */
#define ESC_BREAK            	0x81	/**< @brief Breakcode of Escape key */
#define UP_MAKE                 0x48    /**< @brief Makecode of Up arrow key */
#define DOWN_MAKE               0x50    /**< @brief Makecode of Down arrow key */
#define LEFT_MAKE               0x4b    /**< @brief Makecode of Left arrow key */
#define RIGHT_MAKE              0x4d    /**< @brief Makecode of Right arrow key */
#define ENTER_BREAK             0x9c    /**< @brief Breakcode of Enter key */
#define MSB                  	0x80 	/**< @brief Most significant bit */
#define TWO_BYTE_CODE		 	0xe0 	/**< @brief Double byte scancode */


#define ENABLE_ALL           	0xcc 	/**< @brief Enable mouse and keyboard */
#define MOUSE_BYTE1     	 	BIT(3)  /**< @brief Test if Byte 1 has bit 3 set */
#define PAR_ERR		       	 	BIT(7)	/**< @brief Test if Byte 1 has bit 7 set */
#define TO_ERR				 	BIT(6)	/**< @brief Test if Byte 1 has bit 6 set */
#define CMD_DIS				 	BIT(4)  /**< @brief Disable keyboard interface mask */
#define CMD_MOUSE_DIS        	0xfd    /**< @brief Disable mouse interrupt */
#define CMD_MOUSE_EN         	BIT(1)  /**< @brief Enable mouse interrupt */
#define CMD_ENABLE			 	0xef    /**< @brief Enable keyboard interface mask */
#define OBF_ENABLE		 	 	BIT(0)  /**< @brief Enable interrupt on OBF from keyboard */
#define OBF                  	BIT(0)  /**< @brief Output buffer full */
#define ACK					 	0xFA 	/**< @brief Everything is OK */
#define NACK					0xFE 	/**< @brief Invalid byte */
#define ERROR					0xFC 	/**< @brief Second consecutive invalid byte */
#define MOUSE_ENABLE			0XF4 	/**< @brief Enable data reporting in stream only */
#define MOUSE_DISABLE			0XF5 	/**< @brief Disable data reporting in stream only */
#define SET_REMOTE              0xF0 	/**< @brief Set mouse to remote mode */
#define SET_STREAM              0xEA 	/**< @brief Set mouse to stream mode */
#define READ_DATA               0xEB 	/**< @brief Set data packet request */
#define MOUSE_DATA              BIT(5)  /**< @brief Tells if the byte is related to the mouse */

#define RIGHT_CLICK          	BIT(1) 	/**< @brief Right button of the mouse is pressed */

#define MAX_BYTE_VALUE 			256 	/**< @brief Max value a byte can hold */

#define DELAY_US    20000

#define LEFT_A                  0x1e   /**< @brief Makecode of A(left) */
#define UP_W                    0x11   /**< @brief Makecode of W(up) */
#define DOWN_S                  0x1f   /**< @brief Makecode of S(down) */
#define RIGHT_D                 0x20   /**< @brief Makecode of D(right) */
//#define R_MAKE                  0x13   /**< @brief Makecode of R */

#define	ONE_MAKE		        0x02	/**< @brief Makecode of 1 */
#define	TWO_MAKE	            0x03	/**< @brief Makecode of 2 */
#define	THREE_MAKE	            0x04	/**< @brief Makecode of 3 */
#define	FOUR_MAKE               0x05	/**< @brief Makecode of 4 */
#define	FIVE_MAKE	            0x06	/**< @brief Makecode of 5 */
#define	SIX_MAKE                0x07	/**< @brief Makecode of 6 */
#define	SEVEN_MAKE	            0x08	/**< @brief Makecode of 7 */
#define	EIGHT_MAKE	            0x09	/**< @brief Makecode of 8 */
#define	NINE_MAKE	            0x0a	/**< @brief Makecode of 9 */
#define ZERO_MAKE	            0x0b	/**< @brief Makecode of 0 */
#define	Q_MAKE	                0x10	/**< @brief Makecode of Q */
#define	W_MAKE	                0x11	/**< @brief Makecode of W */
#define	E_MAKE	                0x12	/**< @brief Makecode of E */
#define	R_MAKE                  0x13	/**< @brief Makecode of R */
#define	T_MAKE                  0x14	/**< @brief Makecode of T */
#define	Y_MAKE	                0x15	/**< @brief Makecode of Y */
#define	U_MAKE	                0x16	/**< @brief Makecode of U */
#define	I_MAKE	                0x17	/**< @brief Makecode of I */
#define	O_MAKE	                0x18	/**< @brief Makecode of O */
#define	P_MAKE	                0x19	/**< @brief Makecode of P */
#define	A_MAKE	                0x1e	/**< @brief Makecode of A */
#define	S_MAKE                  0x1f	/**< @brief Makecode of S */
#define	D_MAKE	                0x20	/**< @brief Makecode of D */
#define	F_MAKE	                0x21	/**< @brief Makecode of F */
#define	G_MAKE	                0x22	/**< @brief Makecode of G */
#define	H_MAKE	                0x23	/**< @brief Makecode of H */
#define	J_MAKE	                0x24	/**< @brief Makecode of J */
#define	K_MAKE	                0x25	/**< @brief Makecode of K */
#define	L_MAKE	                0x26	/**< @brief Makecode of L */
#define	Z_MAKE	                0x2c	/**< @brief Makecode of Z */
#define	X_MAKE	                0x2d	/**< @brief Makecode of X */
#define	C_MAKE	                0x2e	/**< @brief Makecode of C */
#define	V_MAKE	                0x2f	/**< @brief Makecode of V */
#define	B_MAKE	                0x30	/**< @brief Makecode of B */
#define	N_MAKE	                0x31	/**< @brief Makecode of N */
#define	M_MAKE	                0x32	/**< @brief Makecode of M */
#define BACKSPACE_MAKE	        0x0e	/**< @brief Makecode of BACKSPACE */
#define BACKSPACE_BREAK         0x8e	/**< @brief Breakcode of BACKSPACE */
#define SPACE_MAKE	            0x39	/**< @brief Makecode of SPACE */


#endif


