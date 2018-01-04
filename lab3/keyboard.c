#include "keyboard.h"

//In this file are all the reusable functions that can be useful to us in the future, with the
//exception of sys_inb_count(), that only is necessary in lab3

unsigned int counter = 0;

int sys_inb_count(port_t port, unsigned long *byte){
	counter++;
	return sys_inb(port, byte);
}

//Function that reads the status register
int read_statReg(unsigned long *_byte){
	if (sys_inb_count(STAT_REG,_byte) != 0){
		printf("Error: Failed to read the status\n");
		return 1;
	}
	return 0;
}

//Function that writes to the control register
int write_ctrlReg(unsigned long _byte){
	if (sys_outb(CTRL_REG,_byte) != 0){
		printf("Error: Failed to write to the control\n");
    	return 1;
	}
	return 0;
}

//Function that writes to the output buffer
int write_outputBuffer(unsigned long _byte){
	if (sys_outb(OUT_BUFF,_byte) != 0){
		printf("Error: Failed to write to the output buffer\n");
    	return 1;
	}
	return 0;
}

//Function that reads the input buffer
int read_inputBuffer(unsigned long *_byte){
	if (sys_inb_count(IN_BUFF,_byte) != 0){
		printf("Error: Failed to read from the input buffer\n");
    	return 1;
	}
	return 0;
}


///////////////////////////////////Keyboard Functions//////////////////////////////////////

//Function that subscribes to the keyboard interrupts
int keyboard_subscribe_int(int * keyboard_id) {

	if(sys_irqsetpolicy(KEYBOARD_IRQ,IRQ_REENABLE | IRQ_EXCLUSIVE,keyboard_id) != 0){
		printf("Error: Unable to subscribe a notification\n");
		return 1;
	}
	if(sys_irqenable(keyboard_id) != 0){
		printf("Error: Failed to enable an interrupt\n");
		return 1;
	}
	return 0;
}

//Function that unsubscribes to the keyboard interrupts
int keyboard_unsubscribe_int(int * keyboard_id) {
	if(sys_irqdisable(keyboard_id) != 0){
	    	printf("Error: The program can't disable the interrupt of the associated keyboard hook id\n");
	    	return 1;
	}
    if(sys_irqrmpolicy(keyboard_id) != 0)
    {
    	printf("Error: The program can't unsubscribe the interrupt of the associated hook id\n");
    	return 1;
    }
	return 0;
}

//Function that disables the IH interrupts
int disable_interrupts(){

	unsigned long _byte;

	if(sys_outb(KBC_CMD_REG, CMD_READ) != 0){
		printf("Error: Failed to send read command\n");
		return 1;
	}
	if(sys_inb_count(OUT_BUFF, &_byte) != 0){
		printf("Error: Failed to read command byte\n");
		return 1;
	}
	_byte = _byte | CMD_DIS;

	if(sys_outb(KBC_CMD_REG, CMD_WRITE) != 0){
		printf("Error: Failed to send write command\n");
		return 1;
	}
	if(sys_outb(CMD_ARGS, _byte) != 0){
		printf("Error: Failed to send arguments\n");
		return 1;

	}
	return 0;
}

//Function that re-enables the IH interrupts
int enable_interrupts(){

	unsigned long _byte;

	if(sys_outb(KBC_CMD_REG, CMD_READ) != 0){
		printf("Error: Failed to send read command\n");
		return 1;
	}
	if(sys_inb_count(OUT_BUFF, &_byte) != 0){
		printf("Error: Failed to read command byte\n");
		return 1;
	}
	_byte = (_byte & CMD_ENABLE) | OBF_ENABLE;

	if(sys_outb(KBC_CMD_REG, CMD_WRITE) != 0){
		printf("Error: Failed to send write command\n");
		return 1;
	}
	if(sys_outb(CMD_ARGS, _byte) != 0){
		printf("Error: Failed to send arguments\n");
		return 1;

	}
	return 0;
}

//Function that handles the interrupt and updates the scancode
int keyboard_handler(unsigned long * scancode){
	static unsigned long last_code;
	unsigned long first_code = 0;
	unsigned long stat = 1;
	read_statReg(&stat);
	if((stat & OBF) == 0){
		return 0;
	}
	while( stat & OBF ) {
		sys_inb_count(STAT_REG, &stat); /* assuming it returns OK */
		/* loop while 8042 output buffer is empty */
		if((stat & OBF )) {
			sys_inb_count(OUT_BUFF, scancode); /* assuming it returns OK */

			if ( (stat & (PAR_ERR | TO_ERR)) == 0 ){

				if((*scancode & TWO_BYTE_CODE)  == TWO_BYTE_CODE){

					first_code = *scancode;

				}

			}


			else
				return 1;
		}
	}

	//Display the scancode correctly depending on its size (1 byte or 2 bytes)
	if(first_code == 0 && last_code != *scancode){
		if(MSB & *scancode)
			printf("Breakcode: 0x%x\n", *scancode);
		else{
			printf("Makecode: 0x%x\n",*scancode);
		}

	}
	else if (last_code != *scancode){
		last_code = *scancode;
		if(MSB & *scancode)
			printf("Breakcode: 0x%x 0x%x\n", first_code, *scancode);
		else{
			printf("Makecode: 0x%x 0x%x\n", first_code, *scancode);
		}
	}

	return 0;
}
