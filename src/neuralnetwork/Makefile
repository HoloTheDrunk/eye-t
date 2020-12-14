# Simple SDL mini Makefile

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O1
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image -lm

all: NeuralNetwork

NeuralNetwork: ../sdl/image_load.o surface_binlist.o ../sdl/pixel_operations.o layer.o Network.o NeuralNetwork.o ../sdl/types/matrix.o

NeuralNetwork.o: ../sdl/image_load.h surface_binlist.h ../sdl/pixel_operations.h  layer.h Network.h ../sdl/types/matrix.h

clean:
	${RM} *.o
	${RM} *.d
	${RM} NeuralNetwork

# END
