#include "mouse.h"
#include "serial_port.h"

//Clears the output buffer
int clean_out(){
	unsigned long cleaner,status;
	if(sys_inb(STAT_REG,&status) != 0){
		return 1;
			}
	while(status & OBF){
		sys_inb(OUT_BUFF,&cleaner);
		sys_inb(STAT_REG, &status);
	};
	return 0;
}

//Subscribes to the mouse interrupts
int mouse_subscribe_int(int * mouse_id) {

	if(sys_irqsetpolicy(MOUSE_IRQ,IRQ_REENABLE | IRQ_EXCLUSIVE,mouse_id) != 0){
		printf("Error: Unable to subscribe a notification\n");
		return 1;
	}
	if(sys_irqenable(mouse_id) != 0){
		printf("Error: Failed to enable an interrupt\n");
		return 1;
	}
	return 0;
}

//Enable mouse data reporting
int enable_mouse(){
	int cnt = 0;
	while(cnt < 5){ // Test 5 times if 0xD4 and the mouse enable command were both sent with success
		if(write_kbc_command(KBC_CMD_INIT) == 0 && write_kbc_command(MOUSE_ENABLE) == 0){
			return 0;
		}
		cnt++;
		tickdelay(micros_to_ticks(DELAY_US));
	}
	return 1; // Tested 5 times, and jumped out of the loop, send error
}

//Disable mouse data reporting
int disable_mouse(){
	int cnt = 0;
	while(cnt < 5){ // Test 5 times if 0xD4 and the mouse disable command were both sent with success
		if(write_kbc_command(KBC_CMD_INIT) == 0 && write_kbc_command(MOUSE_DISABLE) == 0){
			return 0;
		}
		cnt++;
		tickdelay(micros_to_ticks(DELAY_US));
	}
	return 1; // Tested 5 times, and jumped out of the loop, send error

}

// Set mouse to remote mode
int set_mouse_remote(){
	if(write_kbc_command(SET_REMOTE) != 0){
		printf("Error: Unable to set mouse to remote mode\n");
		return 1;
	}
	return 0;
}

// Set mouse to stream mode
int set_mouse_stream(){
	if(write_kbc_command(SET_STREAM) != 0){
		printf("Error: Unable to set mouse to stream mode\n");
		return 1;
	}
	return 0;
}

// Disable the mouse interrupts modifying the command byte
int disable_mouse_interrupt(){

	unsigned long _byte;

	if(sys_outb(KBC_CMD_REG, CMD_READ) != 0){
		printf("Error: Failed to send read command\n");
		return 1;
	}
	if(sys_inb(OUT_BUFF, &_byte) != 0){
		printf("Error: Failed to read command byte\n");
		return 1;
	}
	_byte = _byte & CMD_MOUSE_DIS;

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


// Returns the command byte's configuration
long get_conf(){

	unsigned long _byte;

	if(sys_outb(KBC_CMD_REG, CMD_READ) != 0){
		printf("Error: Failed to send read command\n");
		return 1;
	}
	if(sys_inb(OUT_BUFF, &_byte) != 0){
		printf("Error: Failed to read command byte\n");
		return 1;
	}
	return _byte;
}


// Used to reset the mouse configuration to the given configuration
int reset_conf(unsigned long _byte){
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


// Enable the mouse interrupts modifying the command byte
int enable_mouse_interrupt(){

	unsigned long _byte;

	if(sys_outb(KBC_CMD_REG, CMD_READ) != 0){
		printf("Error: Failed to send read command\n");
		return 1;
	}
	if(sys_inb(OUT_BUFF, &_byte) != 0){
		printf("Error: Failed to read command byte\n");
		return 1;
	}
	_byte = (_byte&ENABLE_ALL) | CMD_MOUSE_EN |OBF_ENABLE;

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


//Writes a command to the mouse
int write_kbc_command(unsigned long cmd_byte){
	int error_counter = 0;
	unsigned long mouse_ack;
	while(error_counter < 5){ // Tries 5 times before giving up
		sys_outb(KBC_CMD_REG, KBC_CMD_INIT);
		sys_outb(IN_BUFF,cmd_byte);
		tickdelay(micros_to_ticks(DELAY_US));
		sys_inb(OUT_BUFF,&mouse_ack);
		if (mouse_ack != NACK || mouse_ack != ERROR){
			break;
		}
		tickdelay(micros_to_ticks(DELAY_US));
		error_counter++;
	}

	if(error_counter == 5){ // Tried 5 times, send error
		return 1;
	}

	return 0;

}



//Function that unsubscribes to the mouse interrupts
int mouse_unsubscribe_int(int * mouse_id) {
	if(sys_irqdisable(mouse_id) != 0){
	    	printf("Error: The program can't disable the interrupt of the associated mouse hook id\n");
	    	return 1;
	}
    if(sys_irqrmpolicy(mouse_id) != 0)
    {
    	printf("Error: The program can't unsubscribe the interrupt of the associated mouse hook id\n");
    	return 1;
    }
	return 0;
}

// Reads from the output buffer
int read_outputBuffer(unsigned long *_byte){
	if (sys_inb(OUT_BUFF,_byte) != 0){
		printf("Error: Failed to read to the output buffer\n");
    	return 1;
	}
	return 0;
}

// In case the number (in binary) is negative, this converts it to positive
long complement(unsigned long h_value){
	long f_value = h_value;
	if(MSB & h_value){
		f_value -= MAX_BYTE_VALUE;
	}
	return f_value;
}

// Handles mouse interrupts
int mouse_handler(unsigned long *mouse_packet){
	unsigned long status;
	static unsigned int counter = 0; // static counter variable used to keep track of the current array index
	sys_inb(STAT_REG,&status);
	if(((status & OBF) && (status & MOUSE_DATA)) == 0){
		return -1;
	}
	unsigned long _byte;
	if(read_outputBuffer(&_byte) != 0)
		return 1;

	if(counter == 0 && (MOUSE_BYTE1 & _byte)){ // Test if the first byte of the packet has bit(3) set to 1
		mouse_packet[0] = _byte;
		counter++;
	}
	else if(counter == 1){
		mouse_packet[counter] = _byte;
		counter++;
	}
	else if(counter >= 2){
		mouse_packet[counter] = _byte;
		counter = 0;
		return 0; // If the function returns 0, then it can print the configuration
	}

	return 1;
}

// Handles the mouse information while in remote mode
int mouse_handler_remote(unsigned long *mouse_packet){
	unsigned long _byte;
	unsigned int i;
	clean_out(); // Clear the output buffer
	write_kbc_command(READ_DATA); // Sends the read data command
	for(i = 0; i < 3;i++){

		if(read_outputBuffer(&_byte) != 0)
			return 1;
		if(i == 0 && (MOUSE_BYTE1 & _byte)){ // Test if the first byte of the packet has bit(3) set to 1
			mouse_packet[0] = _byte;
		}
		else if(i == 1 || i == 2){
			mouse_packet[i] = _byte;
		}
		else{
			return 1;
		}
	}
	return 0; // If the function returns 0, then it can print the configuration
}

// Handler for the mouse_test_gesture
state_t gesture_handler(event_t * mouse_event, state_t state){
	switch (state) {
		case INIT:
			if( mouse_event->type == RDOW ){
				state = DRAW;
			}
			break;
		case DRAW:
			if( mouse_event->type == RDOW ) {
							if(mouse_event->length > 0){ // Se foi fornecido um length positivo
								if ((mouse_event->x_delta > mouse_event->length) && mouse_event->slope == PSLOPE){
									state = COMP;
								}
							}
							else{ // Se foi fornecido um length negativo
								if ((mouse_event->x_delta < mouse_event->length) && mouse_event->slope == PSLOPE){
									state = COMP;
								}
							}
					}
			else if( mouse_event->type == RUP ){ // Stopped pressing the right mouse button
						state = INIT;
						mouse_event->x_delta = 0;
						mouse_event->y_delta = 0;
					}
			break;
		default:
			break;
	}
	return state;
}

// Prints the array given as a mouse configuration
int mouse_packet_printer(unsigned long *mouse_packet){
	unsigned int j;
	for(j = 0; j < 3; j++){
			printf("B%d=0x%x ", j+1, mouse_packet[j]);
		}

		printf("LB=%d ", (mouse_packet[0] & BIT(0)));

		if(mouse_packet[0] & BIT(2)){
			printf("MB=1 ");
		}
		else
			printf("MB=0 ");

		if(mouse_packet[0] & BIT(1)){
			printf("RB=1 ");
		}
		else
			printf("RB=0 ");

		if(mouse_packet[0] & BIT(6)){
			printf("XOV=1 ");
		}
		else
			printf("XOV=0 ");

		if(mouse_packet[0] & BIT(7)){
			printf("YOV=1 ");
		}
		else
			printf("YOV=0 ");

		if(mouse_packet[0] & BIT(4)){ // If the x value is negative
			printf("X=%d ", complement(mouse_packet[1]));

		}
		else{
			printf("X=%d ", mouse_packet[1]);
		}

		if(mouse_packet[0] & BIT(5)){ // If the y value is negative
			printf("Y=%d\n ", complement(mouse_packet[2]));
		}
		else{
			printf("Y=%d\n ", mouse_packet[2]);
		}


		return 0;
}
