#include "test4.h"


int mouse_test_packet(unsigned short cnt){
		int ipc_status;
	    int counter = 0;
	    unsigned long mouse_packet[3];
		message msg;
		int mouse_id = 12;
		unsigned long irq_set = BIT(mouse_id);
		unsigned long r;
		if(mouse_subscribe_int(&mouse_id) != 0){
			printf("The program was unable to subscribe a mouse notification\n");
			return 1;
		}

		if(enable_mouse() != 0){
			printf("The program failed to enable the mouse data reporting\n");
			return 1;
		}
		clean_out(); // Clear the output buffer
		while(counter < cnt) {
		     /* Get a request message. */
		    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
		        printf("driver_receive failed with: %d\n", r);
		        continue;
		    }
		    if (is_ipc_notify(ipc_status)) { /* received notification */
		        switch (_ENDPOINT_P(msg.m_source)) {
		            case HARDWARE: /* hardware interrupt notification */
		                if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */
		                	// Calls the handler, and if it returns 0, then mouse_packet is ready for printing
		                	if(mouse_handler(mouse_packet) == 0){
		                		counter++;
		                		mouse_packet_printer(mouse_packet);
		                	}
		                }
		                break;
		            default:
		                break; /* no other notifications expected: do nothing */
		        }
		    } else { /* received a standard message, not a notification */
		        /* no standard messages expected: do nothing */
		    }
		 }
		printf("\n The program printed %d mouse configurations\n",cnt);
		if(disable_mouse() != 0){
			printf("The program failed to disable the mouse data reporting\n");
			return 1;
		}

		if(mouse_unsubscribe_int(&mouse_id) != 0){
					printf("The program was unable to unsubscribe a mouse notification\n");
					return 1;
				}
		clean_out(); // Clear the output buffer
		return 0;


}	

int mouse_test_async(unsigned short idle_time){
	//Test if the user input is valid
			if(idle_time < 1){
				printf("Error: Invalid time. Time should be an unsigned integer\n");
				return 1;
			}
	    int mouse_id = 12;
		int ipc_status;
		unsigned long mouse_packet[3];
		message msg;
		unsigned long irq_set_timer = BIT(timer_id);
		unsigned long irq_set_mouse = BIT(mouse_id);
		unsigned long r;

			//Subscribe to the interrupts of the timer and mouse
			if(timer_subscribe_int() != 0){
				printf("Error: Unable to subscribe a timer notification\n");
				return 1;
			}
			if(mouse_subscribe_int(&mouse_id) != 0){
				printf("The program was unable to subscribe a mouse notification\n");
				return 1;
			}
			//Enables the mouse data reporting
			if(enable_mouse() != 0){
				printf("The program failed to enable the mouse data reporting\n");
				return 1;
			}
			while(timer_counter/60 < idle_time) {
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
			                if (msg.NOTIFY_ARG & irq_set_mouse) {
			                	// Calls the handler, and if it returns 0, then mouse_packet is ready for printing
			                	if(mouse_handler(mouse_packet) == 0){
			                		mouse_packet_printer(mouse_packet);
			                		timer_counter = 0;
			                	}

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
			if(disable_mouse() != 0){
				printf("The program failed to disable the mouse data reporting\n");
				return 1;
			}

			if(mouse_unsubscribe_int(&mouse_id) != 0){
				printf("The program was unable to unsubscribe a mouse notification\n");
				return 1;
			}

			printf("Timeout: %d seconds have passed\n",idle_time);
			clean_out(); // Clears the output buffer before exiting
			return 0;
}	

int mouse_test_remote(unsigned long period, unsigned short cnt){
	int counter = 0;
	unsigned long mouse_packet[3];
	// Disable the mouse interrupts
	if(disable_mouse_interrupt() != 0){
				printf("Error: failed to disable the mouse interrupts\n");
				return 1;
	}
	// Enables data reporting (was necessary for the program to run correctly)
	if(enable_mouse() != 0){
	    		printf("Error: failed to enable data reporting mode\n");
	    		return 1;
	}
	// Disable data reporting
	if(disable_mouse() != 0){
		printf("Error: failed to disable data reporting mode\n");
		return 1;
	}
	// Sets the mouse to remote mode
	if(set_mouse_remote()!= 0){
		return 1;
	}
	clean_out(); // Clears the output buffer
    while(counter < cnt){
    	mouse_handler_remote(mouse_packet); // Calls the handler
    	mouse_packet_printer(mouse_packet); // Prints the configuration
    	tickdelay(micros_to_ticks(period*1000)); // Waits the time specified in the period argument
    	counter++;
    }
    // Re-set the mouse to stream mode
    if(set_mouse_stream() != 0){
    	return 1;
    }

    if(enable_mouse() != 0){
    		printf("Error: failed to enable data reporting mode\n");
    		return 1;
    }

    printf("\n The program printed %d mouse configurations\n",cnt);
    // Re-enable mouse interrupts
    if(enable_mouse_interrupt() != 0){
        			printf("Error: failed to enable the mouse interrupts\n");
        			return 1;
    }
    clean_out(); // Clear the output buffer
	return 0;
}	

int mouse_test_gesture(short length){
	int ipc_status;
	unsigned long mouse_packet[3];
	message msg;
	int mouse_id = 12;
	unsigned long irq_set = BIT(mouse_id);
	unsigned long r;
	event_t mouse_event;
	state_t state = INIT;
	mouse_event.x_delta = 0;
	mouse_event.y_delta = 0;
	mouse_event.length = length;
	mouse_event.slope = NSLOPE;
	// Subscribe to the mouse interrupts
	if(mouse_subscribe_int(&mouse_id) != 0){
		printf("The program was unable to subscribe a mouse notification\n");
		return 1;
	}
	// Enable data reporting
	if(enable_mouse() != 0){
		printf("The program failed to enable the mouse data reporting\n");
		return 1;
	}
	clean_out(); // Clears output buffer
	while(state != COMP) {
		/* Get a request message. */
		if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
			printf("driver_receive failed with: %d\n", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
				case HARDWARE: /* hardware interrupt notification */
					if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */
			           if(mouse_handler(mouse_packet) == 0){
			             mouse_packet_printer(mouse_packet);

			             if (mouse_packet[0] & RIGHT_CLICK){
			            	 mouse_event.x_delta += (signed char) mouse_packet[1]; // Add the packet x and y values to the total displacement
			            	 mouse_event.y_delta += (signed char) mouse_packet[2];
			            	 state = gesture_handler(&mouse_event, state);
			            	 if (mouse_event.y_delta*mouse_event.x_delta >0){ // positive slope
			            		 if(mouse_event.length > 0){ // if a positive length was given
			            			 if(!(mouse_packet[0] & BIT(4)) && !(mouse_packet[0] & BIT(5))){ // Positive values in the packet's x and y
			            				 mouse_event.type = RDOW;
			            				 mouse_event.slope = PSLOPE;
			            				 state = gesture_handler(&mouse_event,state);
			            			 }
			            			 else {
			            				 // Invalid movement, reset total displacement
			            				 mouse_event.type = RDOW;
			            			 	 mouse_event.x_delta = 0;
			            			 	 mouse_event.y_delta = 0;
			            			 	 state = gesture_handler(&mouse_event,state);
			            			 }
			            		 }
			            		 else if(mouse_event.length < 0){ // negative slope
			            			 if((mouse_packet[0] & BIT(4)) && (mouse_packet[0] & BIT(5))){ // Negative values in the packet's x and y
			            				 mouse_event.type = RDOW;
			            				 mouse_event.slope = PSLOPE;
			            				 state = gesture_handler(&mouse_event,state);
			            			 }
			            			 else {
			            				 // Invalid movement, reset total displacement
			            				 mouse_event.type = RDOW;
			            			 	 mouse_event.x_delta = 0;
			            			 	 mouse_event.y_delta = 0;
			            			 	 state = gesture_handler(&mouse_event,state);
			            			 }
			            		 }

			            	 }
			            	 else {
			            	 	mouse_event.type = RDOW;
			            	 	mouse_event.slope = NSLOPE;
			            	 	mouse_event.x_delta = 0;
			            	 	mouse_event.y_delta = 0;
			            	 	state = gesture_handler(&mouse_event,state);
			            	 }

			             }
			             else{
			             	mouse_event.type = RUP;
			             	state = gesture_handler(&mouse_event, state);
			             }

			           }

			        }
			        break;
			    default:
			    	break; /* no other notifications expected: do nothing */
			}
			    } else { /* received a standard message, not a notification */
			        /* no standard messages expected: do nothing */
			    }
			 }
		printf("\n The program achieved the acceptation state\n");
		if(disable_mouse() != 0){
			printf("The program failed to disable the mouse data reporting\n");
			return 1;
		}
		// Unsubscribe to the mouse interrupts
		if(mouse_unsubscribe_int(&mouse_id) != 0){
			printf("The program was unable to unsubscribe a mouse notification\n");
			return 1;
		}
		clean_out(); // Clear output buffer
		return 0;
}	
