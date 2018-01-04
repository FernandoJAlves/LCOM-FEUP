#include <limits.h>
#include <string.h>
#include <errno.h>
#include <minix/drivers.h>
#include <minix/driver.h>
#include "menu.h"

int main(int argc, char **argv)
{
	/* To initialize service */
	sef_startup();
	/* Enable IO-sensitive operations for ourselves */
	sys_enable_iop(SELF);
	return main_menu();
}
