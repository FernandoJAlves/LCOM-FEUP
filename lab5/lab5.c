#include "test5.h"
#include "pixmap.h"

static int proc_args(int argc, char **argv);
static unsigned long parse_ulong(char *str, int base);
static void print_usage(char **argv);

int main(int argc, char **argv)
{
	/* To initialize service */
	sef_startup();
	/* Enable IO-sensitive operations for ourselves */
	if (argc == 1) {					/* Prints usage of the program if no arguments are passed */
		print_usage(argv);
		return 0;
	}
	else return proc_args(argc, argv);
}

static void print_usage(char **argv)
{
	printf("Usage: one of the following:\n"
			"\t service run %s -args \"init <hex no.- mode> <decimal no.- delay>\"\n"
			"\t service run %s -args \"square <decimal no. - x> <decimal no. - y> <decimal no. - size> <decimal no. - color>\"\n"
			"\t service run %s -args \"line <decimal no. - xi> <decimal no. - yi> <decimal no. - xf> <decimal no. - yf> <decimal no. - color>\"\n"
			"\t service run %s -args \"xpm <string - xpm> <decimal no. - xi> <decimal no. - yi>\"\n"
			"\t service run %s -args \"move <string - xpm> <decimal no. - xi> <decimal no. - yi> <decimal no. - xf> <decimal no. - yf>  <decimal no. - speed> <decimal no. - framerate>\"\n"
			"\t service run %s -args \"controller\"\n",
			argv[0], argv[0], argv[0], argv[0], argv[0], argv[0]);
}

static int proc_args(int argc, char **argv)
{
	unsigned short mode,delay,x,y,size,xf,yf;
	unsigned long color;
	char **xpm;
	short speed,frame_rate;
	if (strncmp(argv[1], "init", strlen("init")) == 0) {
		if (argc != 4) {
			printf("vbe: wrong no. of arguments for video_test_init()\n");
			return 1;
		}
		mode = parse_ulong(argv[2], 10);
		delay = parse_ulong(argv[3], 10);	/* Parses string to unsigned long */
		if (mode == USHRT_MAX)
			return 1;
		if (delay == USHRT_MAX)
					return 1;
		printf("vbe::mouse_test_packet(%lu)\n", mode);
		return video_test_init(mode,delay);
	}
	else if (strncmp(argv[1], "square", strlen("square")) == 0) {
		if (argc != 6) {
			printf("vbe: wrong no. of arguments for video_test_square()\n");
			return 1;
		}
		x = parse_ulong(argv[2], 10);
		y = parse_ulong(argv[3], 10);
		size = parse_ulong(argv[4], 10);
		color = parse_ulong(argv[5], 10);	/* Parses string to unsigned long */
		if (x == USHRT_MAX)
					return 1;
		if (y == USHRT_MAX)
					return 1;
		if (size == USHRT_MAX)
					return 1;
		if (color == ULONG_MAX)
			return 1;

		printf("vbe::video_test_square(%lu, %lu,%lu, %lu)\n", x,y,size,color);
		return video_test_square(x,y,size,color);
	}
	else if (strncmp(argv[1], "line", strlen("line")) == 0) {
		if (argc != 7) {
			printf("vbe: wrong no of arguments for video_test_line()\n");
			return 1;
		}
		x = parse_ulong(argv[2], 10);
		y = parse_ulong(argv[3], 10);
		xf = parse_ulong(argv[4], 10);
		yf = parse_ulong(argv[5], 10);
		color = parse_ulong(argv[6], 10);	/* Parses string to unsigned long */
		if (x == USHRT_MAX)
			return 1;
		if (y == USHRT_MAX)
					return 1;
		if (xf == USHRT_MAX)
					return 1;
		if (yf == USHRT_MAX)
					return 1;
		if (color == ULONG_MAX)
					return 1;
		printf("vbe::video_test_line(%lu, %lu, %lu, %lu, %lu)\n", x,y,xf,yf,color);
		return video_test_line(x,y,xf,yf,color);


	}
	else if (strncmp(argv[1], "xpm", strlen("xpm")) == 0) {
			if (argc != 5) {
				printf("vbe: wrong no of arguments for video_test_xpm()\n");
				return 1;
			}
			if(strncmp(argv[2], "pic1",strlen("pic1")) == 0){
				xpm = pic1;
			}
			else if(strncmp(argv[2], "pic2",strlen("pic2")) == 0){
				xpm = pic2;
			}
			else if(strncmp(argv[2], "cross",strlen("cross")) == 0){
				xpm = cross;
			}
			else if(strncmp(argv[2], "pic3",strlen("pic3")) == 0){
				xpm = pic3;
			}
			else if(strncmp(argv[2], "penguin",strlen("penguin")) == 0){
				xpm = penguin;
			}
			else{
				printf("The pixmap you indicated was not found. Currently available: pic1, pic2, cross, pic3 and penguin\n");
				return 1;
			}
			x = parse_ulong(argv[3], 10);
			y = parse_ulong(argv[4], 10);/* Parses string to unsigned long */
			if (x == USHRT_MAX)
				return 1;
			if (y == USHRT_MAX)
							return 1;
			printf("vbe::video_test_xpm(%s, %lu, %lu)\n", argv[2],x,y);
			return video_test_xpm(xpm,x,y);
	}

	else if (strncmp(argv[1], "move", strlen("move")) == 0) {
			if (argc != 9) {
				printf("vbe: wrong no of arguments for video_test_move()\n");
				return 1;
			}
			//xpm = parse_ulong(argv[2], 10);
			x = parse_ulong(argv[3], 10);
			y = parse_ulong(argv[4], 10);
			xf = parse_ulong(argv[5], 10);
			yf = parse_ulong(argv[6], 10);
			speed = parse_ulong(argv[7], 10);
			frame_rate = parse_ulong(argv[8], 10);/* Parses string to unsigned long */
			if(strncmp(argv[2], "pic1",strlen("pic1")) == 0){
				xpm = pic1;
			}
			else if(strncmp(argv[2], "pic2",strlen("pic2")) == 0){
				xpm = pic2;
			}
			else if(strncmp(argv[2], "cross",strlen("cross")) == 0){
				xpm = cross;
			}
			else if(strncmp(argv[2], "pic3",strlen("pic3")) == 0){
				xpm = pic3;
			}
			else if(strncmp(argv[2], "penguin",strlen("penguin")) == 0){
				xpm = penguin;
			}
			else{
				printf("The pixmap you indicated was not found. Currently available: pic1, pic2, cross, pic3 and penguin\n");
				return 1;
			}
			if (x == USHRT_MAX)
				return 1;
			if (y == USHRT_MAX)
				return 1;
			if (xf == USHRT_MAX)
				return 1;
			if (yf == USHRT_MAX)
				return 1;
			if (speed == SHRT_MAX)
				return 1;
			if (frame_rate == SHRT_MAX)
				return 1;
			printf("vbe::video_test_move(%s, %lu, %lu,%lu, %lu,%lu, %lu)\n", argv[2],x,y,xf,yf,speed,frame_rate);
			return video_test_move(xpm,x,y,xf,yf,speed,frame_rate);
	}
	else if (strncmp(argv[1], "controller", strlen("controller")) == 0) {
			if (argc != 2) {
				printf("vbe: wrong no of arguments for video_test_controller()\n");
				return 1;
			}
			printf("vbe::video_test_controller()\n");
			return video_test_controller();
	}
	else {
		printf("vbe: %s - no valid function!\n", argv[1]);
		return 1;
	}
}

static unsigned long parse_ulong(char *str, int base)
{
	char *endptr;
	unsigned long val;

	/* Convert string to unsigned long */
	val = strtoul(str, &endptr, base);

	/* Check for conversion errors */
	if ((errno == ERANGE && val == ULONG_MAX) || (errno != 0 && val == 0)) {
		perror("strtoul");
		return ULONG_MAX;
	}

	if (endptr == str) {
		printf("vbe: parse_ulong: no digits were found in %s\n", str);
		return ULONG_MAX;
	}

	/* Successful conversion */
	return val;
}

