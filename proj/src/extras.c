#include "extras.h"
#include <stdlib.h>
#include "timer.h"
#include "keyboard.h"
#include "mouse.h"
#include "video_gr.h"
#include "uart_macros.h"
#include "serial_port.h"

int keyboard_id = KEYBOARD_IRQ;
int mouse_id = MOUSE_IRQ;
int uart_id = COM1_IRQ;

MenuPointer * create_MenuPointer(unsigned int x, unsigned int y){

		MenuPointer * mp = (MenuPointer *) malloc(sizeof(MenuPointer));
		mp->x = x;
		mp->y = y;
		mp->op = 0;
		mp->bmp = loadBitmap("home/lcom/proj/res/menu_pointer.bmp");

	return mp;
}

void destroy_MenuPointer(MenuPointer * mp){
	deleteBitmap(mp->bmp);
	free(mp);
}

Aim * create_Aim(){

		Aim * aim = (Aim *) malloc(sizeof(Aim));
		aim->bmp = loadBitmap("home/lcom/proj/res/crosshair.bmp");
		aim->aim_x = getHorResolution()/2;
		aim->aim_y = getVerResolution()/2;
		aim->x = aim->aim_x - aim->bmp->bitmapInfoHeader.width/2;
		aim->y = aim->aim_y - aim->bmp->bitmapInfoHeader.height/2;
		aim->shot = 0;


	return aim;
}

void destroy_Aim(Aim * aim){
	deleteBitmap(aim->bmp);
	free(aim);
}

int game_subscribe_int(){
	if(serial_port_subscribe_int(&uart_id) != 0){
		printf("Erro:failed to enable a subscription to a serial port interrupt\n");
		return 1;
	}
	if(keyboard_subscribe_int(&keyboard_id) != 0){
		printf("Erro:failed to enable a subscription to a keyboard interrupt\n");
		return 1;
	}
	if(mouse_subscribe_int(&mouse_id) != 0){
		printf("Erro:failed to enable a subscription to a mouse interrupt\n");
			return 1;
	}
	if(timer_subscribe_int() != 0){
		printf("Erro:failed to enable a subscription to a timer interrupt\n");
				return 1;
	}
	if(enable_mouse() != 0){
		printf("The program failed to enable the mouse data reporting\n");
		return 1;
	}
	return 0;
}

int game_unsubscribe_int(){
	if(disable_mouse() != 0){
		printf("The program failed to disable the mouse data reporting\n");
		return 1;
	}
	if(keyboard_unsubscribe_int(&keyboard_id) != 0){
		printf("Erro:failed to disable a subscription to a keyboard interrupt\n");
		return 1;
	}
	if(mouse_unsubscribe_int(&mouse_id) != 0){
		printf("Erro:failed to disable a subscription to a mouse interrupt\n");
		return 1;
	}
	if(timer_unsubscribe_int() != 0){
		printf("Erro:failed to disable a subscription to a timer interrupt\n");
		return 1;
	}
	if(serial_port_unsubscribe_int(&uart_id) != 0){
		printf("Erro:failed to enable a subscription to a serial port interrupt\n");
		return 1;
	}
	return 0;
}

void aim_update(unsigned long * mouse_packet, Aim * aim){
	aim->shot = mouse_packet[0] & BIT(0);
	if(((mouse_packet[0] & BIT(6)) |(mouse_packet[0] & BIT(7))) == 0){
		if(mouse_packet[0] & BIT(4)){ // If the x value is negative
			aim->aim_x += complement(mouse_packet[1]);

		}
		else{
			aim->aim_x += mouse_packet[1];
		}

		if(mouse_packet[0] & BIT(5)){ // If the y value is negative
			aim->aim_y += -complement(mouse_packet[2]);
		}
		else{
			aim->aim_y += -mouse_packet[2];
		}

		if (aim->aim_x >= getHorResolution())
			aim->aim_x = getHorResolution();

		if (aim->aim_y >= getVerResolution())
			aim->aim_y = getVerResolution();

		aim->x = aim->aim_x - aim->bmp->bitmapInfoHeader.width/2;
		aim->y = aim->aim_y - aim->bmp->bitmapInfoHeader.height/2;

		if(aim->x < 0){
			aim->x = 0;
			aim->aim_x = aim->bmp->bitmapInfoHeader.width/2;
		}
		if(aim->y < 0){
			aim->y = 0;
			aim->aim_y = aim->bmp->bitmapInfoHeader.height/2;
		}
	}

}
