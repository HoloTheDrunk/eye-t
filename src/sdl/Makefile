# Simple SDL mini Makefile

CC=gcc

CPPFLAGS=`pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3 -g
LDFLAGS=
LDLIBS=`pkg-config --libs sdl` -lSDL_image -lm

all: main
main: pixel_operations.o main.o image_load.o convolution_matrix.o otsu.o types/matrix.o types/tuple.o hough_transform.o autorotate.o rotation.o

main.o: pixel_operations.h main.c image_load.c convolution_matrix.c otsu.c types/matrix.c types/tuple.c hough_transform.c autorotate.h rotation.h

clean:
	${RM} *.o
	${RM} *.d
	${RM} main

# END
