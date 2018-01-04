#include "test3.h"

//Functions prototypes
unsigned long keyboard_handler_asm();


//Global Variables
int keyboard_id = 1;


int kbd_test_scan(unsigned short assembly) {
	//Test if the user input is valid
	if(assembly != 0 && assembly != 1){
		printf("Error: Invalid argument for scan function\n");
		return 1;
	}

	int ipc_status;
	message msg;
	unsigned long irq_set = BIT(keyboard_id);
	unsigned long r;
	unsigned long scancode = 0;
	int double_byte = 0;
	unsigned long first_code;

	//Subscribe to the keyboard interrupts
	if(keyboard_subscribe_int(&keyboard_id) != 0){
		printf("Error: Unable to subscribe to the keyboard interrupts\n");
	    return 1;
	}

	while(scancode != ESC_BREAK) {
			     /* Get a request message. */
			    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
			        printf("driver_receive failed with: %d\n", r);
			        continue;
			    }
			    if (is_ipc_notify(ipc_status)) { /* received notification */
			        switch (_ENDPOINT_P(msg.m_source)) {
			            case HARDWARE: /* hardware interrupt notification */
			                if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */
			                	if(assembly == 0){
			                		//Handle the interrupt in C
			                        keyboard_handler(&scancode);
			                	    }

			                	else if(assembly == 1){
			                		//Handle the interrupt in assembly
			                		if((scancode = keyboard_handler_asm()) == -1){
			                			printf("Error: Unable to read scancode in assembly mode\n");
			                			return 1;
			                		}
			                		//Test if the scancode is 2 bytes long
			                		if((scancode & TWO_BYTE_CODE) == TWO_BYTE_CODE){
			                			first_code = scancode;
			                			double_byte = 1;
			                		}
			                		//Display if the scancode is 1 byte long
			                		else if(double_byte == 0)
			                				if(MSB & scancode)
			                					printf("Breakcode: 0x%x\n", scancode);
			                				else{
			                					printf("Makecode: 0x%x\n",scancode);
			                				}
			                		//Display if the scancode is 2 bytes long
			                		else if( double_byte == 1){
			                			if(MSB & scancode)
			                			  printf("Breakcode: 0x%x 0x%x\n", first_code, scancode);
			                	        else{
			                			  printf("Makecode: 0x%x 0x%x\n",first_code, scancode);
			                			}
			                			double_byte = 0;
			                		}
			                	}
			                	tickdelay(micros_to_ticks(DELAY_US));
			                }
			                break;
			            default:
			                break; /* no other notifications expected: do nothing */
			        }
			    } else { /* received a standard message, not a notification */
			        /* no standard messages expected: do nothing */
			    }
			 }

	//Unsubscribe to the keyboard interrupts
	if(keyboard_unsubscribe_int(&keyboard_id) != 0){
				printf("Error: Unable to unsubscribe the keyboard\n");
			    return 1;
		}
	if(assembly == 0){
	printf("sys_inb() was called %d times\n",counter);
	}
	counter = 0;
	return 0;
}


int kbd_test_poll() {
	unsigned long scancode = 0;

	//Disable the interrupts
	//if(disable_interrupts() != 0){
	//	printf("Error: Failed to disable the interrupts\n");
	//}

	while(scancode != ESC_BREAK){
		keyboard_handler(&scancode);
		tickdelay(micros_to_ticks(DELAY_US));
	}

	//Re-enable the interrupts
	if(enable_interrupts() != 0){
			printf("Error: Failed to enable the interrupts\n");
		}
	printf("sys_inb() was called %d times\n",counter);
	counter = 0; //Reset the counter
	return 0;
}

int kbd_test_timed_scan(unsigned short n) {
	//Test if the user input is valid
		if(n < 1){
			printf("Error: Invalid time. Time should be an unsigned integer\n");
			return 1;
		}

	int ipc_status;
	unsigned long scancode = 0;
	message msg;
	unsigned long irq_set_timer = BIT(timer_id);
	unsigned long irq_set_keyboard = BIT(keyboard_id);
	unsigned long r;

		//Subscribe to the interrupts of the timer and keyboard
		if(timer_subscribe_int() != 0){
			printf("Error: Unable to subscribe a timer notification\n");
			return 1;
		}
		if(keyboard_subscribe_int(&keyboard_id) != 0){
				printf("Error: Unable to subscribe the keyboard notification\n");
			    return 1;
		}


		while( (timer_counter/60 < n) && (scancode != ESC_BREAK)) {
		     /* Get a request message. */
		    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
		        printf("driver_receive failed with: %d\n", r);
		        continue;
		    }
		    if (is_ipc_notify(ipc_status)) { /* received notification */
		        switch (_ENDPOINT_P(msg.m_source)) {
		            case HARDWARE: /* hardware interrupt notification */
		                if (msg.NOTIFY_ARG & irq_set_timer) { /* subscribed interrupt */
		                	//Handle the timer interrupt
		                	timer_int_handler();
		                }
		                if (msg.NOTIFY_ARG & irq_set_keyboard) {
		                	//Handle the keyboard interrupt
		                	keyboard_handler(&scancode);
		                	timer_counter = 0;
		                }
		                break;
		            default:
		                break; /* no other notifications expected: do nothing */
		        }
		    } else { /* received a standard message, not a notification */
		        /* no standard messages expected: do nothing */
		    }
		 }

		//Unsubscribe to the timer interrupts
		if(timer_unsubscribe_int() != 0){
			printf("Error: failed to unsubscribe\n");
		}

		//Test what caused the program to end
		if(timer_counter/60 == n){
			printf("Program ended: timeout\n");
		}
		else if(scancode == ESC_BREAK){
			printf("Program ended: Escape was pressed\n");
		}
		else{
			printf("Program ended: Unknown reason\n");
		}
		counter = 0; //Reset the counter
		return 0;
}
