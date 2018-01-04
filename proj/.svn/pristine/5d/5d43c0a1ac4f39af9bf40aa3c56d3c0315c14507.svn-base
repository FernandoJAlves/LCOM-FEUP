# Makefile for Duck Hunt

COMPILER_TYPE= gnu

CC= gcc

PROG= DuckHunt
SRCS= main.c vbe.c video_gr.c keyboard.c timer.c bitmap.c game.c menu.c extras.c mouse.c duck.c serial_port.c points.c rtc.S

CFLAGS= -Wall

DPADD+= ${LIBDRIVER} ${LIBSYS}
LDADD+= -llm -ldriver -lsys

LDFLAGS+= -L .

MAN=

BINDIR?= /user/sbin

.include <bsd.prog.mk>
.include <bsd.gcc.mk>