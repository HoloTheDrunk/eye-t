# Simple SDL mini Makefile

CC=gcc

CFLAGS= `pkg-config --cflags sdl gtk+-3.0`\
		-Wall -Werror -Wextra -std=c99 -O3 -MMD
LDFLAGS=
LDLIBS=`pkg-config --libs sdl gtk+-3.0` -lSDL_image -lm -lpng

all: main
main: pixel_operations.o main.o image_load.o convolution_matrix.o otsu.o types/matrix.o types/tuple.o types/binary_tree.o autorotate.o rotation.o segmentation.o flood_fill.o recons.o ../neuralnetwork/Network.o ../neuralnetwork/NeuralNetwork.o ../neuralnetwork/layer.o ../neuralnetwork/surface_binlist.o savesurf.o

main.o: main.c *.h types/*.h ../neuralnetwork/*.h

clean:
	${RM} *.o
	${RM} *.d
	${RM} types/*.o
	${RM} types/*.d
	${RM} main
	${RM} ./types/*.o
	${RM} ./types/*.d
	${RM} ../neuralnetwork/*.d
	${RM} ../neuralnetwork/*.o

# END

