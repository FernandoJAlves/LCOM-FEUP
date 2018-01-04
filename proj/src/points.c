#include "points.h"
#include "video_gr.h"
#include "i8042.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rtc_macros.h"

unsigned long day = 0;
unsigned long month = 0;
unsigned long year = 0;
unsigned long hour = 0;
unsigned long minute = 0;
unsigned int highscore = 0;
char name[9] = {0,0,0,0,0,0,0,0};


//RTC Functions

unsigned int get_min_rtc();
unsigned int get_hour_rtc();
unsigned int get_day_rtc();
unsigned int get_month_rtc();
unsigned int get_year_rtc();

void loadDigits_large(){

	number_0 = loadBitmap("home/lcom/proj/res/number_0.bmp");
	number_1 = loadBitmap("home/lcom/proj/res/number_1.bmp");
	number_2 = loadBitmap("home/lcom/proj/res/number_2.bmp");
	number_3 = loadBitmap("home/lcom/proj/res/number_3.bmp");
	number_4 = loadBitmap("home/lcom/proj/res/number_4.bmp");
	number_5 = loadBitmap("home/lcom/proj/res/number_5.bmp");
	number_6 = loadBitmap("home/lcom/proj/res/number_6.bmp");
	number_7 = loadBitmap("home/lcom/proj/res/number_7.bmp");
	number_8 = loadBitmap("home/lcom/proj/res/number_8.bmp");
	number_9 = loadBitmap("home/lcom/proj/res/number_9.bmp");
	double_dot = loadBitmap("home/lcom/proj/res/double_dot.bmp");
	line = loadBitmap("home/lcom/proj/res/line.bmp");
}

void deleteDigits_large(){
	deleteBitmap(number_0);
	deleteBitmap(number_1);
	deleteBitmap(number_2);
	deleteBitmap(number_3);
	deleteBitmap(number_4);
	deleteBitmap(number_5);
	deleteBitmap(number_6);
	deleteBitmap(number_7);
	deleteBitmap(number_8);
	deleteBitmap(number_9);
	deleteBitmap(double_dot);
	deleteBitmap(line);
}

void loadDigits_small(){

	number_0_small = loadBitmap("home/lcom/proj/res/number_0_small.bmp");
	number_1_small = loadBitmap("home/lcom/proj/res/number_1_small.bmp");
	number_2_small = loadBitmap("home/lcom/proj/res/number_2_small.bmp");
	number_3_small = loadBitmap("home/lcom/proj/res/number_3_small.bmp");
	number_4_small = loadBitmap("home/lcom/proj/res/number_4_small.bmp");
	number_5_small = loadBitmap("home/lcom/proj/res/number_5_small.bmp");
	number_6_small = loadBitmap("home/lcom/proj/res/number_6_small.bmp");
	number_7_small = loadBitmap("home/lcom/proj/res/number_7_small.bmp");
	number_8_small = loadBitmap("home/lcom/proj/res/number_8_small.bmp");
	number_9_small = loadBitmap("home/lcom/proj/res/number_9_small.bmp");
	double_dot_small = loadBitmap("home/lcom/proj/res/double_dot_small.bmp");
	line_small = loadBitmap("home/lcom/proj/res/line_small.bmp");
	duck_bmp = loadBitmap("home/lcom/proj/res/duck_counter.bmp");
	bullet_bmp = loadBitmap("home/lcom/proj/res/bullet.bmp");
}

void deleteDigits_small(){
	deleteBitmap(number_0_small);
	deleteBitmap(number_1_small);
	deleteBitmap(number_2_small);
	deleteBitmap(number_3_small);
	deleteBitmap(number_4_small);
	deleteBitmap(number_5_small);
	deleteBitmap(number_6_small);
	deleteBitmap(number_7_small);
	deleteBitmap(number_8_small);
	deleteBitmap(number_9_small);
	deleteBitmap(double_dot_small);
	deleteBitmap(line_small);
	deleteBitmap(duck_bmp);
	deleteBitmap(bullet_bmp);

}

void loadFont(){
	letter_a = loadBitmap("home/lcom/proj/res/letter_a.bmp");
	letter_b = loadBitmap("home/lcom/proj/res/letter_b.bmp");
	letter_c = loadBitmap("home/lcom/proj/res/letter_c.bmp");
	letter_d = loadBitmap("home/lcom/proj/res/letter_d.bmp");
	letter_e = loadBitmap("home/lcom/proj/res/letter_e.bmp");
	letter_f = loadBitmap("home/lcom/proj/res/letter_f.bmp");
	letter_g = loadBitmap("home/lcom/proj/res/letter_g.bmp");
	letter_h = loadBitmap("home/lcom/proj/res/letter_h.bmp");
	letter_i = loadBitmap("home/lcom/proj/res/letter_i.bmp");
	letter_j = loadBitmap("home/lcom/proj/res/letter_j.bmp");
	letter_k = loadBitmap("home/lcom/proj/res/letter_k.bmp");
	letter_l = loadBitmap("home/lcom/proj/res/letter_l.bmp");
	letter_m = loadBitmap("home/lcom/proj/res/letter_m.bmp");
	letter_n = loadBitmap("home/lcom/proj/res/letter_n.bmp");
	letter_o = loadBitmap("home/lcom/proj/res/letter_o.bmp");
	letter_p = loadBitmap("home/lcom/proj/res/letter_p.bmp");
	letter_q = loadBitmap("home/lcom/proj/res/letter_q.bmp");
	letter_r = loadBitmap("home/lcom/proj/res/letter_r.bmp");
	letter_s = loadBitmap("home/lcom/proj/res/letter_s.bmp");
	letter_t = loadBitmap("home/lcom/proj/res/letter_t.bmp");
	letter_u = loadBitmap("home/lcom/proj/res/letter_u.bmp");
	letter_v = loadBitmap("home/lcom/proj/res/letter_v.bmp");
	letter_w = loadBitmap("home/lcom/proj/res/letter_w.bmp");
	letter_x = loadBitmap("home/lcom/proj/res/letter_x.bmp");
	letter_y = loadBitmap("home/lcom/proj/res/letter_y.bmp");
	letter_z = loadBitmap("home/lcom/proj/res/letter_z.bmp");
}

void deleteFont(){
	deleteBitmap(letter_a);
	deleteBitmap(letter_b);
	deleteBitmap(letter_c);
	deleteBitmap(letter_d);
	deleteBitmap(letter_e);
	deleteBitmap(letter_f);
	deleteBitmap(letter_g);
	deleteBitmap(letter_h);
	deleteBitmap(letter_i);
	deleteBitmap(letter_j);
	deleteBitmap(letter_k);
	deleteBitmap(letter_l);
	deleteBitmap(letter_m);
	deleteBitmap(letter_n);
	deleteBitmap(letter_o);
	deleteBitmap(letter_p);
	deleteBitmap(letter_q);
	deleteBitmap(letter_r);
	deleteBitmap(letter_s);
	deleteBitmap(letter_t);
	deleteBitmap(letter_u);
	deleteBitmap(letter_v);
	deleteBitmap(letter_w);
	deleteBitmap(letter_x);
	deleteBitmap(letter_y);
	deleteBitmap(letter_z);
}



int draw_score_6_digits_small(int score, int x_pos, int y_pos){

	int c_milhar = (score/100000);
	score = (score % 100000);
	int d_milhar = (score/10000);
	score = (score % 10000);
	int milhar = (score/1000);
	score = (score % 1000);
	int centena = (score/100);
	score = (score % 100);
	int dezena = (score/10);
	score = (score % 10);
	int unidade = score;

	int array[6] = {c_milhar, d_milhar, milhar, centena, dezena, unidade};
	int i;

	for(i = 0; i < 6; i++){
		switch(array[i]){
		case 0:
			drawSprite(number_0_small, x_pos, y_pos, ALIGN_LEFT);
			break;
		case 1:
			drawSprite(number_1_small, x_pos, y_pos, ALIGN_LEFT);
			break;
		case 2:
			drawSprite(number_2_small, x_pos, y_pos, ALIGN_LEFT);
			break;
		case 3:
			drawSprite(number_3_small, x_pos, y_pos, ALIGN_LEFT);
			break;
		case 4:
			drawSprite(number_4_small, x_pos, y_pos, ALIGN_LEFT);
			break;
		case 5:
			drawSprite(number_5_small, x_pos, y_pos, ALIGN_LEFT);
			break;
		case 6:
			drawSprite(number_6_small, x_pos, y_pos, ALIGN_LEFT);
			break;
		case 7:
			drawSprite(number_7_small, x_pos, y_pos, ALIGN_LEFT);
			break;
		case 8:
			drawSprite(number_8_small, x_pos, y_pos, ALIGN_LEFT);
			break;
		case 9:
			drawSprite(number_9_small, x_pos, y_pos, ALIGN_LEFT);
			break;
		}
		x_pos += 25;

	}


	return 0;
}

int draw_score_6_digits_large(int score, int x_pos, int y_pos){

	int c_milhar = (score/100000);
	score = (score % 100000);
	int d_milhar = (score/10000);
	score = (score % 10000);
	int milhar = (score/1000);
	score = (score % 1000);
	int centena = (score/100);
	score = (score % 100);
	int dezena = (score/10);
	score = (score % 10);
	int unidade = score;

	int array[6] = {c_milhar, d_milhar, milhar, centena, dezena, unidade};
	int i;

	for(i = 0; i < 6; i++){
		switch(array[i]){
		case 0:
			drawSprite(number_0, x_pos, y_pos, ALIGN_LEFT);
			break;
		case 1:
			drawSprite(number_1, x_pos, y_pos, ALIGN_LEFT);
			break;
		case 2:
			drawSprite(number_2, x_pos, y_pos, ALIGN_LEFT);
			break;
		case 3:
			drawSprite(number_3, x_pos, y_pos, ALIGN_LEFT);
			break;
		case 4:
			drawSprite(number_4, x_pos, y_pos, ALIGN_LEFT);
			break;
		case 5:
			drawSprite(number_5, x_pos, y_pos, ALIGN_LEFT);
			break;
		case 6:
			drawSprite(number_6, x_pos, y_pos, ALIGN_LEFT);
			break;
		case 7:
			drawSprite(number_7, x_pos, y_pos, ALIGN_LEFT);
			break;
		case 8:
			drawSprite(number_8, x_pos, y_pos, ALIGN_LEFT);
			break;
		case 9:
			drawSprite(number_9, x_pos, y_pos, ALIGN_LEFT);
			break;
		}

		x_pos += 66;
	}

	return 0;

}

int draw_ducks_bullets(int ducks, int bullets, int x_pos, int y_pos){

	int x_init = x_pos;
	int i;

	for(i = 0; i < ducks; i++){
		drawSprite(duck_bmp, x_pos, y_pos, ALIGN_LEFT);
		x_pos += 25;
	}
	x_pos = x_init;
	y_pos += 30;
	for(i = 0; i < bullets; i++){
		drawSprite(bullet_bmp, x_pos, y_pos, ALIGN_LEFT);
		x_pos += 25;
	}
	return 0;
}



void small_digit_display(int value, int x_pos, int y_pos){

	switch(value){
	case 0x00:
		drawSprite(number_0_small, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 0x01:
		drawSprite(number_1_small, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 0x02:
		drawSprite(number_2_small, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 0x03:
		drawSprite(number_3_small, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 0x04:
		drawSprite(number_4_small, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 0x05:
		drawSprite(number_5_small, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 0x06:
		drawSprite(number_6_small, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 0x07:
		drawSprite(number_7_small, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 0x08:
		drawSprite(number_8_small, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 0x09:
		drawSprite(number_9_small, x_pos, y_pos, ALIGN_LEFT);
		break;
	}

}

void large_digit_display(int value, int x_pos, int y_pos){

	switch(value){
	case 0x00:
		drawSprite(number_0, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 0x01:
		drawSprite(number_1, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 0x02:
		drawSprite(number_2, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 0x03:
		drawSprite(number_3, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 0x04:
		drawSprite(number_4, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 0x05:
		drawSprite(number_5, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 0x06:
		drawSprite(number_6, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 0x07:
		drawSprite(number_7, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 0x08:
		drawSprite(number_8, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 0x09:
		drawSprite(number_9, x_pos, y_pos, ALIGN_LEFT);
		break;
	}

}


void draw_date_small(int dia, int mes, int ano, int hora, int minuto, int x_pos, int y_pos){

	small_digit_display(DEC(dia), x_pos, y_pos);
	x_pos += 25;
	small_digit_display(UNIT(dia), x_pos, y_pos);
	x_pos += 25;
	drawSprite(line_small, x_pos, y_pos, ALIGN_LEFT);
	x_pos += 25;
	small_digit_display(DEC(mes), x_pos, y_pos);
	x_pos += 25;
	small_digit_display(UNIT(mes), x_pos, y_pos);
	x_pos += 25;
	drawSprite(line_small, x_pos, y_pos, ALIGN_LEFT);
	x_pos += 25;
	small_digit_display(DEC(ano), x_pos, y_pos);
	x_pos += 25;
	small_digit_display(UNIT(ano), x_pos, y_pos);
	x_pos += 60;
	small_digit_display(DEC(hora), x_pos, y_pos);
	x_pos += 25;
	small_digit_display(UNIT(hora), x_pos, y_pos);
	x_pos += 25;
	drawSprite(double_dot_small, x_pos, y_pos, ALIGN_LEFT);
	x_pos += 25;
	small_digit_display(DEC(minuto), x_pos, y_pos);
	x_pos += 25;
	small_digit_display(UNIT(minuto), x_pos, y_pos);

}


void draw_date_large(int dia, int mes, int ano, int hora, int minuto, int x_pos, int y_pos){

	int x_init = x_pos;
	large_digit_display(DEC(dia), x_pos, y_pos);
	x_pos += 66;
	large_digit_display(UNIT(dia), x_pos, y_pos);
	x_pos += 66;
	drawSprite(line, x_pos, y_pos, ALIGN_LEFT);
	x_pos += 66;
	large_digit_display(DEC(mes), x_pos, y_pos);
	x_pos += 66;
	large_digit_display(UNIT(mes), x_pos, y_pos);
	x_pos += 66;
	drawSprite(line, x_pos, y_pos, ALIGN_LEFT);
	x_pos += 66;
	large_digit_display(DEC(ano), x_pos, y_pos);
	x_pos += 66;
	large_digit_display(UNIT(ano), x_pos, y_pos);

	x_pos = x_init;
	y_pos += 112;

	large_digit_display(DEC(hora), x_pos, y_pos);
	x_pos += 66;
	large_digit_display(UNIT(hora), x_pos, y_pos);
	x_pos += 66;
	drawSprite(double_dot, x_pos, y_pos, ALIGN_LEFT);
	x_pos += 66;
	large_digit_display(DEC(minuto), x_pos, y_pos);
	x_pos += 66;
	large_digit_display(UNIT(minuto), x_pos, y_pos);

}



void read_score(){
	FILE * file;
	char tmp[3];
	file = fopen( "home/lcom/proj/res/highscore.txt" , "r");
	if (file) {
	    if (fscanf(file, "%s", tmp)!=EOF){
	    	day = atoi(tmp);
	    	fscanf(file, "%x", &month);
	    	fscanf(file, "%x", &year);
	    	fscanf(file, "%x", &hour);
	    	fscanf(file, "%x", &minute);
	    	fscanf(file, "%d\n", &highscore);
			fscanf(file,"%s",&name);
	    	fclose(file);
	    }
	}
	else{
		printf("Error: Failed to find highscore file to read");
	}
}

void write_score(){
	   FILE *file;
	   file = fopen("home/lcom/proj/res/highscore.txt", "w");
	   if(file){
		   if(highscore != 0){
		   fprintf(file,"%d\n",day);
		   fprintf(file,"%x\n",month);
		   fprintf(file,"%x\n",year);
		   fprintf(file,"%x\n",hour);
		   fprintf(file,"%x\n",minute);
		   fprintf(file,"%d\n",highscore);
		   fprintf(file,"%s",name);
		   fclose(file);
		   }
	   }
	   else{
			printf("Error: Failed to find highscore file to write");
		}
}

void reset_score(){
	   FILE *file;
	   file = fopen("home/lcom/proj/res/highscore.txt", "w");
	   if(file){
		   fclose(file);
		   day = 0;
		   month = 0;
		   year = 0;
		   hour = 0;
		   minute = 0;
		   highscore = 0;
	   }
	   else{
			printf("Error: Failed to find highscore file to write");
		}
}

void update_score(unsigned int points, char nome[9]){
	//char t_year, t_month, t_day, t_hour, t_minute;

	if(points > highscore){
		highscore = points;

		year = get_year_rtc();
		month = get_month_rtc();
		day = get_day_rtc();
		hour = get_hour_rtc();
		minute = get_min_rtc();
		strcpy(name,nome);

	}
}

void draw_char(char c, unsigned int x_pos, unsigned int y_pos){
	switch(c){
	case 'a':
		drawSprite(letter_a, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 'b':
		drawSprite(letter_b, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 'c':
		drawSprite(letter_c, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 'd':
		drawSprite(letter_d, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 'e':
		drawSprite(letter_e, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 'f':
		drawSprite(letter_f, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 'g':
		drawSprite(letter_g, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 'h':
		drawSprite(letter_h, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 'i':
		drawSprite(letter_i, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 'j':
		drawSprite(letter_j, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 'k':
		drawSprite(letter_k, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 'l':
		drawSprite(letter_l, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 'm':
		drawSprite(letter_m, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 'n':
		drawSprite(letter_n, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 'o':
		drawSprite(letter_o, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 'p':
		drawSprite(letter_p, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 'q':
		drawSprite(letter_q, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 'r':
		drawSprite(letter_r, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 's':
		drawSprite(letter_s, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 't':
		drawSprite(letter_t, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 'u':
		drawSprite(letter_u, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 'v':
		drawSprite(letter_v, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 'w':
		drawSprite(letter_w, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 'x':
		drawSprite(letter_x, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 'y':
		drawSprite(letter_y, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 'z':
		drawSprite(letter_z, x_pos, y_pos, ALIGN_LEFT);
		break;
	case 0:
		break;
	case ' ':
		break;
	case '0':
		drawSprite(number_0, x_pos, y_pos, ALIGN_LEFT);
		break;
	case '1':
		drawSprite(number_1, x_pos, y_pos, ALIGN_LEFT);
		break;
	case '2':
		drawSprite(number_2, x_pos, y_pos, ALIGN_LEFT);
		break;
	case '3':
		drawSprite(number_3, x_pos, y_pos, ALIGN_LEFT);
		break;
	case '4':
		drawSprite(number_4, x_pos, y_pos, ALIGN_LEFT);
		break;
	case '5':
		drawSprite(number_5, x_pos, y_pos, ALIGN_LEFT);
		break;
	case '6':
		drawSprite(number_6, x_pos, y_pos, ALIGN_LEFT);
		break;
	case '7':
		drawSprite(number_7, x_pos, y_pos, ALIGN_LEFT);
		break;
	case '8':
		drawSprite(number_8, x_pos, y_pos, ALIGN_LEFT);
		break;
	case '9':
		drawSprite(number_9, x_pos, y_pos, ALIGN_LEFT);
		break;
	}

}

void draw_string(char *nome, unsigned int x_pos, unsigned int y_pos){
	unsigned int i;
	for(i = 0; i < 8;i++){
		draw_char(nome[i],x_pos,y_pos);
		x_pos += 66;
	}
}

void write_char(char * c, unsigned long scancode){
	switch(scancode){
	case SPACE_MAKE:
		*c = ' ';
		break;
	case BACKSPACE_MAKE:
		*c = ' ';
		break;
	case ONE_MAKE:
		*c = '1';
		break;
	case TWO_MAKE:
		*c = '2';
		break;
	case THREE_MAKE:
		*c = '3';
		break;
	case FOUR_MAKE:
		*c = '4';
		break;
	case FIVE_MAKE:
		*c = '5';
		break;
	case SIX_MAKE:
		*c = '6';
		break;
	case SEVEN_MAKE:
		*c = '7';
		break;
	case EIGHT_MAKE:
		*c = '8';
		break;
	case NINE_MAKE:
		*c = '9';
		break;
	case ZERO_MAKE:
		*c = '0';
		break;
	case A_MAKE:
		*c = 'a';
		break;
	case B_MAKE:
		*c = 'b';
		break;
	case C_MAKE:
		*c = 'c';
		break;
	case D_MAKE:
		*c = 'd';
		break;
	case E_MAKE:
		*c = 'e';
		break;
	case F_MAKE:
		*c = 'f';
		break;
	case G_MAKE:
		*c = 'g';
		break;
	case H_MAKE:
		*c = 'h';
		break;
	case I_MAKE:
		*c = 'i';
		break;
	case J_MAKE:
		*c = 'j';
		break;
	case K_MAKE:
		*c = 'k';
		break;
	case L_MAKE:
		*c = 'l';
		break;
	case M_MAKE:
		*c = 'm';
		break;
	case N_MAKE:
		*c = 'n';
		break;
	case O_MAKE:
		*c = 'o';
		break;
	case P_MAKE:
		*c = 'p';
		break;
	case Q_MAKE:
		*c = 'q';
		break;
	case R_MAKE:
		*c = 'r';
		break;
	case S_MAKE:
		*c = 's';
		break;
	case T_MAKE:
		*c = 't';
		break;
	case U_MAKE:
		*c = 'u';
		break;
	case V_MAKE:
		*c = 'v';
		break;
	case W_MAKE:
		*c = 'w';
		break;
	case X_MAKE:
		*c = 'x';
		break;
	case Y_MAKE:
		*c = 'y';
		break;
	case Z_MAKE:
		*c = 'z';
		break;
	}

}






