#ifndef _LCOM_MACROS_H_
#define _LCOM_MACROS_H_

#define BIT(n)    (0x01<<(n))

#define KEYBOARD_IRQ         1
#define STAT_REG             0x64 // Status Register
#define CTRL_REG             0x64 // Control Register
#define KBC_CMD_REG          0x64 // Keyboard command register
#define CMD_ARGS			 0x60 // Arguments to commands address
#define CMD_READ			 0X20 // Read command byte
#define CMD_WRITE			 0x60 // Write to the command byte
#define OUT_BUFF             0x60 // Output Buffer
#define IN_BUFF              0x60 // Input Buffer
#define ESC_BREAK            0x81 // Breakcode of Escape key
#define MSB                  0x80 // Most significant bit
#define TWO_BYTE_CODE		 0xe0 // double byte scancode
#define PAR_ERR		     BIT(7)
#define TO_ERR			 BIT(6)
#define CMD_DIS				 BIT(4) // Disable keyboard interface mask
#define CMD_ENABLE			 0xef // Enable keyboard interface mask
#define OBF_ENABLE		 BIT(0) // Enable interrupt on OBF from keyboard
#define OBF                  BIT(0) //Output buffer full

#define DELAY_US    20000


#endif


