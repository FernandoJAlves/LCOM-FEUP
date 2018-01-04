#include <stdio.h>
#include "test3.h"

static int proc_args(int argc, char **argv);
static unsigned long parse_ulong(char *str, int base);
static void print_usage(char **argv);

int main(int argc, char **argv){
	sef_startup();
	sys_enable_iop(SELF);
	if (argc == 1) {
			print_usage(argv);
			return 0;
		}
		else return proc_args(argc, argv);
	return 0;
}

static void print_usage(char **argv)
{
	printf("Usage: one of the following:\n"
			"\t service run %s -args \"scan <decimal no.- IH>\"\n"
			"\t service run %s -args \"poll <no arguments>\"\n"
			"\t service run %s -args \"int <decimal no. - time>\"\n",
			argv[0], argv[0], argv[0]);
}

static int proc_args(int argc, char **argv)
{
	unsigned short ih, time;
	if (strncmp(argv[1], "scan", strlen("scan")) == 0) {
		if (argc != 3) {
			printf("keyboard: wrong no. of arguments for kbd_test_scan()\n");
			return 1;
		}
		ih = parse_ulong(argv[2], 10);						/* Parses string to unsigned short */
		if (ih == USHRT_MAX)
			return 1;
		printf("keyboard::kbd_test_scan(%lu)\n", ih);
		return kbd_test_scan(ih);
	}
	else if (strncmp(argv[1], "poll", strlen("poll")) == 0) {
		if (argc != 2) {
			printf("keyboard: wrong no. of arguments for kbd_test_poll()\n");
			return 1;
		}
		printf("keyboard::kbd_test_poll()\n");
		return kbd_test_poll();
	}
	else if (strncmp(argv[1],"int", strlen("int")) == 0) {
		if (argc != 3) {
			printf("keyboard: wrong no of arguments for timer_test_int()\n");
			return 1;
		}
		time = parse_ulong(argv[2], 10);						/* Parses string to unsigned long */
		if (time == USHRT_MAX)
			return 1;
		printf("kbd_test_timed_scan(%lu)\n", time);
		return kbd_test_timed_scan(time);
	}
	else {
		printf("keyboard: %s - no valid function!\n", argv[1]);
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
	if ((errno == ERANGE && val == USHRT_MAX) || (errno != 0 && val == 0)) {
		perror("strtoul");
		return USHRT_MAX;
	}

	if (endptr == str) {
		printf("timer: parse_ushrt: no digits were found in %s\n", str);
		return USHRT_MAX;
	}

	/* Successful conversion */
	return val;
}
