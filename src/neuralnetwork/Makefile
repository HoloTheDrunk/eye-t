# Simple SDL mini Makefile

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O1
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image -lm

all: NeuralNetwork

NeuralNetwork: sdl_func.o surface_binlist.o pixel_operations.o layer.o Network.o NeuralNetwork.o ../sdl/types/matrix.o

NeuralNetwork.o: sdl_func.h  surface_binlist.h pixel_operations.h  layer.h Network.h ../sdl/types/matrix.h

clean:
	${RM} *.o
	${RM} *.d
	${RM} main

# END
