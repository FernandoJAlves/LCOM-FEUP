#include "graphics.h"
#include "video_gr.h"
#include "test5.h"
#include "keyboard.h"
#include "timer.h"
#include "video_test.h"
#include "sprite.h"
#include "i8254.h"

int video_test_init(unsigned short mode, unsigned short delay) {
	if(vg_init(mode) != 0){
		printf("Error:failed to set graphics mode\n");
		return 1;
	}
	tickdelay(micros_to_ticks(delay*1000000));
	vg_exit();
	printf("Graphics mode deactivated. Text mode set\n");
	return 0;
	
}


int video_test_square(unsigned short x, unsigned short y, unsigned short size, unsigned long color) {

	int keyboard_id = 1;
	int ipc_status;
	message msg;
	unsigned long irq_set = BIT(keyboard_id);
	unsigned long r;
	unsigned long scancode = 0;


	if(keyboard_subscribe_int(&keyboard_id) != 0){
		printf("Erro:failed to enable a subscription to a keyboard interrupt\n");
		return 1;
	}
	if(vg_init(GRAPH_MODE) != 0){
			printf("Error:failed to set graphics mode\n");
			return 1;
	}

	vg_drawSquare(x,y,size,color);
	video_dump_fb();

	while (scancode != ESC_BREAK) {
		/* Get a request message. */
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d\n", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */
					//Handle the interrupt in C
					keyboard_handler(&scancode);
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

	if (keyboard_unsubscribe_int(&keyboard_id) != 0) {
		printf("Erro:failed to disable a subscription to a keyboard interrupt\n");
		return 1;
	}

		vg_exit();
		printf("Graphics mode deactivated. Text mode set\n");
	return 0;
	
}

int video_test_line(unsigned short xi, unsigned short yi, 
		           unsigned short xf, unsigned short yf, unsigned long color) {
	int keyboard_id = 1;
	int ipc_status;
	message msg;
	unsigned long irq_set = BIT(keyboard_id);
	unsigned long r;
	unsigned long scancode = 0;


	if(keyboard_subscribe_int(&keyboard_id) != 0){
		printf("Erro:failed to enable a subscription to a keyboard interrupt\n");
		return 1;
	}
	if(vg_init(GRAPH_MODE) != 0){
			printf("Error:failed to set graphics mode\n");
			return 1;
	}

	vg_drawLine(xi,yi,xf,yf,color);
	video_dump_fb();

	while (scancode != ESC_BREAK) {
		/* Get a request message. */
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d\n", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */
					//Handle the interrupt in C
					keyboard_handler(&scancode);
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

	if (keyboard_unsubscribe_int(&keyboard_id) != 0) {
		printf("Erro:failed to disable a subscription to a keyboard interrupt\n");
		return 1;
	}

		vg_exit();
		printf("Graphics mode deactivated. Text mode set\n");
	return 0;

}
	
int video_test_xpm(char *xpm[], unsigned short xi, unsigned short yi) {

	int keyboard_id = 1;
	int ipc_status;
	message msg;
	unsigned long irq_set = BIT(keyboard_id);
	unsigned long r;
	unsigned long scancode = 0;


	if(keyboard_subscribe_int(&keyboard_id) != 0){
		printf("Erro:failed to enable a subscription to a keyboard interrupt\n");
		return 1;
	}
	if(vg_init(GRAPH_MODE) != 0){
			printf("Error:failed to set graphics mode\n");
			return 1;
	}
	vg_drawMap(xpm,xi, yi);
	video_dump_fb();

	while (scancode != ESC_BREAK) {
		/* Get a request message. */
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d\n", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */
					//Handle the interrupt in C
					keyboard_handler(&scancode);
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

	if (keyboard_unsubscribe_int(&keyboard_id) != 0) {
		printf("Erro:failed to disable a subscription to a keyboard interrupt\n");
		return 1;
	}

		vg_exit();
		printf("Graphics mode deactivated. Text mode set\n");
	return 0;


	
}	

int video_test_move(char *xpm[], unsigned short xi, unsigned short yi, unsigned short xf, unsigned short yf, short s, unsigned short f) {

	if(f > 60){
		printf("Invalid argument: Framerate should be inferior to 60 fps\n");
		return 0;
	}
	int keyboard_id = 1;
	int timer_id = 0;
	int ipc_status;
	message msg;
	unsigned long irq_keyboard = BIT(keyboard_id);
	unsigned long irq_timer = BIT(timer_id);
	unsigned long r;
	unsigned long scancode = 0;
	short xspeed = 0;
	short yspeed = 0;
	unsigned int delta;

	if(keyboard_subscribe_int(&keyboard_id) != 0){
		printf("Erro:failed to enable a subscription to a keyboard interrupt\n");
		return 1;
	}
	if(timer_subscribe_int() != 0){
			printf("Erro:failed to enable a subscription to a timer interrupt\n");
			return 1;
		}
	if(vg_init(GRAPH_MODE) != 0){
			printf("Error:failed to set graphics mode\n");
			return 1;
	}
	if(abs(yf-yi) > 0 && abs(xf-xi) == 0){
		yspeed = s;
		delta = abs(yf-yi);
	}
	else if(abs(xf-xi) > 0 && abs(yf-yi) == 0){
		xspeed = s;
		delta = abs(xf-xi);
	}
	else{
		keyboard_unsubscribe_int(&keyboard_id);
		timer_unsubscribe_int();
		vg_exit();
		printf("Invalid movement. Only horizontal and vertical movements allowed\n");
		return 0;
	}
	Sprite * sp = create_sprite(xpm, xi , yi , xspeed , yspeed);
	while (scancode != ESC_BREAK) {
		if((timer_counter % (PC_FREQ/f)) == 0 && s >= 0){
			vg_animateSprite(sp,xf,yf, f,delta);
		}
		else if((timer_counter *(PC_FREQ/f)) % abs(s) == 0 && s < 0){
			vg_animateSprite(sp,xf,yf, f,delta);
		}
		video_dump_fb();
		/* Get a request message. */
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d\n", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_keyboard) { /* subscribed interrupt */
					keyboard_handler(&scancode);
					tickdelay(micros_to_ticks(DELAY_US));
				}
				if (msg.NOTIFY_ARG & irq_timer) { /* subscribed interrupt */
					timer_int_handler();
				}
				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		} else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}
	}

	if (keyboard_unsubscribe_int(&keyboard_id) != 0) {
		printf("Erro:failed to disable a subscription to a keyboard interrupt\n");
		return 1;
	}
	if (timer_unsubscribe_int() != 0) {
		printf("Erro:failed to disable a subscription to a timer interrupt\n");
		return 1;
	}
	destroy_sprite(sp);
		vg_exit();
		printf("Graphics mode deactivated. Text mode set\n");
	return 0;



}	

int video_test_controller() {
	vg_displayController();
	video_dump_fb();
	return 0;
}	
	
