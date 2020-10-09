# Simple SDL mini Makefile

CC=gcc

CPPFLAGS=`pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS=`pkg-config --libs sdl` -lSDL_image

all: display blackwhite

display: display.o
blackwhite: pixel_operations.o blackwhite.o

blackwhite.o: pixel_operations.h blackwhite.c

clean:
	${RM} *.o
	${RM} *.d
	${RM} display
	${RM} blackwhite

# END
