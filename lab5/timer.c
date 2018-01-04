#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/driver.h>
#include <minix/com.h>
#include <minix/sysutil.h>
#include "i8254.h"


//Global variables
unsigned int timer_counter = 0;
int timer_id = 0;

int timer_get_conf(unsigned char timer, unsigned char *st);

int timer_set_frequency(unsigned char timer, unsigned long freq) {
	if(freq < 0)
		return 1;
	unsigned long _byte;
	unsigned char MSB, LSB;
	sys_inb(TIMER_CTRL,&_byte);
	unsigned int value = 1193181/ freq;
	LSB = (unsigned char) value;
	MSB = (unsigned char) (value>>(8));
	switch(timer){
		case 0:
			_byte = (_byte & 0x0f) | TIMER_SEL0 | TIMER_LSB_MSB;
			sys_outb(TIMER_CTRL, _byte);
			sys_outb(TIMER_0, LSB);
			sys_outb(TIMER_0, MSB);
			break;
		case 1:
			_byte = (_byte & 0x0f) | TIMER_SEL1 | TIMER_LSB_MSB;
			sys_outb(TIMER_CTRL, _byte);
			sys_outb(TIMER_1, LSB);
			sys_outb(TIMER_1, MSB);
			break;
		case 2:
			_byte = (_byte & 0x0f) | TIMER_SEL2 | TIMER_LSB_MSB;
			sys_outb(TIMER_CTRL, _byte);
			sys_outb(TIMER_2, LSB);
			sys_outb(TIMER_2, MSB);
			break;
		}
	return 0;
}

int timer_subscribe_int(void) {

	if(sys_irqsetpolicy(TIMER0_IRQ,IRQ_REENABLE,&timer_id) != 0){
		printf("Error: unable to subscribe a notification\n");
		return 1;
	}
	if(sys_irqenable(&timer_id) != 0){
		printf("Error: failed to enable an interrupt\n");
		return 1;
	}
	return 0;
}

int timer_unsubscribe_int() {
	if(sys_irqdisable(&timer_id) != 0){
	    	printf("Error:The program can't disable the interrupt of the associated hook id\n");
	    	return 1;
	}
    if(sys_irqrmpolicy(&timer_id) != 0)
    {
    	printf("Error:The program can't unsubscribe the interrupt of the associated hook id\n");
    	return 1;
    }
	return 0;
}

void timer_int_handler() {
	timer_counter++;
}

int timer_get_conf(unsigned char timer, unsigned char *st) {
	unsigned long _byte;
	unsigned long control_byte = 0;
	switch(timer){
		case 0:
			control_byte = (TIMER_RB_CMD |TIMER_RB_COUNT_ |TIMER_RB_SEL(0));
			if(sys_outb(TIMER_CTRL,control_byte) != 0)
				return 1;
			if((sys_inb(TIMER_0,&_byte)) != 0)
				return 1;
			break;
		case 1:
			control_byte = (TIMER_RB_CMD |TIMER_RB_COUNT_ |TIMER_RB_SEL(1));
			if(sys_outb(TIMER_CTRL,control_byte) != 0)
				return 1;
			if((sys_inb(TIMER_1,&_byte)) != 0)
				return 1;
			break;
		case 2:
		    control_byte = (TIMER_RB_CMD |TIMER_RB_COUNT_ |TIMER_RB_SEL(2));
		    if(sys_outb(TIMER_CTRL,control_byte) != 0)
			    return 1;
			if((sys_inb(TIMER_2,&_byte)) != 0)
				return 1;
			break;
		default:
			printf("Timer %x not found\n",timer);
			return 1;
		}
	*st = (unsigned char) _byte;
	return 0;
}

int timer_display_conf(unsigned char conf) {
        printf("Bit                 Function               \n");

    if ( conf & TIMER_LSB)
    {
    	if ( conf & TIMER_MSB)
    		printf("5,4                 Type of Access: LSB followed by MSB    \n");

    	else
    		printf("5,4                 Type of Access: LSB    \n");
    }
    else
    	 printf("5,4                 Type of Access: MSB    \n");



    if(conf & TIMER_TRIG_STR){

    	if(conf & TIMER_RATE_GEN){

    		if(conf & TIMER_RET_ONE){
    			printf("3,2,1               Operating Mode: 3    \n");
    		}
    		else
    			printf("3,2,1               Operating Mode: 2    \n");

    	}

    	else{

    	if(conf & TIMER_RET_ONE)
    		printf("3,2,1               Operating Mode: 5    \n");
    	else
    		printf("3,2,1               Operating Mode: 4    \n");
    	}
    }

    else{

    	if(conf & TIMER_RATE_GEN){

    	   if(conf & TIMER_RET_ONE){
    	    printf("3,2,1               Operating Mode: 3    \n");
    	   }
    	   else
    	    printf("3,2,1               Operating Mode: 2    \n");

    	  }

    	 else{

    	  if(conf & TIMER_RET_ONE)
    	 	printf("3,2,1               Operating Mode: 1    \n");
    	  else
    	    printf("3,2,1               Operating Mode: 0    \n");
    	  }
    }



	if ( conf & TIMER_BCD)
		printf("0                   Counting Mode: BCD   \n");
	else
		printf("0                   Counting Mode: Binary   \n");
	return 0;
}

int timer_test_time_base(unsigned long freq) {
	timer_set_frequency(0, freq);
	return 0;
}

int timer_test_config(unsigned char timer) {
	unsigned char _byte;
	if(timer_get_conf(timer,&_byte) != 0){
		printf("Error: failed to get the specified timer configuration");
		return 1;
	}
	if(timer_display_conf(_byte) != 0){
		printf("Error: failed to display information");
		return 1;
	}
	return 0;
}
