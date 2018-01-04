#ifndef _LCOM_MACROS_H_
#define _LCOM_MACROS_H_

#define BIT(n)    (0x01<<(n))

#define KEYBOARD_IRQ         	1
#define MOUSE_IRQ           	12
#define STAT_REG             	0x64 	// Status Register
#define CTRL_REG             	0x64 	// Control Register
#define KBC_CMD_REG          	0x64 	// Keyboard command register
#define CMD_ARGS			 	0x60 	// Arguments to commands address
#define CMD_READ			 	0X20 	// Read command byte
#define CMD_WRITE			 	0x60 	// Write to the command byte
#define KBC_CMD_INIT         	0xd4 	// Write byte do mouse
#define OUT_BUFF             	0x60 	// Output Buffer
#define IN_BUFF              	0x60 	// Input Buffer
#define ESC_BREAK            	0x81	// Breakcode of Escape key
#define MSB                  	0x80 	// Most significant bit
#define TWO_BYTE_CODE		 	0xe0 	// Double byte scancode


#define ENABLE_ALL           	0xcc 	// Enable mouse and keyboard
#define MOUSE_BYTE1     	 	BIT(3)  // Test if Byte 1 has bit 3 set
#define PAR_ERR		       	 	BIT(7)
#define TO_ERR				 	BIT(6)
#define CMD_DIS				 	BIT(4)  // Disable keyboard interface mask
#define CMD_MOUSE_DIS        	0xfd    // Disable mouse interrupt
#define CMD_MOUSE_EN         	BIT(1)  // Enable mouse interrupt
#define CMD_ENABLE			 	0xef    // Enable keyboard interface mask
#define OBF_ENABLE		 	 	BIT(0)  // Enable interrupt on OBF from keyboard
#define OBF                  	BIT(0)  // Output buffer full
#define ACK					 	0xFA 	// Everything is OK
#define NACK					0xFE 	// Invalid byte
#define ERROR					0xFC 	// Second consecutive invalid byte
#define MOUSE_ENABLE			0XF4 	// Enable data reporting in stream only
#define MOUSE_DISABLE			0XF5 	// Disable data reporting in stream only
#define SET_REMOTE              0xF0 	// Set mouse to remote mode
#define SET_STREAM              0xEA 	// Set mouse to stream mode
#define READ_DATA               0xEB 	// Set data packet request

#define RIGHT_CLICK          	BIT(1) 	// Right button of the mouse is pressed

#define MAX_BYTE_VALUE 			256

#define DELAY_US    20000


#endif


