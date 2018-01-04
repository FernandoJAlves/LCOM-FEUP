#include "duck.h"
#include "video_gr.h"
#include <stdlib.h>
#include "i8042.h"
#include "serial_port.h"

Duck* create_duck(int x){

	Duck * d1 = (Duck *) malloc(sizeof(Duck));
	d1->pos_x = x;
	d1->pos_y = getVerResolution() - 180;
	d1->bmp[0] = loadBitmap("home/lcom/proj/res/duck_h1.bmp");
	d1->bmp[1] = loadBitmap("home/lcom/proj/res/duck_h2.bmp");
	d1->bmp[2] = loadBitmap("home/lcom/proj/res/duck_h3.bmp");
	d1->bmp[3] = loadBitmap("home/lcom/proj/res/duck1.bmp");
	d1->bmp[4] = loadBitmap("home/lcom/proj/res/duck2.bmp");
	d1->bmp[5] = loadBitmap("home/lcom/proj/res/duck3.bmp");
	d1->bmp[6] = loadBitmap("home/lcom/proj/res/duck_shot.bmp");
	d1->bmp[7] = loadBitmap("home/lcom/proj/res/duck_falling.bmp");
	d1->x_speed = 0;
	d1->y_speed = 0;
	d1->direction = START;
	d1->index = 0;
	d1->current_state = 0;
	d1->auto_counter = 0;
	d1->count = 0;
	d1->count_shot = 0;

	return d1;
}

void destroy_duck(Duck * d1){
	deleteBitmap(d1->bmp[0]);
	deleteBitmap(d1->bmp[1]);
	deleteBitmap(d1->bmp[2]);
	deleteBitmap(d1->bmp[3]);
	deleteBitmap(d1->bmp[4]);
	deleteBitmap(d1->bmp[5]);
	deleteBitmap(d1->bmp[6]);
	deleteBitmap(d1->bmp[7]);
	free(d1);
}

void move_duck(unsigned long scancode, Duck * d1){

	if(d1->direction == SHOT){
		d1->y_speed = 0;
		d1->x_speed = 0;
		d1->index = 6;
		return ;
	}

	if(d1->direction == FALL){
		if(d1->pos_y >= 570){
			d1->y_speed = 0;
			d1->x_speed = 0;
		}
		else{
			d1->y_speed = 6;
			d1->x_speed = 0;
		}
		d1->pos_x += d1->x_speed;
		d1->pos_y += d1->y_speed;
		d1->index = 7;
		return;
	}


	if(d1->pos_y <= 2){
		d1->y_speed = 3;
		if(d1->direction == LEFT_UP){
			d1->direction = LEFT_DOWN;
		}
		else if(d1->direction == RIGHT_UP){
			d1->direction = RIGHT_DOWN;
		}
		scancode = 0;
	}

	if(d1->pos_y >= 570 && d1->direction != START  && d1->direction != FALL){
		d1->y_speed = -3;
		if(d1->direction == LEFT_DOWN){
			d1->direction = LEFT_UP;
		}
		else if(d1->direction == RIGHT_DOWN){
			d1->direction = RIGHT_UP;
		}
		scancode = 0;
	}


	if(d1->pos_x <= 5){
		d1->x_speed = 3;
		if(d1->direction == LEFT_HOR){
			d1->direction = RIGHT_HOR;
		}
		else if(d1->direction == LEFT_UP){
			d1->direction = RIGHT_UP;
		}
		else if(d1->direction == LEFT_DOWN){
			d1->direction = RIGHT_DOWN;
		}
		scancode = 0;

	}

	if(d1->pos_x >= getHorResolution() - d1->bmp[d1->index]->bitmapInfoHeader.width){
		d1->x_speed = -3;
		if(d1->direction == RIGHT_HOR){
			d1->direction = LEFT_HOR;
		}
		else if(d1->direction == RIGHT_UP){
			d1->direction = LEFT_UP;
		}
		else if(d1->direction == RIGHT_DOWN){
			d1->direction = LEFT_DOWN;
		}
		scancode = 0;
	}



	switch(scancode){
	case LEFT_A:
		d1->direction = LEFT_HOR;
		d1->x_speed = -3;
		d1->y_speed = 0;
		break;
	case RIGHT_D:
		d1->direction = RIGHT_HOR;
		d1->x_speed = 3;
		d1->y_speed = 0;
		break;
	case UP_W:
		if(d1->direction == RIGHT_HOR || d1->direction == RIGHT_DOWN){
			d1->direction = RIGHT_UP;
			d1->x_speed = 3;
			d1->y_speed = -3;
		}
		if(d1->direction == LEFT_HOR || d1->direction == LEFT_DOWN){
			d1->direction = LEFT_UP;
			d1->x_speed = -3;
			d1->y_speed = -3;
		}
		break;
	case DOWN_S:
		if(d1->direction == RIGHT_HOR || d1->direction == RIGHT_UP){
			d1->direction = RIGHT_DOWN;
			d1->x_speed = 3;
			d1->y_speed = 3;
		}
		if(d1->direction == LEFT_HOR || d1->direction == LEFT_UP){
			d1->direction = LEFT_DOWN;
			d1->x_speed = -3;
			d1->y_speed = 3;
		}
		break;

	}

	d1->pos_x += d1->x_speed;
	d1->pos_y += d1->y_speed;

}


void select_new_route(Duck * d1){

	int rand_value = (rand() % 5) + 1; // random number between 1 and 5

	if(d1->pos_y > 0 && d1->pos_y < 150){
		switch(rand_value){
		case 1:
			d1->x_speed = 3;
			d1->y_speed = 3;
			d1->direction = RIGHT_DOWN;
			break;
		case 2:
			d1->x_speed = -3;
			d1->y_speed = 3;
			d1->direction = LEFT_DOWN;
			break;
		case 3:
			d1->x_speed = 3;
			d1->y_speed = 0;
			d1->direction = RIGHT_HOR;
			break;
		case 4:
			d1->x_speed = -3;
			d1->y_speed = 0;
			d1->direction = LEFT_HOR;
			break;
		case 5:
			if(d1->pos_x > (getHorResolution() / 2)){
				d1->x_speed = -3;
				d1->y_speed = -3;
				d1->direction = LEFT_UP;
			}
			else{
				d1->x_speed = 3;
				d1->y_speed = -3;
				d1->direction = RIGHT_UP;
			}
		}
	}

	else if(d1->pos_y > 400){
		switch(rand_value){
		case 1:
			d1->x_speed = 3;
			d1->y_speed = -3;
			d1->direction = RIGHT_UP;
			break;
		case 2:
			d1->x_speed = -3;
			d1->y_speed = -3;
			d1->direction = LEFT_UP;
			break;
		case 3:
			d1->x_speed = 3;
			d1->y_speed = 0;
			d1->direction = RIGHT_HOR;
			break;
		case 4:
			d1->x_speed = -3;
			d1->y_speed = 0;
			d1->direction = LEFT_HOR;
			break;
		case 5:
			if(d1->pos_x > (getHorResolution() / 2)){
				d1->x_speed = -3;
				d1->y_speed = 3;
				d1->direction = LEFT_DOWN;
			}
			else{
				d1->x_speed = 3;
				d1->y_speed = 3;
				d1->direction = RIGHT_DOWN;
			}
		}
	}

	else{
		switch(rand_value){
		case 1:
			d1->x_speed = 3;
			d1->y_speed = -3;
			d1->direction = RIGHT_UP;
			break;
		case 2:
			d1->x_speed = -3;
			d1->y_speed = -3;
			d1->direction = LEFT_UP;
			break;
		case 3:
			d1->x_speed = 3;
			d1->y_speed = 3;
			d1->direction = RIGHT_DOWN;
			break;
		case 4:
			d1->x_speed = -3;
			d1->y_speed = 3;
			d1->direction = LEFT_DOWN;
			break;
		case 5:
			if(d1->pos_x > (getHorResolution() / 2)){
				d1->x_speed = -3;
				d1->y_speed = 0;
				d1->direction = LEFT_HOR;
			}
			else{
				d1->x_speed = 3;
				d1->y_speed = 0;
				d1->direction = RIGHT_HOR;
			}
		}
	}

	d1->auto_counter = rand() % 20 + 40;

}



void move_duck_auto(Duck * d1){

	if(d1->direction == SHOT){
		d1->y_speed = 0;
		d1->x_speed = 0;
		d1->index = 6;
		return ;
	}

	if(d1->direction == FALL){
		if(d1->pos_y >= 570){
			d1->y_speed = 0;
			d1->x_speed = 0;
		}
		else{
			d1->y_speed = 6;
			d1->x_speed = 0;
		}
		d1->pos_x += d1->x_speed;
		d1->pos_y += d1->y_speed;
		d1->index = 7;
		return;
	}

	//selecionar novo caminho se necessário

	if(d1->auto_counter == 0){
		select_new_route(d1);
	}



	//movimento se "bater" contra as bordas

	if(d1->pos_y <= 2){
		d1->y_speed = 3;
		if(d1->direction == LEFT_UP){
			d1->direction = LEFT_DOWN;
		}
		else if(d1->direction == RIGHT_UP){
			d1->direction = RIGHT_DOWN;
		}
	}

	if(d1->pos_y >= 570 && d1->direction != START  && d1->direction != FALL){
		d1->y_speed = -3;
		if(d1->direction == LEFT_DOWN){
			d1->direction = LEFT_UP;
		}
		else if(d1->direction == RIGHT_DOWN){
			d1->direction = RIGHT_UP;
		}
	}


	if(d1->pos_x <= 5){
		d1->x_speed = 3;
		if(d1->direction == LEFT_HOR){
			d1->direction = RIGHT_HOR;
		}
		else if(d1->direction == LEFT_UP){
			d1->direction = RIGHT_UP;
		}
		else if(d1->direction == LEFT_DOWN){
			d1->direction = RIGHT_DOWN;
		}
	}

	if(d1->pos_x >= getHorResolution() - d1->bmp[d1->index]->bitmapInfoHeader.width){
		d1->x_speed = -3;
		if(d1->direction == RIGHT_HOR){
			d1->direction = LEFT_HOR;
		}
		else if(d1->direction == RIGHT_UP){
			d1->direction = LEFT_UP;
		}
		else if(d1->direction == RIGHT_DOWN){
			d1->direction = LEFT_DOWN;
		}
	}

	//fim do movimento se "bater" contra as bordas





	d1->pos_x += d1->x_speed;
	d1->pos_y += d1->y_speed;
	d1->auto_counter--;
}



void animate_duck(unsigned long scancode, Duck * d1){

	//static int count = 0;
	//static int count_shot = 0; Used for testing purposes on a single duck

	d1->count = d1->count % 10;

	if(d1->count == 0){
		if(d1->direction == SHOT){
			d1->count_shot++;
		}
		if(d1->direction == SHOT && d1->count_shot > 2){
			d1->direction = FALL;
			d1->index = 7;
			d1->count_shot = 0;
		}
		if(d1->direction == RIGHT_HOR || d1->direction == LEFT_HOR || d1->direction == RIGHT_DOWN || d1->direction == LEFT_DOWN){
			if(d1->current_state > 2){
				d1->current_state = 0;
			}

			if(d1->current_state == 2){
				d1->index = 2;
				d1->current_state++;
			}

			if(d1->current_state == 1){
				d1->index = 1;
				d1->current_state++;
			}

			if(d1->current_state == 0){
				d1->index = 0;
				d1->current_state++;
			}
			// FALTA O INVERT!

		}

		if(d1->direction == RIGHT_UP || d1->direction == LEFT_UP){
			if(d1->current_state > 2){
				d1->current_state = 0;
			}

			if(d1->current_state == 2){
				d1->index = 5;
				d1->current_state++;
			}

			if(d1->current_state == 1){
				d1->index = 4;
				d1->current_state++;
			}

			if(d1->current_state == 0){
				d1->index = 3;
				d1->current_state++;
			}
		}


	}


	d1->count++;

	if(d1->direction == RIGHT_HOR || d1->direction == RIGHT_UP || d1->direction == RIGHT_DOWN || d1->direction == SHOT || d1->direction == FALL){
		drawSprite(d1->bmp[d1->index],d1->pos_x,d1->pos_y,ALIGN_LEFT);
	}
	if(d1->direction == LEFT_HOR || d1->direction == LEFT_UP || d1->direction == LEFT_DOWN){
		drawSpriteInverted(d1->bmp[d1->index],d1->pos_x,d1->pos_y,ALIGN_LEFT);
	}

}

void shot_duck(Duck * d1,Aim * aim){
	if(aim->shot && aim->aim_x < d1->bmp[d1->index]->bitmapInfoHeader.width + d1->pos_x && aim->aim_x > d1->pos_x && aim->aim_y < d1->bmp[d1->index]->bitmapInfoHeader.height + d1->pos_y && aim->aim_y > d1->pos_y ){
		d1->direction = SHOT;
	}
}

void shot_duck2(Duck * d1,Aim * aim, int * number_hits){
	if(aim->shot && aim->aim_x < d1->bmp[d1->index]->bitmapInfoHeader.width + d1->pos_x && aim->aim_x > d1->pos_x && aim->aim_y < d1->bmp[d1->index]->bitmapInfoHeader.height + d1->pos_y && aim->aim_y > d1->pos_y ){
		d1->direction = SHOT;
		(*number_hits)++;
	}
}

void shot_duck2_transmit(Duck * d1,Aim * aim, int * number_hits){
	if(aim->shot && aim->aim_x < d1->bmp[d1->index]->bitmapInfoHeader.width + d1->pos_x && aim->aim_x > d1->pos_x && aim->aim_y < d1->bmp[d1->index]->bitmapInfoHeader.height + d1->pos_y && aim->aim_y > d1->pos_y ){
		d1->direction = SHOT;
		(*number_hits)++;
		write_THR('s');
	}
}

void shot_duck2_receive(Duck * d1,unsigned long *received_char){
	if(*received_char == 's'){
		d1->direction = SHOT;
		*received_char = 0;
	}
}

// Round handling functions


int all_ducks_dead(Duck** ducks_list){
	// retorna 0 se falso, 1 se verdadeiro;
	unsigned int i;
	for(i = 0; i < 10 ; i++){
		if(!((ducks_list[i]->direction == FALL || ducks_list[i]->direction == START) && (ducks_list[i]->pos_y > 560))){
			return 0;
		}
	}
	return 1;
}

int any_ducks_falling(Duck** ducks_list){
	// retorna 0 se falso, 1 se verdadeiro;
	unsigned int i;
	for(i = 0; i < 10 ; i++){
		if((ducks_list[i]->direction != SHOT) && (ducks_list[i]->direction != FALL) && (ducks_list[i]->direction != START)){
			return 0;
		}
	}
	for(i = 0; i < 10 ; i++){
		if((ducks_list[i]->direction == SHOT) || (ducks_list[i]->direction == FALL)){
			return 1;
		}
	}

	return 0;
}


int next_round_ducks(int round){
	//valores a atribuir
	return round;
}

int next_round_bullets(int round){
	//valores a atribuir
	return 10;
}

int next_round_bullets_mp(int round){
	return (11 - round);
}

void place_duck_start_mp(Duck * d1){
	d1->pos_x = getHorResolution()/2;
	d1->pos_y = getVerResolution() - 180;
	d1->x_speed = 0;
	d1->y_speed = 0;
	d1->direction = START;
	d1->index = 0;
	d1->current_state = 0;
	d1->auto_counter = 0;
	d1->count = 0;
	d1->count_shot = 0;
}

void place_ducks_start(Duck** ducks_list){
	unsigned int i;
	for(i = 0; i < 10; i++){
		Duck * d1 = ducks_list[i];
		d1->pos_x = rand() % 400 + 312;
		d1->pos_y = getVerResolution() - 180;
		d1->x_speed = 0;
		d1->y_speed = 0;
		d1->direction = START;
		d1->index = 0;
		d1->current_state = 0;
		d1->auto_counter = 0;
		d1->count = 0;
		d1->count_shot = 0;
	}
}



