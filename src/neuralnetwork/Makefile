# Simple SDL mini Makefile

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O1 
LDFLAGS= 
LDLIBS= `pkg-config --libs sdl` -lSDL_image -lm

all: main

main: sdl_func.o surface_binlist.o pixel_operations.o layer.o Network.o main.o

main.o: sdl_func.h  surface_binlist.h pixel_operations.h  layer.h Network.h

clean:
	${RM} *.o
	${RM} *.d
	${RM} main

# END
