# Simple SDL mini Makefile

CC=gcc

CPPFLAGS=`pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3 -g
LDFLAGS=
LDLIBS=`pkg-config --libs sdl` -lSDL_image -lm

all: main
main: pixel_operations.o main.o image_load.o convolution_matrix.o otsu.o types/matrix.o types/tuple.o types/binary_tree.o autorotate.o rotation.o segmentation.o recons.o

main.o: main.c *.h types/*.h

clean:
	${RM} *.o
	${RM} *.d
	${RM} types/*.o
	${RM} types/*.d
	${RM} main
	${RM} ./types/*.o
	${RM} ./types/*.d
	${RM} xor

# END

