#include "serial_port.h"
#include "uart_macros.h"
#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/driver.h>
#include <minix/com.h>
#include <minix/sysutil.h>
#include "keyboard.h"
#include "mouse.h"
#include "i8042.h"
#include "i8254.h"
#include "bitmap.h"
#include "video_gr.h"


int serial_port_subscribe_int(int * uart_id){
	if (sys_irqsetpolicy(COM1_IRQ, IRQ_REENABLE|IRQ_EXCLUSIVE , uart_id) != 0) {
		printf("Error: Failed to subscribe an interruption to the serial port\n");
		return 1;
	}
	if (sys_irqenable(uart_id) != 0) {
		printf("Error: Failed to enable an interruption to the serial port\n\n");
		return 1;
	}
	if (sys_outb(IER, RD_EN|RLS_EN) != 0) {
		printf("Error: FadrawBitmap(sky,0,0,ALIGN_LEFT);iled to enable interruptions to RD and RLS \n");
		return 1;
	}
	return 0;
}

int serial_port_unsubscribe_int(int * uart_id){
	if (sys_irqdisable(uart_id) != 0) {
		printf("Error: Failed to disable an interruption to the serial port\n\n");
		return 1;
	}
	if (sys_irqrmpolicy(uart_id) != 0) {
		printf("Error: Failed to unsubscribe an interruption to the serial port\n");
		return 1;
	}
	return 0;
}


int read_IIR(unsigned long * iir_byte){
	if(sys_inb(IIR, iir_byte) != 0){
		printf("Error: Failed to read Interrupt Identification Register data\n");
		return 1;
	}
	return 0;
}

int read_LSR(unsigned long * lsr_byte){
	if(sys_inb(LSR,lsr_byte) != 0){
		printf("Error: Failed to read Line Status Register data\n");
		return 1;
	}
	return 0;
}

int read_RBR(unsigned long *_byte){
	unsigned long lsr_byte;

	unsigned int i;
	for(i = 0; i < 5;i++){
			if(read_LSR(&lsr_byte) != 0){
				printf("Error: unable to read LSR\n");
			}
			else if(lsr_byte & RECEIVER_DATA){
				sys_inb(RBR, _byte);
				printf("Receive: %c \n",(char) *_byte); //debug
                tickdelay(micros_to_ticks(SP_DELAY));
				return 0;
			}
	}
	return 1;
}

int write_THR(unsigned long _byte){
	unsigned long lsr_byte;

	unsigned int i;
	for(i = 0; i < 5;i++){
			if(read_LSR(&lsr_byte) != 0){
				printf("Error: unable to read LSR\n");
			}
			else if(lsr_byte & THR_EMP){
				sys_outb(THR, _byte);
				printf("Transmit: %c \n",(char)_byte);
				return 0;
			}
		}
	return 1;
}

int uart_handler(unsigned long *_byte){
	unsigned long iir_byte;
	unsigned long lsr_byte;
	if(read_IIR(&iir_byte) != 0){
		return 1;
	}
    if(iir_byte & RD){
        if(read_RBR(_byte) != 0){
            return 1;
        }
	}
	else if ((iir_byte & RLS) == RLS){
        if(read_LSR(&lsr_byte) != 0){
            return 1;
        }
	}
	return 0;
}

int clean_RBR(){
	unsigned long cleaner;
	unsigned long iir_byte;
	read_IIR(&iir_byte);
	if(iir_byte & RD){
		read_RBR(&cleaner);
	}
	return 0;
}


int duck_sync_prepare(){
	int ipc_status, r;
	message msg;
	int irq_uart = BIT(COM1_IRQ);
	int irq_keyboard = BIT(KEYBOARD_IRQ);
	int irq_timer = BIT(TIMER0_IRQ);
	int irq_mouse = BIT(MOUSE_IRQ);
	unsigned long scancode = 0;
    unsigned long received_char = 'd';
	Bitmap * back = loadBitmap("home/lcom/proj/res/waiting_hunter.bmp");
	drawBitmap(back,0,0,ALIGN_LEFT);
	pageFlip();
	clean_RBR();
	while (scancode != ESC_BREAK && received_char != 'h') { /* key pressed != ESC or the char received != r */
		/* Get a request message. */
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d\n", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification of kernel*/
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if(msg.NOTIFY_ARG & irq_timer){
					clean_RBR();
					write_THR('d');
				}
				if(msg.NOTIFY_ARG & irq_uart){
					uart_handler(&received_char);

				}
				if(msg.NOTIFY_ARG & irq_keyboard){
					keyboard_handler(&scancode);
				}
				if(msg.NOTIFY_ARG & irq_mouse){
					clean_out();
				}
				break;
			default:
				printf("Default notification\n");
				break; /* no other notifications expected: do nothing */
			}
		}
	}
	if(scancode == ESC_BREAK){
		return 1;
	}
	return 0;
}

int hunter_sync_prepare(){
	int ipc_status, r;
	message msg;
	int irq_uart = BIT(COM1_IRQ);
	int irq_keyboard = BIT(KEYBOARD_IRQ);
	int irq_timer = BIT(TIMER0_IRQ);
	int irq_mouse = BIT(MOUSE_IRQ);
	unsigned long scancode = 0;
    unsigned long received_char = 'n';
	Bitmap * back = loadBitmap("home/lcom/proj/res/waiting_duck.bmp");
	drawBitmap(back,0,0,ALIGN_LEFT);
	pageFlip();
	clean_RBR();
	while (scancode != ESC_BREAK && received_char != 'd') { /* key pressed != ESC or the char received != r */
		/* Get a request message. */
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d\n", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification of kernel*/
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if(msg.NOTIFY_ARG & irq_timer){
					clean_RBR();
					write_THR('h');

				}
				if(msg.NOTIFY_ARG & irq_uart){
					uart_handler(&received_char);
					printf("%c",received_char);
				}
				if(msg.NOTIFY_ARG & irq_keyboard){
					keyboard_handler(&scancode);
				}
				if(msg.NOTIFY_ARG & irq_mouse){
					clean_out();
				}
				break;
			default:
				printf("Default notification\n");
				break; /* no other notifications expected: do nothing */
			}
		}
	}
	if(scancode == ESC_BREAK){
		return 1;
	}
	return 0;
}
