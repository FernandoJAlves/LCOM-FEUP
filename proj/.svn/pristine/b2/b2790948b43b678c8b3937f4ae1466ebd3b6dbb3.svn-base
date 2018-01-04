#include "menu.h"
#include "keyboard.h"
#include "graphics.h"
#include "video_gr.h"
#include "bitmap.h"
#include "timer.h"
#include "i8254.h"
#include "i8042.h"
#include "game.h"
#include "mouse.h"
#include "serial_port.h"
#include "points.h"


//RTC Functions

unsigned int get_min_rtc();
unsigned int get_hour_rtc();
unsigned int get_day_rtc();
unsigned int get_month_rtc();
unsigned int get_year_rtc();

int main_menu(){

	loadDigits_small();
	int ipc_status;
	message msg;
	unsigned long irq_keyboard = BIT(KEYBOARD_IRQ);
	unsigned long irq_mouse = BIT(MOUSE_IRQ);
	unsigned long irq_timer = BIT(TIMER0_IRQ);
	unsigned long r;
	unsigned long scancode = 1;
	game_state state = MENU;
	if(game_subscribe_int() != 0){
		printf("Error: failed to subscribe a module\n");
		return 1;
	}
	if(vg_init(GRAPH_117) != 0){
		printf("Error:failed to set graphics mode\n");
		return 1;
	}
	read_score();
	MenuPointer * mp = create_MenuPointer(0,408);
	Bitmap * back = loadBitmap("home/lcom/proj/res/menu_background.bmp");
	drawBitmap(back, 0, 0, ALIGN_LEFT);
	drawBitmap(mp->bmp, mp->x, mp->y, ALIGN_LEFT);
	draw_date_small(get_day_rtc(),get_month_rtc(),get_year_rtc(),get_hour_rtc(),get_min_rtc(),650,15);
	pageFlip();
	tickdelay(micros_to_ticks(MENU_DELAY));
	clean_out();
	while (scancode != ESC_BREAK && state != END_GAME) {
		/* Get a request message. */
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d\n", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_timer){
					drawBitmap(back, 0, 0, ALIGN_LEFT);
					drawBitmap(mp->bmp, mp->x, mp->y, ALIGN_LEFT);
					draw_date_small(get_day_rtc(),get_month_rtc(),get_year_rtc(),get_hour_rtc(),get_min_rtc(),650,15);
					pageFlip();
				}
				if (msg.NOTIFY_ARG & irq_keyboard) { /* subscribed interrupt */
					keyboard_handler(&scancode);
					tickdelay(micros_to_ticks(DELAY_US));
					if((scancode ==  UP_MAKE && mp->op > 0) || (scancode == DOWN_MAKE && mp->op < 3)){
						change_pointer(scancode,mp);
						drawBitmap(back, 0, 0, ALIGN_LEFT);
						drawBitmap(mp->bmp, mp->x, mp->y, ALIGN_LEFT);
						draw_date_small(get_day_rtc(),get_month_rtc(),get_year_rtc(),get_hour_rtc(),get_min_rtc(),650,15);
						pageFlip();
						tickdelay(micros_to_ticks(MENU_DELAY));
					}
					if(scancode == ENTER_BREAK){
						menu_option(mp,&state);
						drawBitmap(back, 0, 0, ALIGN_LEFT);
						drawBitmap(mp->bmp, mp->x, mp->y, ALIGN_LEFT);
						draw_date_small(get_day_rtc(),get_month_rtc(),get_year_rtc(),get_hour_rtc(),get_min_rtc(),650,15);
						pageFlip();
					}
				}
				if(msg.NOTIFY_ARG & irq_mouse){
					clean_out();
				}
				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		} else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}
	}

	if(game_unsubscribe_int() != 0){
			printf("Error: failed to unsubscribe a module\n");
			return 1;
		}
	destroy_MenuPointer(mp);
	deleteBitmap(back);
	vg_exit();
	clean_out();
	printf("Graphics mode deactivated. Text mode set\n");
	write_score();
	return 0;



}

int score_menu(){

	loadFont();
	loadDigits_large();
	int ipc_status;
	message msg;
	unsigned long irq_keyboard = BIT(KEYBOARD_IRQ);
	unsigned long irq_mouse = BIT(MOUSE_IRQ);
	unsigned long irq_timer = BIT(TIMER0_IRQ);
	unsigned long r;
	unsigned long scancode = 1;

	Bitmap * back = loadBitmap("home/lcom/proj/res/highscore_screen.bmp");
	Bitmap * back2 = loadBitmap("home/lcom/proj/res/no_highscore_screen.bmp");
	clean_out();
	while (scancode != ESC_BREAK) {
		/* Get a request message. */
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d\n", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_timer){
					if(highscore != 0){
						drawBitmap(back, 0, 0, ALIGN_LEFT);
						draw_score_6_digits_large(highscore, 580, 140);
						draw_date_large(day,month,year,hour,minute,335,382);
						draw_string(name, 350, 268);
					}
					else{
						drawBitmap(back2, 0, 0, ALIGN_LEFT);
					}
					pageFlip();
				}
				if (msg.NOTIFY_ARG & irq_keyboard) { /* subscribed interrupt */
					//Handle the interrupt in C
					keyboard_handler(&scancode);
					tickdelay(micros_to_ticks(DELAY_US));
					if(scancode ==  R_MAKE){
						reset_score();
						tickdelay(micros_to_ticks(MENU_DELAY));
					}
				}
				if(msg.NOTIFY_ARG & irq_mouse){
					clean_out();
				}
				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		} else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}
	}
	deleteBitmap(back);
	deleteBitmap(back2);
	clean_out();
	return 0;

}

int game_b_menu(game_state * state){


	int ipc_status;
	message msg;
	unsigned long irq_keyboard = BIT(KEYBOARD_IRQ);
	unsigned long irq_mouse = BIT(MOUSE_IRQ);
	unsigned long r;
	unsigned long scancode = 1;
	MenuPointer * mp = create_MenuPointer(150,283);
	Bitmap * back = loadBitmap("home/lcom/proj/res/menu_selection.bmp");
	drawBitmap(back, 0, 0, ALIGN_LEFT);
	drawBitmap(mp->bmp, mp->x, mp->y, ALIGN_LEFT);
	pageFlip();
	tickdelay(micros_to_ticks(MENU_DELAY));
	clean_out();
	while (scancode != ESC_BREAK && *state != MENU) {
		/* Get a request message. */
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d\n", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_keyboard) { /* subscribed interrupt */
					//Handle the interrupt in C
					keyboard_handler(&scancode);
					tickdelay(micros_to_ticks(DELAY_US));
					if((scancode ==  UP_MAKE && mp->op > 0) || (scancode == DOWN_MAKE && mp->op < 2)){
						change_pointer_b(scancode,mp);
						drawBitmap(back, 0, 0, ALIGN_LEFT);
						drawBitmap(mp->bmp, mp->x, mp->y, ALIGN_LEFT);
						pageFlip();
						tickdelay(micros_to_ticks(MENU_DELAY));
					}
					if(scancode == ENTER_BREAK){
						menu_option_b(mp,state);
						drawBitmap(back, 0, 0, ALIGN_LEFT);
						drawBitmap(mp->bmp, mp->x, mp->y, ALIGN_LEFT);
						pageFlip();
					}
				}
				if(msg.NOTIFY_ARG & irq_mouse){
					clean_out();
				}
				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		} else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}
	}
	destroy_MenuPointer(mp);
	deleteBitmap(back);
	clean_out();
	return 0;



}


void change_pointer(unsigned long scancode, MenuPointer * mp){
	int delta = 63;
	switch(scancode){
	case UP_MAKE:
		mp->y -= delta;
		mp->op--;
		break;
	case DOWN_MAKE:
		mp->y += delta;
		mp->op++;
		break;
	}
}

void change_pointer_b(unsigned long scancode, MenuPointer * mp){
	int delta = 98;
	switch(scancode){
	case UP_MAKE:
		mp->y -= delta;
		mp->op--;
		break;
	case DOWN_MAKE:
		mp->y += delta;
		mp->op++;
		break;
	}
}

void menu_option(MenuPointer * mp, game_state * state){
	switch (mp->op){
	case 0:
		*state = GAME_A;
		game_a();
		*state = MENU;
		break;
	case 1:
		*state = GAME_B_MENU;
		game_b_menu(state);
		*state = MENU;
		break;
	case 2:
		*state = SCORE_MENU;
		score_menu();
		*state = MENU;
		break;
	case 3:
		*state = END_GAME;
		break;
	}

}

void menu_option_b(MenuPointer * mp, game_state * state){
	switch (mp->op){
	case 0:
		*state = GAME_B_DUCK;
		game_b_duck();
		*state = MENU;
		break;
	case 1:
		*state = GAME_B_HUNTER;
		game_b_hunter();
		*state = MENU;
		break;
	case 2:
		*state = MENU;
		break;
	}

}
