#include "graphics.h"
#include "video_gr.h"
#include "game.h"
#include "keyboard.h"
#include "timer.h"
#include "i8254.h"
#include "bitmap.h"
#include "extras.h"
#include "mouse.h"
#include "duck.h"
#include "serial_port.h"
#include "uart_macros.h"
#include "points.h"

int game_a() {

	loadDigits_small();
	int ipc_status;
	message msg;
	unsigned long irq_keyboard = BIT(KEYBOARD_IRQ);
	unsigned long irq_timer = BIT(TIMER0_IRQ);
	unsigned long irq_mouse = BIT(MOUSE_IRQ);
	unsigned long r;
	unsigned long scancode = 0;
	unsigned long mouse_packet[3];
	unsigned int i;
	unsigned int round_index = 0;
	unsigned int number_ducks = 0;
	play_state state = PLAYING;
	unsigned int bullet_counter = 0;
	unsigned int points_counter = 0;
	int number_of_hits = 0;
	int mouse_pressed = 0;
	int ducks_alive = 0;

	Bitmap * sky = loadBitmap("home/lcom/proj/res/Fundo_Azul.bmp");
	Bitmap * grass = loadBitmap("home/lcom/proj/res/Arbusto.bmp");
	Bitmap * dog = loadBitmap("home/lcom/proj/res/dog1.bmp");
	Duck* ducks_list[10];

	for(i=0;i<10;i++){
		ducks_list[i] = create_duck(getHorResolution()/2);
	}

	Aim * aim = create_Aim();

	while (scancode != ESC_BREAK && state != GAME_OVER && state != GAME_WON) {
		/* Get a request message. */
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d\n", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_timer) { /* subscribed interrupt */

					if(all_ducks_dead(ducks_list) == 1){
						points_counter += (bullet_counter * 1000); //funciona
						place_ducks_start(ducks_list);
						round_index++;
						number_ducks = next_round_ducks(round_index);
						ducks_alive = number_ducks;
						bullet_counter = next_round_bullets(round_index);
						if(number_ducks >= 9){
							state = GAME_WON;
						}
					}

					drawBitmap(sky,0,0,ALIGN_LEFT);
					for(i=0;i<number_ducks;i++){
						move_duck_auto(ducks_list[i]);
						//shot_duck2(ducks_list[i],aim, &number_of_hits);
						animate_duck(scancode, ducks_list[i]);
					}


					// se removermos o for, ATENCAO!!!! Garantir que chega ao final do array, sem mudança de aim->shot
					if(aim->shot && mouse_pressed == 0){
						for(i=0;i<number_ducks;i++){
							shot_duck2(ducks_list[i],aim, &number_of_hits);
						}
						mouse_pressed = 1;
						bullet_counter--;
						points_counter += (number_of_hits * 500);
						ducks_alive = ducks_alive - number_of_hits;
						number_of_hits = 0; //restart the hit counter
					}
					if(!(aim->shot)){
						mouse_pressed = 0;
					}

					//review this! (fixed)
					if(bullet_counter == 0){
						state = GAME_OVER;
						if(any_ducks_falling(ducks_list) == 1){
							state = PLAYING;
						}

					}

					drawSprite(grass,0,0,ALIGN_LEFT);
					//drawSprite(dog,200,600,ALIGN_LEFT);
					drawSprite(aim->bmp,aim->x,aim->y,ALIGN_LEFT);
					draw_score_6_digits_small(points_counter, 755, 697);
					draw_ducks_bullets(ducks_alive, bullet_counter, 73, 680);
					pageFlip();
				}
				if (msg.NOTIFY_ARG & irq_keyboard) { /* subscribed interrupt */
					//Handle the interrupt in C
					keyboard_handler(&scancode);
					tickdelay(micros_to_ticks(DELAY_US));
				}
				if(msg.NOTIFY_ARG & irq_mouse){
                	if(mouse_handler(mouse_packet) == 0){
                		aim_update(mouse_packet,aim);
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

	clean_out();
	gameover_screen_a(points_counter,state);
	clean_out();
	destroy_Aim(aim);
	for(i=0;i<10;i++){
		destroy_duck(ducks_list[i]);
	}
	deleteBitmap(sky);
	deleteBitmap(grass);
	deleteBitmap(dog);
	return 0;



}

int game_b_hunter() {
	if(hunter_sync_prepare() != 0){
		return 0;
	}
	int ipc_status;
	message msg;
	unsigned long irq_keyboard = BIT(KEYBOARD_IRQ);
	unsigned long irq_uart = BIT(COM1_IRQ);
	unsigned long irq_timer = BIT(TIMER0_IRQ);
	unsigned long irq_mouse = BIT(MOUSE_IRQ);
	unsigned long r;
	unsigned long scancode = 0;
	unsigned long duck_scancode = 0;
	unsigned long mouse_packet[3];
	int number_of_hits = 0;

	unsigned int round_index = 0;
	play_state state = PLAYING;
	unsigned int bullet_counter = 0;
	int mouse_pressed = 0;
	timer_counter = 0;

	Bitmap * sky = loadBitmap("home/lcom/proj/res/Fundo_Azul.bmp");
	Bitmap * grass = loadBitmap("home/lcom/proj/res/Arbusto.bmp");
	Bitmap * dog = loadBitmap("home/lcom/proj/res/dog1.bmp");
	Duck * duck = create_duck(getHorResolution()/2);
	Aim * aim = create_Aim();
	clean_RBR();
	while (scancode != ESC_BREAK && state != GAME_OVER && state != GAME_WON) {
		/* Get a request message. */
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d\n", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_timer) { /* subscribed interrupt */



					drawBitmap(sky,0,0,ALIGN_LEFT);

					if((duck->direction == FALL || ((duck->direction == START) && (timer_counter == 0))) && (duck->pos_y > 560)){
						place_duck_start_mp(duck);
						round_index++;
						bullet_counter = next_round_bullets_mp(round_index);
						if(round_index > 10){
							state = GAME_WON;
						}
						timer_int_handler();
					}

					move_duck(duck_scancode, duck);
					animate_duck(scancode, duck);

					if(aim->shot && mouse_pressed == 0){
						shot_duck2_transmit(duck,aim,&number_of_hits);
						mouse_pressed = 1;
						bullet_counter--;
						number_of_hits = 0; //restart the hit counter
					}
					if(!(aim->shot)){
						mouse_pressed = 0;
					}

					if(bullet_counter == 0){
						state = GAME_OVER;
						if((duck->direction == SHOT) || (duck->direction == FALL)){
							state = PLAYING;
						}
					}

					drawSprite(grass,0,0,ALIGN_LEFT);
					//drawSprite(dog,200,600,ALIGN_LEFT);
					drawSprite(aim->bmp,aim->x,aim->y,ALIGN_LEFT);
					draw_score_6_digits_small(0, 755, 697);
					draw_ducks_bullets(!(((duck->direction == SHOT) || (duck->direction == FALL))), bullet_counter, 73, 680);
					pageFlip();


				}
				if(msg.NOTIFY_ARG & irq_mouse){
                	if(mouse_handler(mouse_packet) == 0){
                		aim_update(mouse_packet,aim);
                		clean_out();
                	}

				}
				if (msg.NOTIFY_ARG & irq_keyboard ) { /* subscribed interrupt */
					keyboard_handler(&scancode);
					tickdelay(micros_to_ticks(DELAY_US));

				}
				if (msg.NOTIFY_ARG & irq_uart) { /* subscribed interrupt */
					printf("boooom\n");
					uart_handler(&duck_scancode);
					if(duck_scancode == 'w'){
						state = GAME_WON;
					}
					//clean_RBR();
					//tickdelay(micros_to_ticks(DELAY_US));
				}

				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		} else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}
	}


	//ATENCAO, FALTA ME FAZER MENUS SEM SCORE, JÁ QUE AFINAL NÃO HAVERÁ PONTOS NO MULTIPLAYER
	clean_out();
	if(scancode == ESC_BREAK){
		state = GAME_OVER;
	}
	if(state == GAME_OVER){
		write_THR('w'); //se o hunter perdeu, então o pato ganhou, logo é enviado w para o pato
	}
	if(state == GAME_WON){
		write_THR('l');
	}
	gameover_screen_b(state);


	destroy_Aim(aim);
	destroy_duck(duck);
	deleteBitmap(sky);
	deleteBitmap(grass);
	deleteBitmap(dog);
	return 0;



}

int game_b_duck() {
	if(duck_sync_prepare() != 0){
		return 0;
	}
	disable_mouse();
	int ipc_status;
	message msg;
	unsigned long irq_keyboard = BIT(KEYBOARD_IRQ);
	unsigned long irq_uart = BIT(COM1_IRQ);
	unsigned long irq_timer = BIT(TIMER0_IRQ);
	unsigned long r;
	unsigned long scancode = 0;
	unsigned long received_char;
	play_state state = PLAYING;


	Bitmap * sky = loadBitmap("home/lcom/proj/res/Fundo_Azul.bmp");
	Bitmap * grass = loadBitmap("home/lcom/proj/res/Arbusto2.bmp");
	Bitmap * dog = loadBitmap("home/lcom/proj/res/dog1.bmp");
	Duck * duck = create_duck(getHorResolution()/2);
	clean_RBR();
	while (scancode != ESC_BREAK && received_char != 'w' && received_char != 'l') {
		/* Get a request message. */
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d\n", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_timer) { /* subscribed interrupt */
					drawBitmap(sky,0,0,ALIGN_LEFT);
					if((duck->direction == FALL || (duck->direction == START)) && (duck->pos_y > 560)){
						place_duck_start_mp(duck);
					}
					move_duck(scancode, duck);
					shot_duck2_receive(duck,&received_char);
					animate_duck(scancode, duck);
					drawSprite(grass,0,0,ALIGN_LEFT);
					//drawSprite(dog,200,600,ALIGN_LEFT);
					pageFlip();
					//clean_RBR();

				}
				if (msg.NOTIFY_ARG & irq_keyboard ) { /* subscribed interrupt */
					keyboard_handler(&scancode);
					write_THR(scancode);
					//tickdelay(micros_to_ticks(DELAY_US));
				}
				if (msg.NOTIFY_ARG & irq_uart) { /* subscribed interrupt */
					printf("boooom\n");
					uart_handler(&received_char);
					//clean_RBR();
					//tickdelay(micros_to_ticks(DELAY_US));
				}

				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		} else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}
	}

	if(scancode == ESC_BREAK){
		write_THR('w');
		state = GAME_OVER;
	}
	if(received_char == 'w'){
		state = GAME_WON;
	}
	if(received_char == 'l'){
		state = GAME_OVER;
	}
	gameover_screen_b(state);

	destroy_duck(duck);
	deleteBitmap(sky);
	deleteBitmap(grass);
	deleteBitmap(dog);
	enable_mouse();
	return 0;



}


int gameover_screen_a(int score, play_state state){

	loadDigits_large();
	loadFont();
	int ipc_status;
	message msg;
	unsigned long irq_keyboard = BIT(KEYBOARD_IRQ);
	unsigned long irq_timer = BIT(TIMER0_IRQ);
	unsigned long irq_mouse = BIT(MOUSE_IRQ);
	unsigned long r;
	unsigned long scancode = 0;
	Bitmap * game_screen;
	char nome[9] = {0,0,0,0,0,0,0,0,0};
	unsigned int i = 0;

	if(state == GAME_WON){
		game_screen = loadBitmap("home/lcom/proj/res/game_won_screen.bmp");
	}
	else{
		game_screen = loadBitmap("home/lcom/proj/res/game_over_screen.bmp");;
	}

	while (scancode != ENTER_BREAK) {
		/* Get a request message. */
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d\n", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_timer) { /* subscribed interrupt */
					drawBitmap(game_screen,0,0,ALIGN_LEFT);
					draw_score_6_digits_large(score, 500, 277);
					draw_string(nome, 250, 550);
					pageFlip();
				}
				if (msg.NOTIFY_ARG & irq_keyboard) { /* subscribed interrupt */
					//Handle the interrupt in C
					keyboard_handler(&scancode);
					if(i < 8 && scancode != BACKSPACE_MAKE && (scancode & MSB) == 0){
						write_char(&nome[i],scancode);
						i++;
					}
					else if(scancode == BACKSPACE_MAKE && i > 0){
						i--;
						write_char(&nome[i],scancode);
					}
					tickdelay(micros_to_ticks(DELAY_US));
					printf("%s %d\n",nome,i);
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
	clean_out();
	update_score(score,nome);
	deleteBitmap(game_screen);
	return 0;

}

int gameover_screen_b(play_state state){

	loadDigits_large();
	int ipc_status;
	message msg;
	unsigned long irq_keyboard = BIT(KEYBOARD_IRQ);
	unsigned long irq_timer = BIT(TIMER0_IRQ);
	unsigned long irq_mouse = BIT(MOUSE_IRQ);
	unsigned long r;
	unsigned long scancode = 0;
	Bitmap * game_screen;

	if(state == GAME_WON){
		game_screen = loadBitmap("home/lcom/proj/res/game_won_screen_b.bmp");
	}
	else{
		game_screen = loadBitmap("home/lcom/proj/res/game_over_screen_b.bmp");;
	}

	while (scancode != ENTER_BREAK) {
		/* Get a request message. */
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d\n", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_timer) { /* subscribed interrupt */
					drawBitmap(game_screen,0,0,ALIGN_LEFT);
					pageFlip();
				}
				if (msg.NOTIFY_ARG & irq_keyboard) { /* subscribed interrupt */
					//Handle the interrupt in C
					keyboard_handler(&scancode);
					tickdelay(micros_to_ticks(DELAY_US));
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
	clean_out();
	deleteBitmap(game_screen);
	return 0;

}
