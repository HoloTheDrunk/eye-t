# Simple SDL mini Makefile

CC=gcc

CPPFLAGS=`pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS=`pkg-config --libs sdl` -lSDL_image

all: main
main: pixel_operations.o main.o image_load.o

main.o: pixel_operations.h main.c image_load.c

clean:
	${RM} *.o
	${RM} *.d
	${RM} main

# END
